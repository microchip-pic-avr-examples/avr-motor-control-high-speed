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

/* Analog module settings */
#define ADC_IIR_FILTER                  true         /* Smoothing filter on ADC functions: POT, VBUS, current */

/* PWM-In settings */
#define PWM_IN_PERIOD                   (20.0)       /* ms */
#define PWM_IN_MAX_DCY                  ( 2.0)       /* ms */
#define PWM_IN_MIN_DCY                  ( 1.0)       /* ms */

/* Drive mode settings */
#define MOTOR_FORCED                    false        /* Setting to 'true' makes the motor run with no BEMF sensing, only blind drive */

/* Board specific settings - MPPB */
#define CURRENT_SHUNT_RESISTANCE        (0.01)       /* Resistance in ohm of the current shunt */
#define CURRENT_AMPLIFIER_GAIN          (22.5)
#define CURRENT_AMPLIFIER_OFFSET        (1650.0)     /* mV - Typical offset is VREF/2 = 1650 mV  */
#define VBUS_DIVIDER                    (16.0)
#define ANALOG_REFERENCE                (3300.0)     /* mV */
#define ADC_VBUS_TRIP                   (51000.0)    /* mV - VBUS trip level */
#define ADC_CURRENT_TRIP                (7000.0)     /* mA - ADC current trip level */
#define COMPARATOR_CURRENT_TRIP         (7333.0)     /* mA - Comparator trip level - not used on external-comparator configurations */
#define FAULT_COMPARATOR_EN             true

/* Motor-specific settings */
/* ACT42BLF01:  supply 24V, 3A limit */
#define MOTOR_PHASE_ADVANCE             (15.0)       /* Phase advance 0.0 ... 30.0 electrical degrees */
#define MOTOR_STARTUP_CURRENT           (2500.0)     /* mA - Initial alignment current pulse may be higher than overcurrent protection */
#define MOTOR_RPP                       (2.6)        /* ohms - Motor resistance measured phase-to-phase */
#define MOTOR_AMPRAMP_STEP_INTERVAL     (15)         /* Amplitude ramp step interval: expressed in milliseconds, time passed between two amplitude steps, 10 for aggresive ramp, 100 for soft ramp */
#define MOTOR_ALIGNMENT_DURATION        (10)         /* ms */
#define MOTOR_MAXIMUM_ERPM              (50000.0)    /* e-RPM */
#define MOTOR_SPEED_REGULATOR_EN        true         /* Setting to 'true' enables speed control in Closed Loop, setting to 'false' enables amplitude control in Open Loop */
#define REGULATOR_MAX_SPEED             (15000.0)    /* e-RPM */
#define REGULATOR_MIN_SPEED             ( 5000.0)    /* e-RPM */
#define REGULATOR_PI_KP                 (0.1)        /* PI control loop proportional coefficient */
#define REGULATOR_PI_KI                 (0.1)        /* PI control loop integral coefficient */
#define STALL_DETECTION_THRESHOLD       (200)        /* Stall detection tolerance: higher number - more tolerant to perturbances, but slower detection */
#define STALL_DETECTION_DISABLED        false        /* Setting to 'true' disables the stall mechanism, setting to 'false' enables the stall mechanism */
#define MOTOR_STARTUP_TIME              (1000)       /* ms until POT is used | '-1' means potentiometer is ignored, whether it is real or emulated */

#endif	/* CONFIG_H */


