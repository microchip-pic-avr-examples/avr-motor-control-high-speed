/*
© [2025] Microchip Technology Inc. and its subsidiaries.

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

static volatile motor_status_t motor_state, motor_events;
static volatile button_state_t button_state = BUTTON_IDLE;
static volatile led_ctrl_t     led_state = LED_OFF;

static void PrintEndl(void)
{
    printf("\n\r");
}


static void Periodic_MainHandler1(void)
{
    uint32_t erpm  = SPEED_MEASUREMENT_CONSTANT * Motor_ErpmGet();
    uint16_t amp   = Motor_AmplitudeGet();
    uint8_t  pot   = ADC_TO_PERCENT(Analog_Get(ID_POT)) + 0.5;
    uint32_t vbus  = ADC_TO_VOLTAGE(Analog_Get(ID_VBUS));
    int16_t  crt   = ADC_TO_CURRENT(Analog_Get(ID_CRT));
    int16_t  ibus  = (int16_t)((int32_t)crt * (uint32_t)amp / (uint32_t)Motor_MaxAmpGet());
    char *mstate   = (motor_state == MOTOR_RUNNING)? "run":"off";

    PrintEndl(); printf("Pot:%03u%% Ampl:%05u e-rpm:%06lu Vbus:%06lumV Ibus:%05dmA Imotor:%05dmA Motor:%s", pot, amp, erpm, vbus, ibus, crt, mstate);
}

static void Periodic_MainHandler2(void)
{
    uint16_t pot = Analog_Get(ID_POT);
    Motor_AmplitudeSet(SCALE(pot, Analog_MaxGet(), Motor_MaxAmpGet()));
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
    const char *buildString = "\n\rThis build was compiled at " __DATE__ ", " __TIME__;
    const char *boardString = "\n\rBoard Configuration: " __BOARD_STRING__;
    const char *platformString = "\n\rMCU Configuration: " __PLATFORM_STRING__;

    swtimer_data_t tm1, tm2, ti;
    
    SW_TIMER_CB_REGISTER(SwTimer_Tick);
    Analog_Initialize();
    PRECISE_DELAY_MS(3000);

    Motor_Initialize();

    SwTimer_Start(SwTimer_IntrAdd(&ti,     1, Periodic_IntHandler));
    SwTimer_Start(SwTimer_MainAdd(&tm1, 1000, Periodic_MainHandler1));
    SwTimer_Start(SwTimer_MainAdd(&tm2,   50, Periodic_MainHandler2));

    Analog_EmergencyStop_Register(ID_VBUS, Motor_Fault, VOLTAGE_TO_ADC(ADC_VBUS_TRIP),    MOTOR_FAULT_OVERVOLTAGE);
    Analog_EmergencyStop_Register(ID_CRT,  Motor_Fault, CURRENT_TO_ADC(ADC_CURRENT_TRIP), MOTOR_FAULT_OVERCURRENT);

    PrintEndl(); printf("%s%s%s", buildString, boardString, platformString);
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
                printf(" Motor Starting");
                Motor_Start(Analog_Get(ID_VBUS));
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

