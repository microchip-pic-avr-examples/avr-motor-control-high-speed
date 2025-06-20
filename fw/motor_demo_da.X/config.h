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


#ifndef CONFIG_H
#define	CONFIG_H

#define __BOARD_STRING__                "LowVoltage MPPB"
#define __PLATFORM_STRING__             "AVR128DA48"
#define DEBUG_BUFF_SIZE                 15000  /* this has to be an even number */

/* analog thresholds */
#define VIRTUAL_POTENTIOMETER           (0.00)       /* value: 0.1 ... 100.0 |  set to 0.00 for the real potentiometer usage */
#define ADC_IIR_FILTER                  true         /* smoothing filter on analog adc functions: pot, vbus, current */

/* board specific settings - MPPB */
#define CURRENT_SHUNT_RESISTANCE        (0.01)       /* resistance in Ohm of the current shunt */
#define CURRENT_AMPLIFIER_GAIN          (7.5)
#define CURRENT_AMPLIFIER_OFFSET        (1650.0)     /* mV - typical offset is Vref/2 = 1650mV  */
#define VBUS_DIVIDER                    (16.0)
#define ANALOG_REFERENCE                (3300.0)     /* millivolt */
#define ADC_VBUS_TRIP                   (51000.0)    /* mV - vbus trip level */
#define ADC_CURRENT_TRIP                (7000.0)     /* mA - adc current trip level */
#define COMPARATOR_CURRENT_TRIP         (8000.0)     /* mA - comparator trip level - not used on external-comp configurations */
#define FAULT_COMPARATOR_EN             false

/* motor specific settings */
/* ACT42BLF01:  supply 24V, 3A limit */
#define MOTOR_STARTUP_CURRENT           (2500.0)     /* milliamperes, initial alignment current pulse, may be higher than over-current protection */
#define MOTOR_RPP                       (2.6)        /* ohms - motor resistance measured phase-to-phase */
#define MOTOR_AMPRAMP_STEP_INTERVAL     (15)         /* amplitude ramp step interval: expressed milliseconds, time passed between two amplitude steps, 10 for aggresive ramp, 100 for soft ramp */
#define MOTOR_ALIGNMENT_DURATION        (10)         /* milliseconds */
#define MOTOR_MAXIMUM_ERPM              (50000.0)    /* e-rpm */
#define STALL_THRS                      10           /* stall detection tolerance: higher number - more tolerant to perturbances. but slower detection */

#define MOTOR_STARTUP_TIME              (1000)        /* milliseconds until POT is used | '-1' means potentiometer is ignored, both emulated and real */
#define MOTOR_FORCED                    false         /* setting to 'true' makes the motor running with no BEMF sensing, only blind drive */

#endif	/* CONFIG_H */


