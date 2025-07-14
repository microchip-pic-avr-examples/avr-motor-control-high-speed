#ifndef MCC_MAPPING_H
#define MCC_MAPPING_H

#include <stdint.h>
#include <stdbool.h>

#include "mcc_generated_files/system/system.h"

#define __CPU_STRING__                  "ATmega4809"
#define DEBUG_BUFF_SIZE                 100         /* This has to be an even number */

/* BEMF comparator pins */
#define CMP_MUX_A    AC_MUXPOS_PIN0_gc // PD2
#define CMP_MUX_B    AC_MUXPOS_PIN1_gc // PD4
#define CMP_MUX_C    AC_MUXPOS_PIN2_gc // PD6
#define CMP_MUX_N    AC_MUXNEG_PIN2_gc // PD7

/* BEMF comparator APIs */
static void AC0_MuxSet(uint8_t mux_ctrl) __attribute__((unused));
static void AC0_MuxSet(uint8_t mux_ctrl){    AC0.MUXCTRLA = mux_ctrl;}
#define COMP_MUX_SET               AC0_MuxSet
static void AC0_Invert(bool config)  __attribute__((unused));
static void AC0_Invert(bool config){if(config) AC0.MUXCTRLA |=  AC_INVERT_bm; else AC0.MUXCTRLA &= ~AC_INVERT_bm;}
#define COMP_INVERT                AC0_Invert

/* external comparator - fault trip */
#define FAULT_CONTROL                       PORTC.PIN7CTRL
#define FAULT_DISABLE                       (PORT_PULLUPEN_bm | PORT_ISC_INTDISABLE_gc)
#define CURRENT_TRIP_SetInterruptHandler    FAULT_INPUT_SetInterruptHandler
#define COMP_EDGE_RISING                    (PORT_PULLUPEN_bm | PORT_ISC_RISING_gc)
#define COMP_EDGE_FALLING                   (PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc)
#define FAULT_COMPARATOR_EDGE               false /* true - on rising edge  | false - on falling edge */
#define CURRENT_TRIP_LEVEL_SET(X)           /* unused on Mega, external comparator */
#define AC_REF_DAC_MAX                      0 /* dummy value */

#define PWM_PERIOD                 256UL

/* pins used for PWM/GPIO motor drive */
#define DRIVE_LPORT                PORTA
#define DRIVE_AH                   PIN0_bm
#define DRIVE_BH                   PIN1_bm
#define DRIVE_CH                   PIN2_bm
#define DRIVE_AL                   PIN3_bm
#define DRIVE_BL                   PIN4_bm
#define DRIVE_CL                   PIN5_bm

#define DRIVE_LOW(X)               do{DRIVE_LPORT.OUT = (X);}while(0) /* affects the unused 2 bits of the port */

/* timer used to generate PWM and sample comparator */
#define PWM_TIMER_DCY_SET_A        TCA0_Compare0BufferSet
#define PWM_TIMER_DCY_SET_B        TCA0_Compare1BufferSet
#define PWM_TIMER_DCY_SET_C        TCA0_Compare2BufferSet

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
#define CRT_P_ADC_PIN           ADC_MUXPOS_AIN0_gc  // PD0
#define VBUS_ADC_PIN            ADC_MUXPOS_AIN8_gc  // PE0
#define POT_ADC_PIN             ADC_MUXPOS_AIN10_gc // PE2

/* ADC APIs */
#define ADC_MUX_SET             ADC0_ChannelSelect
#define ADC_CONV_START          ADC0_ConversionStart
#define ADC_RESULT_GET          ADC0_ConversionResultGet
#define ADC_RESOLUTION_GET      ADC0_ResolutionGet
#define ADC_CB_REGISTER         TCA0_OverflowCallbackRegister
#define ADC_NO_CONV_PROGRESS    ADC0_IsConversionDone

#define System_Reset_Command    RSTCTRL_reset

/* Button polarity */
#define BUTTON_ACTIVE           0

/* PWM Input capture */
#define PWM_IN_PIN_REGISTER     PWM_IN_SetInterruptHandler
#define PWM_IN_PIN_READ         PWM_IN_GetValue
#define PWM_IN_TMR_REGISTER     TCB2_CaptureCallbackRegister
#define PWM_IN_TMR_CLEAR()      TCB2_CounterSet(0)
#define PWM_IN_TMR_READ         TCB2_CounterGet


#endif /* MCC_MAPPING_H */

