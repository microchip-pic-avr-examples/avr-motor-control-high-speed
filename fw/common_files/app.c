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

#include <stdio.h>  /* for printf() */
#include "motor.h"
#include "conversion_macros.h"
#include "sw_timer.h"
#include "precise_delay.h"
#include "analog.h"
#include "button_led.h"
#include "config.h"
#include "mcc_mapping.h"
#include "pwm_in.h"

static volatile motor_status_t motor_state, motor_events;
static volatile button_state_t button_state = BUTTON_IDLE;
static volatile led_ctrl_t     led_state = LED_OFF;

static void PrintEndl(void)
{
    printf("\n\r");
}

static void Periodic_MainHandler1(void)
{
    uint16_t ipwm = IPWM_Read();
    if(ipwm != 0)
        ipwm = (uint16_t)SCALE_FULL(ipwm, IPWM_Min(), IPWM_Max(), 0, 100);

    uint32_t erpm  = Motor_ErpmGet();
    uint16_t amp   = Motor_AmplitudeGet();
    uint8_t  pot   = ADC_TO_PERCENT(Analog_Get(ID_POT)) + 0.5;
    uint32_t vbus  = ADC_TO_VOLTAGE(Analog_Get(ID_VBUS));
    int16_t  crt   = ADC_TO_CURRENT(Analog_Get(ID_CRT), Analog_Get(ID_REF));
    int16_t  ibus  = (int16_t)((int32_t)crt * (uint32_t)amp / (uint32_t)Motor_MaxAmpGet());
    char *mstate   = (motor_state == MOTOR_RUNNING)? "run":"off";
    PrintEndl(); printf("PwmIn:%03u%% Pot:%03u%% Ampl:%05u e-rpm:%06lu Vbus:%06lumV Ibus:%05dmA Imotor:%05dmA Motor:%s", ipwm, pot, amp, erpm, vbus, ibus, crt, mstate);
}

static void Periodic_MainHandler2(void)
{
    const uint16_t SPEED_MAX = (uint16_t)(REGULATOR_MAX_SPEED/SPEED_MEASUREMENT_FACTOR);
    const uint16_t SPEED_MIN = (uint16_t)(REGULATOR_MIN_SPEED/SPEED_MEASUREMENT_FACTOR);
    uint16_t pot, in, imax, imin, omax, omin;
    uint16_t ipwm = IPWM_Read();
    if(ipwm == 0)
        pot = Analog_Get(ID_POT);

    if(REGULATOR_SPEED_EN == true)
    {
        if(ipwm != 0) {in = ipwm; imin = IPWM_Min(); imax = IPWM_Max();   omin = SPEED_MIN; omax = SPEED_MAX;}
        else          {in = pot;  imin = 0;          imax = Analog_Max(); omin = SPEED_MIN; omax = SPEED_MAX;}
    }
    else
    {
        if(ipwm != 0) {in = ipwm; imin = IPWM_Min(); imax = IPWM_Max();   omin = 0;         omax = Motor_MaxAmpGet();}
        else          {in = pot;  imin = 0;          imax = Analog_Max(); omin = 0;         omax = Motor_MaxAmpGet();}
    }
    uint16_t reference = SCALE_FULL(in, imin, imax, omin, omax);  /* reference: either speed or amplitude */
    Motor_CommandSet(reference);
}

/* this handler is called on interrupt context every 1 ms */
static void Periodic_IntHandler(void)
{
    Motor_TimeTick();
    motor_status_t ms = Motor_StatusGet();
    button_state_t bs = ButtonGet();
    if(bs != BUTTON_IDLE)
        button_state = bs;
    motor_state = ms;
    motor_events |= (ms & MOTOR_ERROR_FLAGS);
    
    if(motor_events)
        led_state = LED_BLINK;
    else
    {
        if(ms & MOTOR_RUNNING)
            led_state = LED_ON;
        else
            led_state = LED_OFF;
    }
    LedControl(led_state);
}

void app(void)
{
    const char *buildString    = "\n\rThis build was compiled at " __DATE__ ", " __TIME__;
    const char *platformString = "\n\rMCU Configuration: " __CPU_STRING__;

    swtimer_data_t tm1, tm2, ti;
    
    SW_TIMER_CB_REGISTER(SwTimer_Tick);
    Analog_Initialize();
    IPWM_Initialize();
    PRECISE_DELAY_MS(3000);

    Motor_Initialize();

    SwTimer_Start(SwTimer_IntrAdd(&ti,     1, Periodic_IntHandler));
    SwTimer_Start(SwTimer_MainAdd(&tm1, 1000, Periodic_MainHandler1));
    SwTimer_Start(SwTimer_MainAdd(&tm2,   50, Periodic_MainHandler2));
    
    PRECISE_DELAY_MS(1000); /* delay required for analog engine to perform measurements */
    
    Analog_EmergencyStop_Register(ID_VBUS, Motor_Fault, VOLTAGE_TO_ADC(ADC_VBUS_TRIP),                         MOTOR_FAULT_OVERVOLTAGE);
    Analog_EmergencyStop_Register(ID_CRT,  Motor_Fault, CURRENT_TO_ADC(ADC_CURRENT_TRIP) + Analog_Get(ID_REF), MOTOR_FAULT_OVERCURRENT);

    PrintEndl(); printf("%s%s", buildString, platformString);
    PrintEndl(); printf("Motor Demo App Started");
    PrintEndl(); printf("Short-press button to start / stop motor");
    PrintEndl(); printf("Long-press button to restart the board any time");
    PrintEndl();
    
    while(1)
    {
        if(motor_events)
        {
            PrintEndl();
            if(motor_events & MOTOR_EVENT_STALL)
                printf("Motor Stall");
            if(motor_events & MOTOR_EVENT_FAULT)
                printf("Motor Comparator OverCurrent");
            if(motor_events & MOTOR_EVENT_OC)
                printf("Motor ADC OverCurrent");
            if(motor_events & MOTOR_EVENT_OV)
                printf("Motor ADC OverVoltage");
            if(motor_events & MOTOR_EVENT_UV)
                printf("Supply UnderVoltage");
            motor_events = 0;
        }
        
        if(button_state == BUTTON_SHORT_PRESS)
        {
            button_state = BUTTON_IDLE;
            PrintEndl();
            printf("Button Short-Press");
            if(motor_state & MOTOR_RUNNING)
            {
                printf(" Motor Stopping");
                Motor_Stop();
            }
            else
            {
                static motor_dir_t direction = DIR_CW;
                printf(" Motor Starting %s",(direction == DIR_CW)? "CW":"CCW");
                Motor_Start(Analog_Get(ID_VBUS), direction);
                if(direction == DIR_CW) direction = DIR_CCW;
                else                    direction = DIR_CW;
            }
        }
        
        if(button_state == BUTTON_LONG_PRESS)
        {
            button_state = BUTTON_IDLE;
            PrintEndl(); printf("Button Long-Press");
            if(motor_state & MOTOR_RUNNING)
            {
                printf(" Motor Stopping");
                Motor_Stop();
            }
            PrintEndl(); printf("Restarting...");
            PRECISE_DELAY_MS(100);
            System_Reset_Command();
        }
        PRECISE_DELAY_MS(1);
    }
}

