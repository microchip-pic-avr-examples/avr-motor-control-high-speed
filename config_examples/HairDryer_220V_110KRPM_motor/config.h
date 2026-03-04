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

#ifndef CONFIG_H
#define	CONFIG_H

/* Analog module settings */
#define ADC_IIR_FILTER                  true         /* Smoothing filter on ADC functions: POT, VBUS, current */

/* PWM-In settings */
#define PWM_IN_PERIOD                   (20.0)       /* ms */
#define PWM_IN_MAX_DCY                  ( 2.0)       /* ms */
#define PWM_IN_MIN_DCY                  ( 1.0)       /* ms */

/* Board specific settings - MPPB */
#define CURRENT_SHUNT_RESISTANCE        (0.01)       /* Resistance in ohm of the current shunt */
#define CURRENT_AMPLIFIER_GAIN          (7.5)
#define VBUS_DIVIDER                    (16.0)
#define ANALOG_REFERENCE                (3300.0)     /* mV */
#define ADC_VBUS_TRIP                   (51000.0)    /* mV - VBUS trip level */
#define ADC_CURRENT_TRIP                (15000.0)    /* mA - ADC current trip level */
#define COMPARATOR_CURRENT_TRIP         (20000.0)    /* mA - Comparator trip level - not used on external-comparator configurations */
#define FAULT_COMPARATOR_EN             false
#define BOARD_PHASE_RC_DELAY            (10.0)       /* microseconds - RC filter delay */
#define BOARD_MOSFET_RDSON              (0.004)      /* ohm - MOSFETs Rds-on resistance */

/* Motor-specific settings */
/* 220V AC 100W 110000RPM:  supply 50V, 1.5A limit */
#define MOTOR_PHASE_ADVANCE             (5.0)        /* Phase advance 0.0 ... 30.0 electrical degrees */
#define MOTOR_STARTUP_CURRENT           (800.0)      /* mA - Initial alignment current pulse may be higher than overcurrent protection */
#define MOTOR_RPP                       (50.0)       /* ohms - Motor resistance measured phase-to-phase */
#define MOTOR_OPEN_LOOP_RAMP            (0.0004)     /* Amplitude ramp steepness: step size per millisecond 0.00004 ... 1.0 */
#define MOTOR_ALIGNMENT_DURATION        (5)          /* ms */
#define MOTOR_STARTUP_TIME              (1000)       /* ms -  Delay until commands (POT or PWM-in) are accepted; '-1' makes commands to be ignored */
#define MOTOR_STATRUP_SPEED             (5000.0)     /* e-RPM - Specify the initial speed for fast motors */

/* Speed regulation specific settings */
#define REGULATOR_SPEED_EN              true         /* Setting to 'true' enables speed control in Closed Loop, setting to 'false' enables amplitude control in Open Loop */
#define REGULATOR_MAX_SPEED             (25000.0)    /* e-RPM target speed for 100% command */
#define REGULATOR_MIN_SPEED             (10000.0)    /* e-RPM target speed for   0% command */
#define REGULATOR_PI_KP                 (1.0)        /* PI speed control loop proportional coefficient */
#define REGULATOR_PI_KI                 (0.5)        /* PI speed control loop integral coefficient */
#define REGULATOR_PI_DT                 (20.0)       /* PI time step size [ms]; this parameter is also used for measurement of speed in open loop — minimum 10 ms */

/* Drive Algorithm settings */
#define DRIVE_FORCED                    false        /* Setting to 'true' runs the motor without BEMF sensing, only blind drive and no rotor synchronization, which could overheat the motor */
#define SINGLE_PULSE_MODE               false        /* Setting to 'true' enables the single pulse drive method, while setting to 'false' enables the PWM modulation drive method */
#define PWM_TO_SP_THRESHOLD             (120000.0)   /* e-RPM  PWM -> Single Pulse transition */
#define SP_TO_PWM_THRESHOLD             (100000.0)   /* e-RPM  Single Pulse -> PWM transition */
#define STALL_DETECTION_THRESHOLD       (50)         /* Stall detection tolerance: higher number - more tolerant to perturbances, but slower detection */
#define STALL_DETECTION_ENABLED         true         /* Setting to 'false' disables the stall detection mechanism */
#define STALL_MAXIMUM_ERPM              (350000.0)   /* e-RPM - Threshold when the algorithm might lose synchronization */
#define ONE_PHASE_MODE                  false        /* Setting to 'true' enables the One Phase mode, where only phases A and B are used. Setting to 'false' enables the Three Phase mode, where phases A, B and C are used. */


#endif	/* CONFIG_H */
