/*
© [2026] Microchip Technology Inc. and its subsidiaries.
 
    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include <stdbool.h>
#include <stdint.h>
#include "conversion_macros.h"
#include "precise_delay.h"
#include "motor.h"
#include "mcc_mapping.h"
#include "config.h"

/****************************/
/*** internal definitions ***/
/****************************/
#define U16_TSECT_OFF              ((uint16_t)(-1))
#define MAX_AMP_GET                FLOAT_TO_FIXP16(1.0)
#define MIN_AMP_GET                ((int24_t)(0))

#define DRIVE_OFF               ((split16_t){.H8 = 0,        .L8 = 0})
#define DRIVE_ALIGN_3P          ((split16_t){.H8 = DRIVE_BH, .L8 = DRIVE_AL | DRIVE_CL})
#define DRIVE_ALIGN_SP          ((split16_t){.H8 = DRIVE_AH, .L8 = DRIVE_BL})
#define DRIVE_ALIGN             (ONE_PHASE_MODE ? DRIVE_ALIGN_SP : DRIVE_ALIGN_3P)
#define DRIVE_TABLE_3P          ((direction == DIR_CW) ? drive_table_cw : drive_table_ccw)
#define CMP_MUX_TABLE_3P        ((direction == DIR_CW) ? cmp_mux_table_cw : cmp_mux_table_ccw)
#define DRIVE_TABLE             (ONE_PHASE_MODE ? drive_table_sp : DRIVE_TABLE_3P)
#define CMP_MUX_TABLE           (ONE_PHASE_MODE ? cmp_mux_table_sp : CMP_MUX_TABLE_3P)
#define HALL_MASK_TABLE		    ((direction == DIR_CW) ? hall_mask_table_cw : hall_mask_table_ccw)
#define MAX_POSITION            (ONE_PHASE_MODE ? 5 : 7)
#define PERIOD_SHIFT            (ONE_PHASE_MODE ? 0 : 1)
#define ONE_PHASE_CONDITION     (ONE_PHASE_MODE ? (position & 1) : true)
#define CMP_INV_MASK            (ONE_PHASE_MODE ? 0 : (position & 1))
#define HALL_INV_TABLE		    ((direction == DIR_CW) ? hall_inv_table_cw : hall_inv_table_ccw)
#define EVEN_HALL_SECT          ((HALL_INVERTED == true) ? 0 : HALL_INVERT)
#define ODD_HALL_SECT           ((HALL_INVERTED == true) ? HALL_INVERT : 0)
#define HALL_INV_MASK           ((position & 1) ? ODD_HALL_SECT : EVEN_HALL_SECT)
#define CAPTURE_CNT_RESET       ((low_speed == false) ? 48 : 0)
#define LOW_SPEED_MODE          ((MOTOR_STATRUP_SPEED > CONVERT_STMR_TO_ERPM(U16_TSECT_OFF, 1)) ? false : true)
#define MOTOR_MIN_SPEED         (500.0) // e-RPM
#define MOTOR_INITIAL_SPEED     ((MOTOR_STATRUP_SPEED < MOTOR_MIN_SPEED) ? MOTOR_MIN_SPEED : MOTOR_STATRUP_SPEED) // e-RPM
#define CAPTURE_PER_RESET       ((HALL_ENABLED == true) ? CONVERT_ERPM_TO_STMR(MOTOR_MIN_SPEED, DIV_LOW_SPEED) : U16_TSECT_OFF)
#define LOW_TO_HIGH_SP_TH       (4800.0) // e-RPM
#define HIGH_TO_LOW_SP_TH       (4000.0) // e-RPM

typedef enum {
    PWM_MODE,
    SP_MODE
} mode_t;

typedef enum
{
    STALL_NONE,
    STALL_TOO_LATE,
    STALL_TOO_FAST,
} stall_ev_t;

/****************************/
/****** internal data *******/
/****************************/


/* Three Phase mode tables */

/* ======================== START - Three Phase CW Direction ================= */

/* Drive Table */
const split16_t drive_table_cw[8] = {
    {.H8 = 0,        .L8 = 0},
    {.H8 = DRIVE_BH, .L8 = DRIVE_CL}, // A float
    {.H8 = DRIVE_AH, .L8 = DRIVE_CL}, // B float
    {.H8 = DRIVE_AH, .L8 = DRIVE_BL}, // C float
    {.H8 = DRIVE_CH, .L8 = DRIVE_BL}, // A float
    {.H8 = DRIVE_CH, .L8 = DRIVE_AL}, // B float
    {.H8 = DRIVE_BH, .L8 = DRIVE_AL}, // C float
    {.H8 = 0,        .L8 = 0},
};

/* MUX Table */
const uint8_t cmp_mux_table_cw[8] = {
    0,
    CMP_MUX_A | CMP_MUX_N,
    CMP_MUX_B | CMP_MUX_N,
    CMP_MUX_C | CMP_MUX_N,
    CMP_MUX_A | CMP_MUX_N,
    CMP_MUX_B | CMP_MUX_N,
    CMP_MUX_C | CMP_MUX_N,
    0
};

/* HALL Invert Table*/
register8_t* const hall_inv_table_cw[8] = {
    NULL,
    &(HALL_PORT.HALL_C_PIN),
    &(HALL_PORT.HALL_A_PIN),
    &(HALL_PORT.HALL_B_PIN),
    &(HALL_PORT.HALL_C_PIN),
    &(HALL_PORT.HALL_A_PIN),
    &(HALL_PORT.HALL_B_PIN),
    NULL
};

/* HALL Mask Table */
const uint8_t hall_mask_table_cw[8] = {
    0,
    HALL_MASK_C,
    HALL_MASK_A,
    HALL_MASK_B,
    HALL_MASK_C,
    HALL_MASK_A,
    HALL_MASK_B,
    0
};

/* ======================== END - Three Phase CW Direction =================== */

/* ======================== START - Three Phase CCW Direction ================ */

/* Drive Table */
const split16_t drive_table_ccw[8] = {
    {.H8 = 0,        .L8 = 0},
    {.H8 = DRIVE_BH, .L8 = DRIVE_AL}, // A float
    {.H8 = DRIVE_CH, .L8 = DRIVE_AL}, // B float
    {.H8 = DRIVE_CH, .L8 = DRIVE_BL}, // C float
    {.H8 = DRIVE_AH, .L8 = DRIVE_BL}, // A float
    {.H8 = DRIVE_AH, .L8 = DRIVE_CL}, // B float
    {.H8 = DRIVE_BH, .L8 = DRIVE_CL}, // C float
    {.H8 = 0,        .L8 = 0},
};

/* MUX Table */
const uint8_t cmp_mux_table_ccw[8] = {
    0,
    CMP_MUX_C | CMP_MUX_N,
    CMP_MUX_B | CMP_MUX_N,
    CMP_MUX_A | CMP_MUX_N,
    CMP_MUX_C | CMP_MUX_N,
    CMP_MUX_B | CMP_MUX_N,
    CMP_MUX_A | CMP_MUX_N,
    0
};

/* HALL Invert Table*/
register8_t* const hall_inv_table_ccw[8] = {
    NULL,
    &(HALL_PORT.HALL_C_PIN),
    &(HALL_PORT.HALL_B_PIN),
    &(HALL_PORT.HALL_A_PIN),
    &(HALL_PORT.HALL_C_PIN),
    &(HALL_PORT.HALL_B_PIN),
    &(HALL_PORT.HALL_A_PIN),
    NULL
};

/* HALL Mask Table */
const uint8_t hall_mask_table_ccw[8] = {
    0,
    HALL_MASK_C,
    HALL_MASK_B,
    HALL_MASK_A,
    HALL_MASK_C,
    HALL_MASK_B,
    HALL_MASK_A,
    0
};

/* ======================== END - Three Phase CCW Direction ================== */


/* One Phase (Single Phase) mode tables  */

/* ======================== START - One Phase CW/CCW Direction =================== */

/* Drive Table */
const split16_t drive_table_sp[5] = {
    {.H8 = 0,        .L8 = 0},
    {.H8 = 0,        .L8 = 0},        // A & B float
    {.H8 = DRIVE_AH, .L8 = DRIVE_BL}, 
    {.H8 = 0,        .L8 = 0},        // A & B float
    {.H8 = DRIVE_BH, .L8 = DRIVE_AL}, 
};

/* MUX Table */
const uint8_t cmp_mux_table_sp[5] = {
    0,
    CMP_MUX_B | CMP_MUX_N,
    CMP_MUX_B | CMP_MUX_N,
    CMP_MUX_A | CMP_MUX_N,
    CMP_MUX_A | CMP_MUX_N,
};

/* ======================== END - One Phase CW/CCW Direction ===================== */

/* status flags */
static          bool status_running, command_enabled, hall_enabled, low_speed;
static volatile motor_status_t status_events;

static          uint8_t     position;
static volatile fixp16_t    actual_amplitude, target_amplitude;
static volatile uint16_t    timerPeriod;
static volatile uint16_t    integrator;
static          mode_t      drive_mode;
static          motor_dir_t direction;

/****************************/
/***** private functions ****/
/****************************/

static void __OpenLoop_Control(void)
{
    if(actual_amplitude > target_amplitude)
    {
        actual_amplitude -= FLOAT_TO_FIXP16(MOTOR_OPEN_LOOP_RAMP);
        if(actual_amplitude > FLOAT_TO_FIXP16(1.0))  // TEST IF NEGATIVE
            actual_amplitude = 0;
    }
    else if(actual_amplitude < target_amplitude)
    {
        actual_amplitude += FLOAT_TO_FIXP16(MOTOR_OPEN_LOOP_RAMP);
        if(actual_amplitude > FLOAT_TO_FIXP16(1.0))  // TEST IF OVERFLOW
            actual_amplitude = FLOAT_TO_FIXP16(1.0);
    }
}

extern uint16_t fmul_FP16xU16(fixp16_t a, uint16_t b);
/* asm function with C equivalent:
uint16_t fmul_FP16xU16(fixp16_t a, uint16_t b)
{
    uint16_t result = ((uint32_t)a * (uint32_t)b) >> 15;
    return   result;
}
*/

int24_t  Multiply_U16xI16(uint16_t a,  int16_t b)
{
    int24_t result;
    result = (uint24_t)a * (int24_t)b;
    return   result;
}

/* data shared across __Speed_* functions only */
static volatile uint16_t speed_base, speed_counter, measured_speed, target_speed;
static inline void __Speed_Clear(void)
{
    speed_counter = 0;
    speed_base = 0;
}

/* parameter: 'false' - normal run , 'true' - first run & initialization */
static void __Speed_Control(bool state)
{
    static uint16_t integrator = 0;
    
    if(state == true)
    {
        integrator = actual_amplitude;
        target_speed = (uint16_t)(REGULATOR_MIN_SPEED/SPEED_MEASUREMENT_FACTOR);
    }
    
    if((REGULATOR_SPEED_EN == true) && (command_enabled))
    {
        int24_t Ki_err, Kp_err, err, tmp;
        tmp = (int24_t)target_speed - (int24_t)measured_speed;
        err = (int16_t)SATURATE(tmp, -32000, 32000);

        Ki_err = Multiply_U16xI16((uint16_t)(REGULATOR_PI_KI * REGULATOR_PI_DT), err);
        Kp_err = Multiply_U16xI16((uint16_t)(REGULATOR_PI_KP), err);
        
        tmp = Ki_err + (int24_t)integrator;
        integrator = (uint16_t)SATURATE(tmp, MIN_AMP_GET, MAX_AMP_GET);
        
        tmp = Kp_err + (int24_t)integrator;
        actual_amplitude = (uint16_t)SATURATE(tmp, MIN_AMP_GET, MAX_AMP_GET);
    }
}

/* returns 'true' if a new result is available after speed measurement */
static inline bool __Speed_Base(void)
{
    speed_base++;
    if(speed_base == SPEED_MEASUREMENT_BASE)
    {
        ATOMIC_COPY(measured_speed, speed_counter);
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

static inline void __Drive(split16_t pins)
{    
    DRIVE_PINS(pins.H8, pins.L8);
}

static void __ShutOff(void)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        __Drive(DRIVE_OFF);
        command_enabled = false;
        status_running = false;
        actual_amplitude = 0;
        position = 1;
        __Speed_Reset();
        SECTOR_TIMER_STOP();
        SECTOR_TIMER_PERIOD_SET(U16_TSECT_OFF);
    }
}

static inline void  __Motor_StallHandler(stall_ev_t ev)
{
    static uint8_t stall_counter = 0;
    if(status_running == false)
    {
        stall_counter = 0;
        /* motor already off, nothing to do */
    }
    else
    {
        switch(ev)
        {
            case STALL_NONE:     if(stall_counter) stall_counter--;  break;
            case STALL_TOO_LATE: stall_counter++; if(stall_counter > STALL_DETECTION_THRESHOLD) {__ShutOff(); status_events |= MOTOR_EVENT_STALL; } break;
            case STALL_TOO_FAST: __ShutOff(); status_events |= MOTOR_EVENT_STALL; break;
        }
    }
}

/* x is a constant between 0 .... 30 electrical degrees */
static inline uint16_t __Phase_Advance(float x, uint16_t y)    { split24_t ph; ph.W24 = (uint24_t)(256.0 * (x) / 60.0) * (y); return ph.H16; }

static inline void __PWM_SP_Switch(void)
{
    if((measured_speed > (uint16_t)(PWM_TO_SP_THRESHOLD / SPEED_MEASUREMENT_FACTOR)) && (drive_mode == PWM_MODE))
    {
        PWM_TIMER_PERIOD_SET(U16_TSECT_OFF);
        drive_mode = SP_MODE;
    }
    if((measured_speed < (uint16_t)(SP_TO_PWM_THRESHOLD / SPEED_MEASUREMENT_FACTOR)) && (drive_mode == SP_MODE))
    {
        PWM_TIMER_PERIOD_SET(PWM_PERIOD);
        PWM_CNT_RESET();
        drive_mode = PWM_MODE;
    }
}

static inline void __Clock_Switch(void)
{
    if((timerPeriod < CONVERT_ERPM_TO_STMR(LOW_TO_HIGH_SP_TH, DIV_LOW_SPEED)) && (low_speed == true))
    {
        LOW_SPEED_DISABLE();
        timerPeriod <<= DIV_SHIFT;
        integrator <<=  DIV_SHIFT;
        low_speed = false;
        SECTOR_TIMER_COUNTER_SET(0);
        CAPTURE_TIMER_COUNTER_SET(0);
    }
    if((timerPeriod > CONVERT_ERPM_TO_STMR(HIGH_TO_LOW_SP_TH, 1)) && (low_speed == false))
    {
        LOW_SPEED_ENABLE();
        timerPeriod >>= DIV_SHIFT;
        integrator >>= DIV_SHIFT;
        low_speed = true;
        SECTOR_TIMER_COUNTER_SET(0);
        CAPTURE_TIMER_COUNTER_SET(0);
    }
}

static inline void  __Sector_Changer(void)
{
    CAPTURE_TIMER_COUNTER_SET(CAPTURE_CNT_RESET); // ISR handling delay
    uint16_t capValue = CAPTURE_TIMER_PERIOD_GET(); CAPTURE_TIMER_PERIOD_SET(CAPTURE_PER_RESET); 
    if(status_running == true)
    {
        __Drive(DRIVE_TABLE[position]);
        uint16_t per = PWM_PERIOD;
        if(SINGLE_PULSE_MODE)
        {
            __PWM_SP_Switch();
            if(drive_mode == SP_MODE)
            {
                if(!(position & 1))
                    PWM_CNT_RESET();
                per = SECTOR_TIMER_PERIOD_GET() << PERIOD_SHIFT;
            }
		}
        if((HALL_ENABLED) && (hall_enabled))
        {
            HALL_MASK_SET(HALL_MASK_TABLE[position]);
            HALL_INV_SET(HALL_INV_TABLE[position], HALL_INV_MASK); /* hall pins are inverted alternatively */
        }
        else
        {
            COMP_MUX_SET(CMP_MUX_TABLE[position]);
            COMP_INVERT(CMP_INV_MASK);  /* comparator's output is inverted alternatively */
        }
        position++; if(position == MAX_POSITION) position = 1;
        if((DRIVE_FORCED == false) && (ONE_PHASE_CONDITION))
        {
            uint16_t setValue;
            if((HALL_ENABLED) && (hall_enabled))
                setValue = __Phase_Advance(MOTOR_PHASE_ADVANCE + HALL_MISALIGNMENT, timerPeriod);
            else
                setValue = __Phase_Advance(MOTOR_PHASE_ADVANCE + 30.0, timerPeriod) + CONVERT_US_TO_CLKS(BOARD_PHASE_RC_DELAY);     
            int24_t deltaValue = (int24_t)capValue - (int24_t)setValue;

            uint24_t tmp = (uint24_t)integrator + (deltaValue >> 4);
            if(tmp > U16_TSECT_OFF) integrator = U16_TSECT_OFF;
            else                    integrator = tmp;

            tmp = (uint24_t)integrator + (deltaValue >> 2);
            if(tmp > U16_TSECT_OFF) timerPeriod = U16_TSECT_OFF;
            else                    timerPeriod = tmp;

            if(STALL_DETECTION_ENABLED)
            {
                if((timerPeriod < CONVERT_ERPM_TO_STMR(STALL_MAXIMUM_ERPM, 1)) && (low_speed == false))
                    __Motor_StallHandler(STALL_TOO_FAST);
                if(capValue == U16_TSECT_OFF)
                    __Motor_StallHandler(STALL_TOO_LATE);
            }
            if((LOW_SPEED_MODE) || (HALL_ENABLED)) __Clock_Switch();
            SECTOR_TIMER_PERIOD_SET(timerPeriod);
        }
        PWM_TIMER_DCY_SET(fmul_FP16xU16(actual_amplitude, per));
        __Speed_Count();
    }
}

static inline void __Align(void)
{
    __Drive(DRIVE_OFF);
    PRECISE_DELAY_MS(5);
    __Drive(DRIVE_ALIGN);
    PRECISE_DELAY_MS(MOTOR_ALIGNMENT_DURATION);
    position = 1;
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
    if(status_running == false)
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
    if(HALL_ENABLED)
        HALL_ENABLE();
    else
        HALL_DISABLE();
}


motor_status_t Motor_StatusGet(void)
{
    motor_status_t  retval = status_events;
    status_events = 0;
    if(status_running == true)
        retval |= MOTOR_RUNNING;
    else
        retval |= MOTOR_IDLE;
    return retval;
}


uint32_t Motor_ErpmGet(void)
{
    return (uint32_t)(SPEED_MEASUREMENT_FACTOR) * (uint32_t)__Speed_Get();
}


void Motor_CommandSet(uint16_t ref)
{
    if(command_enabled)
    {
        if(REGULATOR_SPEED_EN == false) ATOMIC_COPY(target_amplitude, ref);
        else                            ATOMIC_COPY(target_speed, ref);
    }
}


uint16_t  Motor_AmplitudeGet(void)
{
    uint16_t retval;
    ATOMIC_COPY(retval, actual_amplitude);
    return retval;
}


void Motor_Start(uint16_t vbus_adc, motor_dir_t dir)
{
    if(status_running == true)
        return;  /* already running */
    __Speed_Reset();
    if(vbus_adc < VOLTAGE_TO_ADC(MOTOR_STARTUP_CURRENT * (MOTOR_RPP + 2*BOARD_MOSFET_RDSON + CURRENT_SHUNT_RESISTANCE)))
        status_events |= MOTOR_EVENT_UV;
    else
    {
        uint16_t start_amp = (uint16_t)(MOTOR_STARTUP_CURRENT * (float)FLOAT_TO_FIXP16(1.0) * (MOTOR_RPP + 2*BOARD_MOSFET_RDSON + CURRENT_SHUNT_RESISTANCE) / ADC_TO_VOLTAGE(vbus_adc));
        ATOMIC_COPY(target_amplitude, start_amp);
        ATOMIC_COPY(actual_amplitude, start_amp);
        uint16_t initial_sector;
        if(LOW_SPEED_MODE == true)
        {
            LOW_SPEED_ENABLE();
            low_speed = true;
            initial_sector = CONVERT_ERPM_TO_STMR(MOTOR_INITIAL_SPEED, DIV_LOW_SPEED);
        }
        else
        {
            LOW_SPEED_DISABLE();
            low_speed = false;
            initial_sector = CONVERT_ERPM_TO_STMR(MOTOR_INITIAL_SPEED, 1);
        }
        direction = dir;
        SECTOR_TIMER_COUNTER_SET(0);
        CAPTURE_TIMER_COUNTER_SET(0);
        SECTOR_TIMER_PERIOD_SET(initial_sector);
        CAPTURE_TIMER_PERIOD_SET(initial_sector);
        PWM_TIMER_PERIOD_SET(PWM_PERIOD);
        PWM_TIMER_DCY_SET(fmul_FP16xU16(actual_amplitude, PWM_PERIOD));
        timerPeriod = initial_sector;
        integrator = initial_sector;
        __Motor_StallHandler(STALL_NONE); /* clear any previous stall flag */
        status_running = true;
        drive_mode = PWM_MODE;
        if(HALL_ENABLED) hall_enabled = true;
        else             hall_enabled = false;
        __Align();
        if(REGULATOR_SPEED_EN == true)
        {
            __Speed_Control(true); /* initialize speed regulator */
        }
        if(FAULT_COMPARATOR_EN == true)
        {
            CURRENT_TRIP_SetInterruptHandler(__Current_Trip_Handler);
        }
        SECTOR_TIMER_START();

        if(MOTOR_STARTUP_TIME != -1)
        {
            PRECISE_DELAY_MS(MOTOR_STARTUP_TIME);
            command_enabled = true;
        }
    }
}


void  Motor_Fault(motor_fault_t event)
{
    if(status_running == false)
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
    return FLOAT_TO_FIXP16(1.0);
}

/* this function has to be called once every 1 ms, on interrupt context */
void  Motor_TimeTick(void)
{
    Analog_Handler();
    if(status_running == true)
    {
        bool new_speed = __Speed_Base();
        if(command_enabled)
        {
            if((REGULATOR_SPEED_EN) && (new_speed))
                __Speed_Control(false);
            else
                __OpenLoop_Control();
        }
    }
}
