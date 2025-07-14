#include "conversion_macros.h"
#include "precise_delay.h"
#include "motor.h"
#include "mcc_mapping.h"
#include "config.h"

/****************************/
/*** internal definitions ***/
/****************************/
#define U16_TSECT_OFF              ((uint16_t)(-1))
#define MAX_AMP_GET                ((int24_t)(PWM_PERIOD/1))
#define MIN_AMP_GET                ((int24_t)(0))

#define DRIVE_OFF    (0)
#define DRIVE_ALIGN  (DRIVE_BH | DRIVE_AL | DRIVE_CL)
#define DRIVE_ALL    (DRIVE_AH | DRIVE_BH | DRIVE_CH | DRIVE_AL | DRIVE_BL | DRIVE_CL)
        

/****************************/
/****** internal data *******/
/****************************/

const uint8_t drive_table[8] = {
    0,
    DRIVE_BH | DRIVE_CL, // A float
    DRIVE_AH | DRIVE_CL, // B float
    DRIVE_AH | DRIVE_BL, // C float
    DRIVE_CH | DRIVE_BL, // A float
    DRIVE_CH | DRIVE_AL, // B float
    DRIVE_BH | DRIVE_AL, // C float
    0
};

const uint8_t cmp_mux_table[8] = {
    0,
    CMP_MUX_A | CMP_MUX_N,
    CMP_MUX_B | CMP_MUX_N,
    CMP_MUX_C | CMP_MUX_N,
    CMP_MUX_A | CMP_MUX_N,
    CMP_MUX_B | CMP_MUX_N,
    CMP_MUX_C | CMP_MUX_N,
    0
};

/* status flags */
static volatile bool status_running, status_amp_en;
static volatile motor_status_t status_events;

static volatile uint8_t  position;
static volatile uint16_t actual_amplitude, target_amplitude;
static volatile uint16_t timerPeriod;
static volatile uint16_t integrator;


/****************************/
/***** private functions ****/
/****************************/

static void __AmpRamp(void)
{
    static uint16_t cnt = 0;
    cnt++;
    if(cnt == MOTOR_AMPRAMP_STEP_INTERVAL)
    {
        cnt = 0;
        if(actual_amplitude > target_amplitude)
        {
            actual_amplitude --;
        }
        else if(actual_amplitude < target_amplitude)
        {
            actual_amplitude ++;
        }
    }
}

/* data shared across __Speed_* functions only */
static volatile uint16_t speed_base, speed_counter, measured_speed, target_speed;
static inline void __Speed_Clear(void)
{
    speed_counter = 0;
    speed_base = 0;
}

static inline int16_t FXP_Multiply(fixp_t factor, int16_t data)
{
    int32_t data32 = (int32_t)data * factor;
    data32 >>= 15;
    return (int16_t)data32;
}

/* parameter: 'false' - normal run , 'true' - first run */
static void __Speed_Control(bool state)
{
    static uint16_t integrator = 0;
    
    if(state == true)
    {
        integrator = actual_amplitude;
        target_speed = REGULATOR_MIN_SPEED/SPEED_MEASUREMENT_CONSTANT;
    }
    
    if((MOTOR_SPEED_REGULATOR_EN == true) && (status_amp_en))
    {
        int16_t Ki_err, Kp_err, err;
        int24_t tmp;
        tmp = (int24_t)target_speed - (int24_t)measured_speed;
        err = (int16_t)SATURATE(tmp, -32000, 32000);

        Ki_err = FXP_Multiply(FLOAT_TO_FIXP(REGULATOR_PI_KI), err);
        Kp_err = FXP_Multiply(FLOAT_TO_FIXP(REGULATOR_PI_KP), err);
        
        tmp = (int24_t)Ki_err + (int24_t)integrator;
        integrator = (uint16_t)SATURATE(tmp, MIN_AMP_GET, MAX_AMP_GET);
        
        tmp = (int24_t)Kp_err + (int24_t)integrator;
        actual_amplitude = (uint16_t)SATURATE(tmp, MIN_AMP_GET, MAX_AMP_GET);
    }
}

/* returns 'true' if a new result is available after speed measurement */
static inline bool __Speed_Base(void)
{
    speed_base++;
    if(speed_base == SPEED_MEASUREMENT_BASE)
    {
        measured_speed = speed_counter;
        __Speed_Clear();
        return true;
    }
    else return false;
}

static inline void __Speed_Count(void)
{
    speed_counter++;
}

static inline uint16_t __Speed_Get(void)
{
    uint16_t retval;
    ATOMIC_COPY(retval, measured_speed);
    return retval;
}

static inline void __Speed_Reset(void)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        measured_speed = 0;
        __Speed_Clear();
    }
}

static void __Drive(uint8_t drive_pins)
{
    if(drive_pins & DRIVE_AH)  PWM_TIMER_DCY_SET_A(actual_amplitude);
    else                       PWM_TIMER_DCY_SET_A(0);
    if(drive_pins & DRIVE_BH)  PWM_TIMER_DCY_SET_B(actual_amplitude);
    else                       PWM_TIMER_DCY_SET_B(0);
    if(drive_pins & DRIVE_CH)  PWM_TIMER_DCY_SET_C(actual_amplitude);
    else                       PWM_TIMER_DCY_SET_C(0);

    DRIVE_LOW(drive_pins & (DRIVE_AL | DRIVE_BL | DRIVE_CL));
}

static void __ShutOff(void)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        __Drive(DRIVE_OFF);
        status_amp_en = 0;
        status_running = 0;
        actual_amplitude = 0;
        position = 1;
        __Speed_Reset();
        SECTOR_TIMER_STOP();
        SECTOR_TIMER_PERIOD_SET(U16_TSECT_OFF);
    }
}

static void  __Motor_StallHandler(void)
{
    if((status_running == 0) || (STALL_DETECTION_DISABLED == true))
        return;  /* motor already off, nothing to do */
    __ShutOff();
    status_events |= MOTOR_EVENT_STALL;
}

/* x is a constant between 0 .... 30 degrees */
static inline uint16_t __Phase_Advance(float x, uint16_t y)    { split24_t ph; ph.W = (uint24_t)(256.0 * (x) / 60.0) * (y); return ph.H; }

static void  __Sector_Changer(void)
{
    static uint8_t stall_counter;
    CAPTURE_TIMER_COUNTER_SET(0);

    if(status_running == 1)
    {
        uint16_t capValue = CAPTURE_TIMER_PERIOD_GET();
        CAPTURE_TIMER_PERIOD_SET(65535);
        position++; if(position == 7) position = 1;
        uint8_t drive = drive_table[position];
        __Drive(drive);
        COMP_MUX_SET(cmp_mux_table[position]);
        COMP_INVERT((position & 1));  /* if even sector, comparator's output inverted */

        uint16_t limitValue = timerPeriod - (timerPeriod >> 4); /* limit capture position to 15/16*timerPeriod */
        if(capValue >= limitValue)
        {
            stall_counter++;
            if(stall_counter > STALL_DETECTION_THRESHOLD)
            {
                timerPeriod = U16_TSECT_OFF;
                __Motor_StallHandler();
            }
        }
        else if(stall_counter > 0)
        {
            stall_counter--;
        }
        uint16_t setValue;
        int24_t deltaValue;
        uint24_t tmp;
        setValue = (timerPeriod >> 1);
        setValue += __Phase_Advance(MOTOR_PHASE_ADVANCE, timerPeriod);
        deltaValue = (int24_t)capValue - (int24_t)setValue;

        tmp = (uint24_t)integrator + (deltaValue >> 8);
        if(tmp > 65535u) integrator = 65535;
        else             integrator = tmp;

        tmp = (uint24_t)integrator + (deltaValue >> 2);
        if(tmp > 65535u) timerPeriod = 65535;
        else             timerPeriod = tmp;

        if((timerPeriod < CONVERT_ERPM_TO_STMR(MOTOR_MAXIMUM_ERPM)))
        {
            timerPeriod = U16_TSECT_OFF;
            __Motor_StallHandler();
        }
        if(MOTOR_FORCED == false)
            SECTOR_TIMER_PERIOD_SET(timerPeriod);

        __Speed_Count();
    }
    else
    {
        stall_counter = 0;
    }
}

static inline void __Align(void)
{
    __Drive(DRIVE_OFF);
    PRECISE_DELAY_MS(5);
    __Drive(DRIVE_ALIGN);
    PRECISE_DELAY_MS(MOTOR_ALIGNMENT_DURATION);
    position = 1;
    __Drive(drive_table[position]);
}

static inline void __Current_Trip_EdgeSense(bool edge)
{
    if(edge == true)
        FAULT_CONTROL = COMP_EDGE_RISING;
    else
        FAULT_CONTROL = COMP_EDGE_FALLING;  
}

static inline void __Current_Trip_Disable(void)
{
    FAULT_CONTROL = FAULT_DISABLE;
}

static void __Current_Trip_Handler(void)
{
    if(status_running == 0)
        return;  /* motor already off, nothing to do */
    __ShutOff();
    status_events |= MOTOR_EVENT_FAULT;
}

/****************************/
/***** public functions *****/
/****************************/
void Motor_Initialize(void)
{
    __ShutOff();
    __Current_Trip_Disable();
    __Current_Trip_EdgeSense(FAULT_COMPARATOR_EDGE);
    /* this setting has no effect in case of external-comparator setup: */
    CURRENT_TRIP_LEVEL_SET(CURRENT_TO_ACREF(COMPARATOR_CURRENT_TRIP));
    status_events = 0;
    SECTOR_TIMER_CB_REGISTER(__Sector_Changer);
}


motor_status_t Motor_StatusGet(void)
{
    motor_status_t  retval = status_events;
    status_events = 0;
    if(status_running == 1)
        retval |= MOTOR_RUNNING;
    else
        retval |= MOTOR_IDLE;
    return retval;
}


uint32_t Motor_ErpmGet(void)
{
    return SPEED_MEASUREMENT_CONSTANT * (uint32_t)__Speed_Get();
}


void Motor_CommandSet(uint16_t ref)
{
    if(status_amp_en)
    {
        if(MOTOR_SPEED_REGULATOR_EN == false) ATOMIC_COPY(target_amplitude, ref);
        else                                  ATOMIC_COPY(target_speed, ref);
    }
}


uint16_t  Motor_AmplitudeGet(void)
{
    uint16_t retval;
    ATOMIC_COPY(retval, actual_amplitude);
    return retval;
}


void Motor_Start(uint16_t vbus_adc)
{
    if(status_running == 1)
        return;  /* already running */
    __Speed_Reset();
    uint16_t start_amp = (uint16_t)(MOTOR_STARTUP_CURRENT * MAX_AMP_GET * MOTOR_RPP / (0.75 * ADC_TO_VOLTAGE(vbus_adc)));
    ATOMIC_COPY(target_amplitude, start_amp);
    ATOMIC_COPY(actual_amplitude, start_amp);

    SECTOR_TIMER_COUNTER_SET(0);
    SECTOR_TIMER_PERIOD_SET(U16_TSECT_OFF);
    timerPeriod = U16_TSECT_OFF;
    integrator = U16_TSECT_OFF;
    status_running = 1;
    __Align();
    if(FAULT_COMPARATOR_EN == true)
    {
        CURRENT_TRIP_SetInterruptHandler(__Current_Trip_Handler);
    }
    SECTOR_TIMER_START();
    if(MOTOR_STARTUP_TIME != -1)
    {
        PRECISE_DELAY_MS(MOTOR_STARTUP_TIME);
        status_amp_en = 1;
        if(MOTOR_SPEED_REGULATOR_EN == true)
        {
            __Speed_Control(true); /* initialize integrator */
        }
    }
}


void  Motor_Fault(motor_fault_t event)
{
    if(status_running == 0)
        return;  /* motor already off, nothing to do */

    __ShutOff();
    if(FAULT_COMPARATOR_EN == true)
    {
        CURRENT_TRIP_SetInterruptHandler(NULL);
    }
    if(event == MOTOR_FAULT_OVERCURRENT)
        status_events |= MOTOR_EVENT_OC;
    if(event == MOTOR_FAULT_OVERVOLTAGE)
        status_events |= MOTOR_EVENT_OV;
}


void Motor_Stop(void)
{
    __ShutOff();
    if(FAULT_COMPARATOR_EN == true)
    {
        CURRENT_TRIP_SetInterruptHandler(NULL);
    }
}


uint16_t Motor_MaxAmpGet(void)
{
    return MAX_AMP_GET;
}

/* this function has to be called once every 1 ms, on interrupt context */
void  Motor_TimeTick(void)
{
    if(status_running == 1)
    {
        bool new_speed = __Speed_Base();
        if(status_amp_en)
        {
            if(MOTOR_SPEED_REGULATOR_EN == true)
            {
                if(new_speed) __Speed_Control(false);
            }
            else
            {
                __AmpRamp();
            }
        }
    }
}
