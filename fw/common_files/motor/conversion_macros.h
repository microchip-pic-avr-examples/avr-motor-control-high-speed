/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef CONVERSION_MACROS_H
#define	CONVERSION_MACROS_H

#include <stdint.h>
#include <util/atomic.h>
#include "analog.h"
#include "mcc_mapping.h"
#include "config.h"

#define ADC_MAX_SCALE                     (float)(Analog_MaxGet())
#define DAC_MAX_SCALE                     AC_REF_DAC_MAX

/* potentiometer conversion formulas to/from percents */
#define ADC_TO_PERCENT(X)                 ((float)(X) * 100.0 / ADC_MAX_SCALE)
#define PERCENT_TO_ADC(X)                 (uint16_t)((float)(X) * ADC_MAX_SCALE / 100.0 + 0.5)

/* voltage conversion formulas to/from millivolts */
#define ADC_TO_VOLTAGE(X)                 ((float)(X) * VBUS_DIVIDER * ANALOG_REFERENCE / ADC_MAX_SCALE)
#define VOLTAGE_TO_ADC(X)                 (uint16_t)((float)(X) * ADC_MAX_SCALE / (VBUS_DIVIDER * ANALOG_REFERENCE) + 0.5)

/* current conversion formulas to/from milliamperes */
#define ADC_TO_CURRENT(X)                 ( ((float)(X) * ANALOG_REFERENCE / ADC_MAX_SCALE - CURRENT_AMPLIFIER_OFFSET) / (CURRENT_AMPLIFIER_GAIN * CURRENT_SHUNT_RESISTANCE) )
#define CURRENT_TO_ADC(X)                 (uint16_t)( ((float)(X) * CURRENT_AMPLIFIER_GAIN * CURRENT_SHUNT_RESISTANCE + CURRENT_AMPLIFIER_OFFSET) * ADC_MAX_SCALE / ANALOG_REFERENCE + 0.5)

/* current conversion formulas to/from milliamperes - reference DAC */
#define ACREF_TO_CURRENT(X)               ( ((float)(X) * ANALOG_REFERENCE / DAC_MAX_SCALE - CURRENT_AMPLIFIER_OFFSET) / (CURRENT_AMPLIFIER_GAIN * CURRENT_SHUNT_RESISTANCE) )
#define CURRENT_TO_ACREF(X)               (uint8_t)( ((float)(X) * CURRENT_AMPLIFIER_GAIN * CURRENT_SHUNT_RESISTANCE + CURRENT_AMPLIFIER_OFFSET) * DAC_MAX_SCALE / ANALOG_REFERENCE + 0.5)

/* conversion macros from/into float e-rpm value into/from 16-bit sector timer value (60 sec in a minute, 6 sectors per rev) */
#define CONVERT_ERPM_TO_STMR(ERPM)        (uint16_t)(60.0 * (SECTOR_TIMER_FREQUENCY) / (6.0 * (ERPM)) - 0.5)
#define CONVERT_STMR_TO_ERPM(STMR)                  (60.0 * (SECTOR_TIMER_FREQUENCY) / (6.0 * (STMR + 1)))

typedef __int24  int24_t;
typedef __uint24 uint24_t;

typedef union
{
    struct
    {
        uint8_t L8;
        uint8_t H8;
    };
    uint16_t W16;
} split16_t;

typedef union
{
    struct
    {
        uint8_t   L;
        uint16_t  H;
    };
    uint24_t  W;
} split24_t;

typedef union
{
	struct
	{
		uint16_t L16;
		uint16_t H16;
	};
	uint32_t W32;
} split32_t;

typedef uint16_t fixp_t;

#define FLOAT_TO_FIXP(FLOAT)               (fixp_t)((FLOAT)*32768.0 + 0.5)
#define FIXP_TO_FLOAT(FIXP)                ((float)(FIXP)/32768.0)


#define MAXIMUM(A,B)                       (((A)>(B))?(A):(B))
#define MINIMUM(A,B)                       (((A)<(B))?(A):(B))
#define SATURATE(X, MIN, MAX)              (MINIMUM(MAX,MAXIMUM(MIN,X)))

/* 
 * {return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;}
 */
#define SCALE_ZERO(VAL,         IN_MAX,          OUT_MAX)     ((uint32_t)(VAL) * (uint32_t)(OUT_MAX) / (uint32_t)(IN_MAX))
#define SCALE_FULL(VAL, IN_MIN, IN_MAX, OUT_MIN, OUT_MAX)    (((uint32_t)(VAL) - (uint32_t)(IN_MIN)) * ((uint32_t)(OUT_MAX) - (uint32_t)(OUT_MIN)) / ((uint32_t)(IN_MAX) - (uint32_t)(IN_MIN)) + (uint32_t)OUT_MIN)


#define ATOMIC_COPY(DST_VAR, SRC_VAR)      do{ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {DST_VAR = SRC_VAR;}}while(0)

#define SPEED_MEASUREMENT_CONSTANT         (64)
#define SPEED_MEASUREMENT_BASE             (uint16_t)(1000000.0 * 60.0 / (6.0 * SW_TIMER_PERIOD * SPEED_MEASUREMENT_CONSTANT)) /* 60 sec in a minute, 6 sectors per electrical rev, 1,000,000 us in a second */


#endif	/* CONVERSION_MACROS_H */


