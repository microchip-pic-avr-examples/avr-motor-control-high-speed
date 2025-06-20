#ifndef MCC_MAPPING_H
#define MCC_MAPPING_H

#include <stdint.h>
#include <stdbool.h>

#include "mcc_generated_files/system/system.h"

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
#define FAULT_CONTROL                       AC1.INTCTRL
#define FAULT_DISABLE                       0
#define CURRENT_TRIP_SetInterruptHandler    AC1_CallbackRegister
#define COMP_EDGE_RISING                    (AC_INTMODE_NORMAL_POSEDGE_gc | AC_CMP_bm) 
#define COMP_EDGE_FALLING                   (AC_INTMODE_NORMAL_NEGEDGE_gc | AC_CMP_bm)
#define FAULT_COMPARATOR_EDGE               true /* true - on rising edge  | false - on falling edge */
#define CURRENT_TRIP_LEVEL_SET              AC1_DACRefValueSet
#define AC_REF_DAC_MAX                      255

#define PWM_PERIOD                 256UL

/* pins used for PWM/GPIO motor drive */
#define DRIVE_LPORT
#define DRIVE_AH                   WEX_PGMOUT0_bm
#define DRIVE_BH                   WEX_PGMOUT2_bm
#define DRIVE_CH                   WEX_PGMOUT4_bm
#define DRIVE_AL                   WEX_PGMOUT1_bm
#define DRIVE_BL                   WEX_PGMOUT3_bm
#define DRIVE_CL                   WEX_PGMOUT5_bm

#define DRIVE_LOW(X)               WEX0_PatternGenerationOutputSet(X) /* affects the unused 2 bits of the port */

/* timer used to generate PWM and sample comparator */
#define PWM_TIMER_DCY_SET_A        TCE0_PWM_BufferedDutyCycle0Set
#define PWM_TIMER_DCY_SET_B        TCE0_PWM_BufferedDutyCycle1Set
#define PWM_TIMER_DCY_SET_C        TCE0_PWM_BufferedDutyCycle2Set

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

/* periodic 1ms software timer */
#define SW_TIMER_CB_REGISTER       RTC_SetPITIsrCallback
#define SW_TIMER_PERIOD            (970) /* us */

/* ADC pins definitions */
#define CRT_P_ADC_PIN           ADC_MUXPOS_AIN3_gc  // PD3
#define VBUS_ADC_PIN            ADC_MUXPOS_AIN20_gc // PF4
#define POT_ADC_PIN             ADC_MUXPOS_AIN1_gc  // PD1

/* ADC APIs */
#define ADC_CONVERSION_START    ADC0_ConversionStart
#define ADC_MUX_SET             ADC0_ChannelSelect
#define ADC_IS_DONE             ADC0_IsConversionDone
#define ADC_RESULT_GET          ADC0_ConversionResultGet
#define ADC_RESOLUTION_GET      ADC0_ResolutionGet
#define ADC_CB_REGISTER(X)      do{ADC0_ResultReadyCallbackRegister(X); ADC0_ResultReadyInterruptEnable();}while(0)


static void System_Reset_Command(void)  __attribute__ ((unused));
static void System_Reset_Command(void)  { _PROTECTED_WRITE(RSTCTRL.SWRR, RSTCTRL_SWRE_bm);  while(true);}

/* Button polarity */
#define BUTTON_ACTIVE           0


#endif /* MCC_MAPPING_H */

