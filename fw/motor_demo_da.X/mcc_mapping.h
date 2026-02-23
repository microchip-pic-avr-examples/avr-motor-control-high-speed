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
#include "mcc_generated_files/reset/rstctrl.h"

#define __CPU_STRING__                  "AVR128DA48"
#define DEBUG_BUFF_SIZE                 12000        /* This has to be an even number */

/* BEMF comparator pins */
#define CMP_MUX_A    AC_MUXPOS_AINP3_gc // PD6
#define CMP_MUX_B    AC_MUXPOS_AINP0_gc // PD2
#define CMP_MUX_C    AC_MUXPOS_AINP2_gc // PD4
#define CMP_MUX_N    AC_MUXNEG_AINN2_gc // PD7

/* BEMF comparator APIs */
#define COMP_MUX_SET               AC1_MuxSet
static void AC1_Invert(bool config)  __attribute__((unused));
static void AC1_Invert(bool config){if(config) AC1.MUXCTRL |=  AC_INVERT_bm; else AC1.MUXCTRL &= ~AC_INVERT_bm;}
#define COMP_INVERT                AC1_Invert

/* external/internal comparator - fault trip */
#define FAULT_CONTROL                       AC0.INTCTRL
#define FAULT_DISABLE                       0
#define CURRENT_TRIP_SetInterruptHandler    AC0_CallbackRegister                    
#define COMP_EDGE_RISING                    (AC_INTMODE_NORMAL_POSEDGE_gc | AC_CMP_bm)
#define COMP_EDGE_FALLING                   (AC_INTMODE_NORMAL_NEGEDGE_gc | AC_CMP_bm)
#define FAULT_COMPARATOR_EDGE               true /* true - on rising edge  | false - on falling edge */
#define CURRENT_TRIP_LEVEL_SET              AC0_DACRefValueSet
#define AC_REF_DAC_MAX                      255

#define PWM_PERIOD                 613UL

/* pins used for PWM/GPIO motor drive */
#define DRIVE_LPORT                PORTB
#define DRIVE_AH                   TCA_SINGLE_CMP0EN_bm
#define DRIVE_BH                   TCA_SINGLE_CMP1EN_bm
#define DRIVE_CH                   TCA_SINGLE_CMP2EN_bm
#define DRIVE_AL                   PIN0_bm
#define DRIVE_BL                   PIN1_bm
#define DRIVE_CL                   PIN2_bm
#define DRIVE_HIGH_MASK            (TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_CMP1EN_bm | TCA_SINGLE_CMP2EN_bm)
#define DRIVE_PINS(X, Y)           do{uint8_t temp = (TCA0.SINGLE.CTRLB & ~DRIVE_HIGH_MASK) | ((X) & DRIVE_HIGH_MASK);\
                                   TCA0.SINGLE.CTRLB = temp;\
                                   DRIVE_LPORT.OUT = (Y);\
                                   }while(0)

/* timer used to generate PWM and sample comparator */
#define PWM_TIMER_DCY_SET(X)       do{\
                                   TCA0.SINGLE.CMP0BUF = (X);\
                                   TCA0.SINGLE.CMP1BUF = (X);\
                                   TCA0.SINGLE.CMP2BUF = (X);\
                                   }while(0)
#define PWM_TIMER_PERIOD_SET       TCA0_PeriodSet
#define PWM_TIMER_PERIOD_GET       TCA0_PeriodGet
#define PWM_CNT_RESET()            do{TCA0.SINGLE.CTRLESET = TCA_SINGLE_CMD_RESTART_gc; }while(0)

/* timer used to change sector */
#define SECTOR_TIMER_CB_REGISTER   TCB0_CaptureCallbackRegister
#define SECTOR_TIMER_START         TCB0_Start
#define SECTOR_TIMER_STOP          TCB0_Stop
#define SECTOR_TIMER_PERIOD_GET    TCB0_PeriodGet
#define SECTOR_TIMER_PERIOD_SET    TCB0_PeriodSet
#define SECTOR_TIMER_COUNTER_GET   TCB0_CounterGet
#define SECTOR_TIMER_COUNTER_SET   TCB0_CounterSet
#define SECTOR_TIMER_FREQUENCY     (F_CPU)

/* timer used to capture comparator transition */
#define CAPTURE_TIMER_START        TCB1_Start
#define CAPTURE_TIMER_STOP         TCB1_Stop
#define CAPTURE_TIMER_PERIOD_GET   TCB1_PeriodGet
#define CAPTURE_TIMER_PERIOD_SET   TCB1_PeriodSet
#define CAPTURE_TIMER_COUNTER_GET  TCB1_CounterGet
#define CAPTURE_TIMER_COUNTER_SET  TCB1_CounterSet

/* periodic 1ms software timer */
#define SW_TIMER_CB_REGISTER       RTC_SetPITIsrCallback
#define SW_TIMER_PERIOD            (970) /* us */

/* ADC pins definitions */
#define CRT_P_ADC_PIN           ADC_MUXPOS_AIN10_gc // PE2
#define CRT_N_ADC_PIN           ADC_MUXPOS_AIN8_gc  // PE0
#define VBUS_ADC_PIN            ADC_MUXPOS_AIN0_gc  // PD0
#define POT_ADC_PIN             ADC_MUXPOS_AIN1_gc  // PD1

/* ADC APIs */
#define ADC_MUX_SET             ADC0_ChannelSelect
#define ADC_CONV_START          ADC0_ConversionStart
#define ADC_RESULT_GET          ADC0_ConversionResultGet
#define ADC_RESOLUTION_GET      ADC0_ResolutionGet
#define ADC_NO_CONV_PROGRESS    ADC0_IsConversionDone

#define System_Reset_Command    RSTCTRL_SoftwareReset

/* Button polarity */
#define BUTTON_ACTIVE           0

/* PWM Input capture */
#define PWM_IN_PIN_REGISTER     PWM_IN_SetInterruptHandler
#define PWM_IN_PIN_READ         PWM_IN_GetValue
#define PWM_IN_TMR_REGISTER     TCB2_OverflowCallbackRegister
#define PWM_IN_TMR_CLEAR()      TCB2_CounterSet(0)
#define PWM_IN_TMR_READ         TCB2_CounterGet


#endif /* MCC_MAPPING_H */

