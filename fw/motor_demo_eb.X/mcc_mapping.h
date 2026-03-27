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

#ifndef MCC_MAPPING_H
#define MCC_MAPPING_H

#include <stdint.h>
#include <stdbool.h>

#include "mcc_generated_files/system/system.h"

#define __CPU_STRING__                  "AVR16EB32"
#define DEBUG_BUFF_SIZE                 100         /* This has to be an even number */

/* BEMF comparator pins */
#define CMP_MUX_A    AC_MUXPOS_AINP5_gc // PD4
#define CMP_MUX_B    AC_MUXPOS_AINP6_gc // PD5
#define CMP_MUX_C    AC_MUXPOS_AINP3_gc // PD6
#define CMP_MUX_N    AC_MUXNEG_AINN1_gc // PD0

/* BEMF comparator APIs */
#define COMP_MUX_SET               AC0_MuxSet
static void AC0_Invert(bool)  __attribute__((unused));
static void AC0_Invert(bool config) { if(config) AC0.MUXCTRL |=  AC_INVERT_bm; else AC0.MUXCTRL &= ~AC_INVERT_bm;}
#define COMP_INVERT                AC0_Invert

/* external/internal comparator - fault trip */
#define FAULT_CONTROL                       WEX0.FAULTCTRL
#define FAULT_DISABLE                       (WEX_FDDBD_bm | WEX_FDACT_NONE_gc)
#define CURRENT_TRIP_SetInterruptHandler(X) do{WEX0_SoftwareCommand(WEX_CMD_FAULTCLR_gc); WEX0_FaultDetectionAction(WEX_FDACT_LOW_gc); WEX0_FAULTIsrCallbackRegister(X);}while(0)
#define COMP_EDGE_RISING                    (WEX_FDDBD_bm | WEX_FDACT_NONE_gc)
#define COMP_EDGE_FALLING                   (WEX_FDDBD_bm | WEX_FDACT_NONE_gc)
#define FAULT_COMPARATOR_EDGE               true /* true - on rising edge  | false - on falling edge */
#define CURRENT_TRIP_LEVEL_SET              AC1_DACRefValueSet
#define AC_REF_DAC_MAX                      255

#define PWM_PERIOD                 511UL
#define DIV_SHIFT                  9    // 511 = 2 ** 9 - 1
#define DIV_LOW_SPEED              512UL

/* pins used for PWM/GPIO motor drive */
#define DRIVE_LPORT
#define DRIVE_AH                   WEX_PGMOUT0_bm
#define DRIVE_BH                   WEX_PGMOUT2_bm
#define DRIVE_CH                   WEX_PGMOUT4_bm
#define DRIVE_AL                   WEX_PGMOUT1_bm
#define DRIVE_BL                   WEX_PGMOUT3_bm
#define DRIVE_CL                   WEX_PGMOUT5_bm
#define DRIVE_PINS(X, Y)           do{WEX0.PGMOVR = 0xFF & ~(X); WEX0.PGMOUT = Y;}while(0)

/* timer used to generate PWM and sample comparator */
#define PWM_TIMER_DCY_SET(X)       do{\
                                      TCE0.CMP0BUF = (X);\
                                      TCE0.CMP1BUF = (X);\
                                      TCE0.CMP2BUF = (X);\
                                   }while(0)
#define PWM_TIMER_PERIOD_SET       TCE0_PeriodSet
#define PWM_TIMER_PERIOD_GET       TCE0_PeriodGet
#define PWM_CNT_RESET()            do{TCE0.CTRLESET = TCE_CMD_RESTART_gc; }while(0)

/* timer used to change sector */
#define SECTOR_TIMER_CB_REGISTER   TCB0_CaptureCallbackRegister
#define SECTOR_TIMER_START         TCB0_Start
#define SECTOR_TIMER_STOP          TCB0_Stop
#define SECTOR_TIMER_PERIOD_GET    TCB0_CaptureCompareRead
#define SECTOR_TIMER_PERIOD_SET    TCB0_CaptureCompareWrite
#define SECTOR_TIMER_COUNTER_GET   TCB0_Read
#define SECTOR_TIMER_COUNTER_SET   TCB0_Write
#define SECTOR_TIMER_FREQUENCY     (F_CPU)

/* timer used to capture comparator transition */
#define CAPTURE_TIMER_START        TCB1_Start
#define CAPTURE_TIMER_STOP         TCB1_Stop
#define CAPTURE_TIMER_PERIOD_GET   TCB1_CaptureCompareRead
#define CAPTURE_TIMER_PERIOD_SET   TCB1_CaptureCompareWrite
#define CAPTURE_TIMER_COUNTER_GET  TCB1_Read
#define CAPTURE_TIMER_COUNTER_SET  TCB1_Write

/* settings used based on motor speed */
#define LOW_SPEED_ENABLE()         do{\
                                   EVSYS.CHANNEL2 = EVSYS_CHANNEL_TCE0_OVF_gc;\
                                   uint8_t temp = (TCB0.CTRLA & ~TCB_CLKSEL_gm)| (TCB_CLKSEL_EVENT_gc & TCB_CLKSEL_gm); TCB0.CTRLA = temp;\
                                   temp = (TCB1.CTRLA & ~TCB_CLKSEL_gm)| (TCB_CLKSEL_EVENT_gc & TCB_CLKSEL_gm); TCB1.CTRLA = temp;\
                                   TCB0.EVCTRL = TCB_CAPTEI_bm;\
                                   }while(0)               
#define LOW_SPEED_DISABLE()        do{\
                                   EVSYS.CHANNEL2 = EVSYS_CHANNEL_OFF_gc;\
                                   uint8_t temp = (TCB0.CTRLA & ~TCB_CLKSEL_gm)| (TCB_CLKSEL_DIV1_gc & TCB_CLKSEL_gm); TCB0.CTRLA = temp;\
                                   temp = (TCB1.CTRLA & ~TCB_CLKSEL_gm)| (TCB_CLKSEL_DIV1_gc & TCB_CLKSEL_gm); TCB1.CTRLA = temp;\
                                   TCB0.EVCTRL = 0;\
                                   }while(0)

/* periodic 1ms software timer */
#define SW_TIMER_CB_REGISTER       RTC_SetPITIsrCallback
#define SW_TIMER_PERIOD            (1260) /* us */

/* ADC pins definitions */
#define CRT_P_ADC_PIN           ADC_MUXPOS_AIN3_gc  // PD3
#define CRT_N_ADC_PIN           ADC_MUXPOS_AIN7_gc  // PD7
#define VBUS_ADC_PIN            ADC_MUXPOS_AIN20_gc // PF4
#define POT_ADC_PIN             ADC_MUXPOS_AIN1_gc  // PD1

/* ADC APIs */
#define ADC_MUX_SET             ADC0_ChannelSelect
#define ADC_CONV_START          ADC0_ConversionStart
#define ADC_RESULT_GET          ADC0_ConversionResultGet
#define ADC_RESOLUTION_GET      ADC0_ResolutionGet
#define ADC_NO_CONV_PROGRESS    ADC0_IsConversionDone


static void System_Reset_Command(void)  __attribute__ ((unused));
static void System_Reset_Command(void)  { _PROTECTED_WRITE(RSTCTRL.SWRR, RSTCTRL_SWRE_bm);  while(true);}

/* Button polarity */
#define BUTTON_ACTIVE           0

/* PWM Input capture */
#define PWM_IN_PIN_REGISTER     PWM_IN_SetInterruptHandler
#define PWM_IN_PIN_READ         PWM_IN_GetValue
#define PWM_IN_TMR_REGISTER     TCF0_OverflowCallbackRegister
#define PWM_IN_TMR_CLEAR()      TCF0_CounterSet(0)
#define PWM_IN_TMR_READ         (uint16_t)TCF0_CounterGet

/* HALL Sensored Functions */

#define HALL_PORT               PORTF
#define HALL_A_PIN              PIN1CTRL
#define HALL_B_PIN              PIN2CTRL
#define HALL_C_PIN              PIN3CTRL
#define HALL_ENABLE()           do{\
                                EVSYS.CHANNEL1 = EVSYS_CHANNEL_PORTF_EV0_gc;\
                                }while(0)      
#define HALL_DISABLE()          do{\
                                EVSYS.CHANNEL1 = EVSYS_CHANNEL_AC0_OUT_gc;\
                                }while(0)
#define HALL_MASK_A             PORT_EVGEN0SEL_PIN1_gc
#define HALL_MASK_B             PORT_EVGEN0SEL_PIN2_gc
#define HALL_MASK_C             PORT_EVGEN0SEL_PIN3_gc
#define HALL_INVERT             PORT_INVEN_bm
#define HALL_MASK_SET(X)        do{HALL_PORT.EVGENCTRLA = (X);}while(0)   
#define HALL_INV_SET(X, Y)      do{uint8_t _tmp = (Y); if((X) != NULL) *(X) = _tmp;}while(0)


#endif /* MCC_MAPPING_H */

