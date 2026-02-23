[![MCHP](images/microchip.png)](https://www.microchip.com)

<h2> Table of Contents </h2>

- [Motor Control With AVR®](#motor-control-with-avr®)
- [Release Notes](#release-notes)
- [Related Documentation](#related-documentation)
- [Software Used](#software-used)
- [Hardware Used](#hardware-used)
- [Solution Diagram](#solution-diagram)
- [Quick Start Guide](#quick-start-guide)
  - [Physical Setup](#physical-setup)
  - [Curiosity Nano - MPPB Pin Mapping](#curiosity-nano---mppb-pin-mapping)
  - [Necessary Hardware Tweaks](#necessary-hardware-tweaks)
  - [Configuration Settings](#configuration-settings)
- [Application Usage](#application-usage)
  - [Let's Spin the Motor](#lets-spin-the-motor)
  - [Tunning Guide](#tunning-guide)
  - [Programming the AVR®](#programming-the-avr®)
  - [Console Interface](#console-interface)
  - [PWM Input Interface](#pwm-input-interface)
- [Software Description](#software-description)
  - [Software Organization in Folders and Files](#software-organization-in-folders-and-files)
  - [MCC Maping](#mcc-maping)
  - [Application Block Overview](#application-block-overview)
  - [Application Flowchart](#application-flowchart)
  - [Application Programming Interface Functions](#application-programming-interface-functions)
  - [Configurable Parameters](#configurable-parameters)
  - [Application Interrupt Window Time](#application-interrupt-window-time)
  - [Motor Drive Sequence](#motor-drive-sequence)
    - [PWM Mode](#pwm-mode)
    - [Single Pulse Mode](#single-pulse-mode)
    - [Switch Between PWM And Single Pulse](#switch-between-pwm-and-single-pulse)
  - [Motor Feedback Sensing](#motor-feedback-sensing)
  - [Motor Synchronization Algorithm](#motor-synchronization-algorithm)
  - [Motor Speed Regulator Algorithm](#motor-speed-regulator-algorithm)
- [Results](#results)
- [Summary](#summary)

## Motor Control With AVR®

This repository contains a Motor Control application focused on extreme-speed Trapezoidal Sensorless control, using three implementations of the AVR family: AVR16EB32, AVR128DA48 and ATmega4809 devices. Check the [*Release Notes*](#release-notes) section to see the available functionality of the current release. The aim of this application is keeping stability at the high count of electrical rotations per minute (> 200,000 Electrical RPM), using a simplified Proportional-Integral (PI) algorithm. All the three code examples have the same functionality; the only difference is the used device.

- <b>AVR EB</b> has two new peripherals, the Timer Counter type E (TCE) and a Waveform Extension (WEX), that have new hardware capabilities meant to take over software functions usually used in motor control, as described in [Getting Started with the TCE and WEX](https://onlinedocs.microchip.com/oxy/GUID-8FB8D192-E8C9-4748-B991-D4D842E01591-en-US-1/index.html) and in the [AVR® EB Data Sheet](https://www.microchip.com/en-us/product/avr16eb32#document-table)

- <b>AVR DA</b> offers more memory and a bit more CPU frequency and pins, as described in the [AVR® DA Data Sheet](https://www.microchip.com/en-us/product/avr128da48#document-table)

- <b>ATmega</b> incorporates features from both AVR EB and AVR DA families, offering a well-balanced combination of hardware capabilities, memory, and pin count, as described in the [AVR® ATmega Data Sheet](https://www.microchip.com/en-us/product/atmega4809#document-table)
  
- The application's functionality is to obtain a trapezoidal (6-step block commutation) with motor synchronization and support for sensorless feedback type. The focus is on Brushless Direct Current (BLDC) motors and Permanent Magnet Synchronous Motors (PMSMs)

- The Sensorless feedback and synchronization are achieved using the Zero-Cross Detections (ZCDs) of Back-Electromotive Forces (BEMFs) of each of the three phases of the motor. The BEMFs are captured using hardware peripherals, thus improving the accuracy of zero-cross detections at high speeds. The motor synchronization is achieved using a Proportional-Integral (PI) algorithm, that calculates the error between the measured ZCD and the ideal ZCD.

## Release Notes

Current version 1.2.0 features:

- Crossing from PWM drive mode to Single Pulse drive mode with adjustable speed thresholds

Version 1.1.0 features:

- Adjustable phase advance
- Speed regulator with adjustable Kp and Ki parameters for Closed-Loop control
- Pulse-Width Modulation (PWM) input for compatibility with radio-controlled receivers
- Removed virtual potentiometer feature

Version 1.0.0 features:

- Support for three-phase BLDC and PMSM motors
- Motor specification in the configuration file
- Trapezoidal drive
- BEMF sensing
- Start ramp
- Proportional-Integral (PI) algorithm with fixed parameters for Open-Loop synchronization
- Fault support for Hardware Peak Overcurrent Protection (Peak OCP), Software Average Overcurrent Protection (Avg OCP), Overvoltage Protection (OVP) and Stall Detection
- Current, Voltage Bus and Potentiometer analog measurements at run time
- Potentiometer emulation in percentage, configurable from configuration file
- Switching frequency at 40 kHz

## Related Documentation

More details and code examples on the AVR16EB32, AVR128DA48 and ATmega4809 can be found at the following links:

- [AVR<sup>®</sup> EB Product Page](https://www.microchip.com/en-us/products/microcontrollers/8-bit-mcus/avr-mcus/avr-eb)
- [AVR<sup>®</sup> EB Code Examples](https://mplab-discover.microchip.com/v2?dsl=avr16eb32)
- [AVR<sup>®</sup> DA Product Page](https://www.microchip.com/en-us/products/microcontrollers/8-bit-mcus/avr-mcus/avr-da)
- [AVR<sup>®</sup> DA Code Examples](https://mplab-discover.microchip.com/v2?dsl=avr128da48)
- [AVR<sup>®</sup> ATmega Product Page](https://www.microchip.com/en-us/products/microcontrollers/8-bit-mcus/avr-mcus/atmega4809)
- [AVR<sup>®</sup> ATmega Code Examples](https://mplab-discover.microchip.com/v2?dsl=atmega4809)

## Software Used

- [MPLAB® X IDE v6.30 or newer](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_AVR-EB&utm_content=avr16eb32-bldc-pmsm-motor-control-library-github&utm_bu=MCU08)
- [AVR-Ex DFP v2.11.221 or newer](https://packs.download.microchip.com/)
- [AVR-Dx DFP v2.7.321 or newer](https://packs.download.microchip.com/)
- [AVR-ATmega DFP v3.6.229 or newer](https://packs.download.microchip.com/)
- [MPLAB® XC8 compiler v3.10 or newer](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_AVR-EB&utm_content=avr16eb32-bldc-pmsm-motor-control-library-github&utm_bu=MCU08)
- [MPLAB Code Configurator (MCC) v5.8.4 or newer](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator)

## Hardware Used

- [AVR<sup>®</sup> EB Curiosity Nano](https://www.microchip.com/en-us/development-tool/EV73J36A)
- [AVR<sup>®</sup> DA Curiosity Nano](https://www.microchip.com/en-us/development-tool/DM164151)
- [AVR<sup>®</sup> ATmega Curiosity Nano](https://www.microchip.com/en-us/development-tool/DM320115)
- [Multi-Phase Power Board (MPPB)](https://www.microchip.com/en-us/development-tool/EV35Z86A)
- [AVR EB Curiosity Nano Adaptor to MPPB](https://www.microchip.com/en-us/development-tool/EV88N31A)
- [AVR DA Curiosity Nano Adaptor to MPPB](#curiosity-nano---mppb-pin-mapping), made with wires
- [AVR ATmega Curiosity Nano Adaptor to MPPB](#curiosity-nano---mppb-pin-mapping), made with wires
- A Voltage power supply (6-55V and 10A limit, depending on the motor used)
- At least one BLDC Motor. For development and testing of this demo the following motors were used:
  - ACT42BLF01
  - SZSPEED 2207 KV 2500
  - Hacker A10 KV 2900
  - A2212 KV 2200
  - 130K RPM 12V low cost hair-dryer motor

## Solution Diagram

<br><img src="images/solution_diagram.png">

## Quick Start Guide

### Physical Setup

The AVR16EB32, AVR128DA48 or ATmega4809 Curiosity Nano Development boards are used along with the MPPB, AVR EB, AVR DA or ATmega CNANO to MPPB adapter board, the BLDC Motor and a Voltage power supply.

<br>Connection steps:

1. Plug in the AVR16EB32, AVR128DA48 or ATmega4809 Curiosity Nano board in the connector present on the MPPB adapter board.
2. Plug in the MPPB adapter board to the MPPB board.
3. Plug in the AVR® EB, AVR DA or ATmega Curiosity Nano boards to the PC.
4. Connect the voltage power supply wires to the V_SUPPLY conector from the MPPB.
5. Connect the motor phase wires to the PHASE connector from MPPB in any order.

<h4> Example Setup: </h4>

<br><img src="images/full_setup.png">

### Curiosity Nano - MPPB Pin Mapping

If the MPPB and the adapter boards are not used, the user can integrate the AVR EB, AVR DA or ATmega boards into another hardware setup by using the following pinouts:

| Curiosity Nano Boards Pinout                 | Curiosity Nano - MPPB Pin Mapping          |
|:--------------------------------------------:|:------------------------------------------:|
| <img src="images/avr_eb_mc_pinout.png">      | <img src="images/avr_eb_mppb_map.png">     |
| <img src="images/avr_da_mc_pinout.png">      | <img src="images/avr_da_mppb_map.png">     |
| <img src="images/avr_atmega_mc_pinout.png">  | <img src="images/avr_atmega_mppb_map.png"> |

<br>Pin mapping legend AVR16EB32, AVR128DA48, ATmega4809 Curiosity Nano Boards to MPPB:

| Pin Name          | AVR16EB32 Curiosity Nano Board | AVR128DA48 Curiosity Nano Board | ATmega4809 Curiosity Nano Board | MPPB Board                  |
|-------------------|--------------------------------|---------------------------------|---------------------------------|-----------------------------|
|Drive A High       |Pin 9 -  PA0                    |Pin 7 -  PA0                     |Pin 7 -   PA0                    |Pin 26                       |
|Drive A Low        |Pin 10 - PA1                    |Pin 20 - PB0                     |Pin 10 -  PA3                    |Pin 25                       |
|Drive B High       |Pin 7 -  PA2                    |Pin 8 -  PA1                     |Pin 8 -   PA1                    |Pin 24                       |
|Drive B Low        |Pin 8 -  PA3                    |Pin 21 - PB1                     |Pin 11 -  PA4                    |Pin 23                       |
|Drive C High       |Pin 11 - PA4                    |Pin 36 - PA2                     |Pin 9 -   PA2                    |Pin 22                       |
|Drive C Low        |Pin 12 - PA5                    |Pin 22 - PB2                     |Pin 12 -  PA5                    |Pin 21                       |
|Feedback A         |Pin 35 - PD4                    |Pin 49 - PD6                     |Pin 45 -  PD2                    |Pin 12                       |
|Feedback B         |Pin 36 - PD5                    |Pin 48 - PD2                     |Pin 47 -  PD4                    |Pin 10                       |
|Feedback C         |Pin 29 - PD6                    |Pin 44 - PD4                     |Pin 49 -  PD6                    |Pin 8                        |
|Feedback N         |Pin 31 - PD0                    |Pin 50 - PD7                     |Pin 50 -  PD7                    |Pin 4                        |
|Current Sense      |Pin 34 - PD3                    |Pin 40 - PE2                     |Pin 43 -  PD0                    |Pin 7                        |
|Current Sense VREF |Pin 30 - PD7                    |Pin 38 - PE0                     |Pin 44 -  PD1                    |Pin 3                        |
|Current Trip       |Pin 34 - PD3                    |Pin 40 - PE2                     |Pin 41 -  PC7                    | -                           |
|V Supply Monitor   |Pin 27 - PF4                    |Pin 46 - PD0                     |Pin 25 -  PE0                    |Pin 9                        |
|Potentiometer      |Pin 32 - PD1                    |Pin 47 - PD1                     |Pin 27 -  PE2                    |Pin 29                       |
|LED                |Pin 21 - PF5                    |Pin 27 - PC6                     |Pin 32 -  PF5                    |Pin 33                       |
|Switch             |Pin 20 - PF6                    |Pin 28 - PC7                     |Pin 54 -  PF6                    |Pin 35                       |
|PWM IN             |Pin 23 - PF0                    |Pin 37 - PA3                     |Pin 28  - PE3                    |Pin 18                       |
|TXC                |Pin 16 - PC1                    |Pin 25 - PC0                     |Pin 20 -  PB0                    | -                           |
|RXC                |Pin 17 - PC2                    |Pin 26 - PC1                     |Pin 21 -  PB1                    | -                           |
|3V3                |Pin 37                          |Pin 51                           |Pin 51                           |Pin 39                       |
|VOFF               |Pin 41                          |Pin 55                           |Pin 55                           |Pin 38                       |
|GND                |Pins 38, 28, 15                 |Pins 52, 42, 33, 24, 15          |Pins 52, 42, 33, 24, 15          |Pins 40, 28, 27, 14, 13, 2, 1|

<br><b>Note:</b> In this repository, schematics for all three platforms are provided in the `pdf` folder:
 - AVR16EB32_MPPB_Mapping
 - AVR128DA48_MPPB_Mapping
 - ATMEGA4809_MPPB_Mapping
</br>

### Necessary Hardware Tweaks

<br> This demo requires adding three SMD capacitors of 1 nF each with the size of 0402 on the MPPB board, one for each motor phases. Also, the capacitor for the motor neutral filter must be replaced with one of 3.3 nF with the same size, 0402, as explained below.

<br> Because this demo counts on capturing the BEMF using a hardware capture mechanism of a timer, the captured signals need filtering to remove false zero-cross detection. The easiest method to do this is by using a RC low-pass filter. The MPPB board has placeholder pads for the capacitors that need to be added. The capacitor for virtual neutral point is already in place, but needs to be replaced with a 3.3 nF capacitor, and the capacitor values for phases A, B and C must have the value of 1 nF (three times smaller than the one from virtual neutral). With these capacitor values, the resulted RC filters will add a 10 µs delay to the zero-cross detection. The resulted RC filters are good enough for noise filtering and not adding a big delay, thus allowing for spinning the motor at very high electrical RPM.

<h3> Capacitors location marked with green rectangles </h3>

<br><br><img src="images/rc_caps_add.png">

<h3> Capacitors location zoomed in</h3>

<br><br><img src="images/hardware_rc_zoomed.png">

### Configuration Settings

<br>These are a set of configuration settings, apart from the default values, needed to run the demo in the Trapezoidal Sensorless mode with the ACT42BLF01 motor and SZSPEED 2207 2500KV drone motor.
<br>In the configuration file [`config.h`](#configurable-parameters) edit the settings according to the usage scenario. 

<br><h3> Configuration Settings for the ACT42BLF01 Motor </h3>

```c

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
#define ADC_CURRENT_TRIP                (7000.0)     /* mA - ADC current trip level */
#define COMPARATOR_CURRENT_TRIP         (20000.0)    /* mA - Comparator trip level - not used on external-comparator configurations */
#define FAULT_COMPARATOR_EN             true
#define BOARD_PHASE_RC_DELAY            (10.0)       /* microseconds - RC filter delay */
#define BOARD_MOSFET_RDSON              (0.004)      /* ohm - MOSFETs Rds-on resistance */

/* Motor-specific settings */
/* ACT42BLF01:  supply 24V, 3A limit */
#define MOTOR_PHASE_ADVANCE             (10.0)       /* Phase advance 0.0 ... 30.0 electrical degrees */
#define MOTOR_STARTUP_CURRENT           (2500.0)     /* mA - Initial alignment current pulse may be higher than overcurrent protection */
#define MOTOR_RPP                       (2.6)        /* ohms - Motor resistance measured phase-to-phase */
#define MOTOR_OPEN_LOOP_RAMP            (0.0004)     /* Amplitude ramp steepness: step size per millisecond 0.00004 ... 1.0 */
#define MOTOR_ALIGNMENT_DURATION        (10)         /* ms */
#define MOTOR_STARTUP_TIME              (1000)       /* ms -  delay until commands (POT or PWM-in) are accepted; '-1' makes commands to be ignored */
#define MOTOR_STATRUP_SPEED             (0.0)        /* e-RPM - specify the initial speed for fast motors */

/* Speed regulation specific settings */
#define REGULATOR_SPEED_EN              true         /* Setting to 'true' enables speed control in Closed Loop, setting to 'false' enables amplitude control in Open Loop */
#define REGULATOR_MAX_SPEED             (15000.0)    /* e-RPM target speed for 100% command */
#define REGULATOR_MIN_SPEED             ( 4000.0)    /* e-RPM target speed for   0% command */
#define REGULATOR_PI_KP                 (1.0)        /* PI speed control loop proportional coefficient */
#define REGULATOR_PI_KI                 (1.0)        /* PI speed control loop integral coefficient */
#define REGULATOR_PI_DT                 (50.0)       /* PI time step size [ms], this parameter is also used for measurement of speed in open loop, minimum 10ms */

/* Drive Algorithm settings */
#define DRIVE_FORCED                    false        /* Setting to 'true' runs the motor without BEMF sensing, only blind drive, no rotor synchronization, could overheat the motor */
#define SINGLE_PULSE_MODE               false        /* Setting to 'true' enables single pulse drive method, setting to 'false' enables the PWM modulation drive method */
#define PWM_TO_SP_THRESHOLD             (120000.0)   /* e-RPM  PWM -> SinglePulse transition */
#define SP_TO_PWM_THRESHOLD             (100000.0)   /* e-RPM  SinglePulse -> PWM transition */
#define STALL_DETECTION_THRESHOLD       (50)         /* Stall detection tolerance: higher number - more tolerant to perturbances, but slower detection */
#define STALL_DETECTION_ENABLED         true         /* Setting to 'false' disables stall detection mechanism */
#define STALL_MAXIMUM_ERPM              (350000.0)   /* e-RPM  - threshold when algorithm might lose synchronization */
```

<br><h3> Configuration Settings for the SZSPEED 2207 2500KV Drone Motor </h3>

```c

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
/* A2207-2500KV:  supply 16V, 3A limit */
#define MOTOR_PHASE_ADVANCE             (10.0)       /* Phase advance 0.0 ... 30.0 electrical degrees */
#define MOTOR_STARTUP_CURRENT           (10000.0)    /* mA - Initial alignment current pulse may be higher than overcurrent protection */
#define MOTOR_RPP                       (0.1)        /* ohms - Motor resistance measured phase-to-phase */
#define MOTOR_OPEN_LOOP_RAMP            (0.0004)     /* Amplitude ramp steepness: step size per millisecond 0.00004 ... 1.0 */
#define MOTOR_ALIGNMENT_DURATION        (5)          /* ms */
#define MOTOR_STARTUP_TIME              (1000)       /* ms -  delay until commands (POT or PWM-in) are accepted; '-1' makes commands to be ignored */
#define MOTOR_STATRUP_SPEED             (25000.0)    /* e-RPM - specify the initial speed for fast motors */

/* Speed regulation specific settings */
#define REGULATOR_SPEED_EN              true         /* Setting to 'true' enables speed control in Closed Loop, setting to 'false' enables amplitude control in Open Loop */
#define REGULATOR_MAX_SPEED             (250000.0)   /* e-RPM target speed for 100% command */
#define REGULATOR_MIN_SPEED             (50000.0)    /* e-RPM target speed for   0% command */
#define REGULATOR_PI_KP                 (1.0)        /* PI speed control loop proportional coefficient */
#define REGULATOR_PI_KI                 (0.1)        /* PI speed control loop integral coefficient */
#define REGULATOR_PI_DT                 (20.0)       /* PI time step size [ms], this parameter is also used for measurement of speed in open loop, minimum 10ms */

/* Drive Algorithm settings */
#define DRIVE_FORCED                    false        /* Setting to 'true' runs the motor without BEMF sensing, only blind drive, no rotor synchronization, could overheat the motor */
#define SINGLE_PULSE_MODE               true         /* Setting to 'true' enables single pulse drive method, setting to 'false' enables the PWM modulation drive method */
#define PWM_TO_SP_THRESHOLD             (120000.0)   /* e-RPM  PWM -> SinglePulse transition */
#define SP_TO_PWM_THRESHOLD             (100000.0)   /* e-RPM  SinglePulse -> PWM transition */
#define STALL_DETECTION_THRESHOLD       (50)         /* Stall detection tolerance: higher number - more tolerant to perturbances, but slower detection */
#define STALL_DETECTION_ENABLED         true         /* Setting to 'false' disables stall detection mechanism */
#define STALL_MAXIMUM_ERPM              (50000000.0) /* e-RPM  - threshold when algorithm might lose synchronization */
```

<br><b>Note:</b> In the `config_examples` folder there are `config.h` example files, one for each motor used in testing this demo. Copy the variant of the `config.h` file corresponding to the desired motor and place it in `fw/common_files`. The copied configuration file will overwrite the old one.</br>

## Application Usage

### Let's Spin the Motor

After all the steps from [Quick Start Guide](#quick-start-guide) are completed, turn the MPPB potentiometer to 50%, then press the MPPB button to spin the motor.
The spinning direction depends on the wiring of the phases.

### Tunning Guide

After following all the steps from [Quick Start Guide](#quick-start-guide) and the motor is not yet spining, or an error message is displayed in the console, these are some useful steps to try to tune the application for a new motor:

1. Measure the phase-to-phase resistance between any two wires of the motor. Put this value in `MOTOR_RPP`, from the `config.h` file.
2. Disable the speed regulator by setting `REGULATOR_SPEED_EN` to `false`.
3. The initial value for `MOTOR_STARTUP_CURRENT` can be close to the rated current of the motor.
4. If the motor is not spinning after the first two steps and reprogramming, set `MOTOR_STARTUP_TIME` to `-1` and `DRIVE_FORCED` to `true`, to put the motor in Forced Commutation mode. Try to increase `MOTOR_STARTUP_CURRENT` by 0.5A and reprogram until the motor starts spinning. After the motor is spinning in Forced mode without vibrations, set `MOTOR_STARTUP_TIME` to the initial value and `MOTOR_FORCED` back to `false`.
5. `MOTOR_ALIGNMENT_DURATION` can also be adjusted. For example, for a drone motor with low inductance, the alignment period is much smaller compared to a motor with high inductance. Try to increase or decrease the duration with steps not greater than 10 ms at a time.
6. `MOTOR_OPEN_LOOP_RAMP` can also be adjusted. This parameter establishes how aggresive the ramp-up process is. Higher values of this parameter means more aggresive ramp. For a motor with low inductance and high nominal speed, the ramp can be more aggresive compared to a motor with higher inductance and lower nominal speed. The safe and minimum value of this parameter is 0.00004.
7. After getting the motor spinning, set back the parameter `REGULATOR_SPEED_EN` to `true`.
8. For stability, ensure that `REGULATOR_MIN_SPEED` is high enough to run the motor stable (10% of nominal speed) and `REGULATOR_MAX_SPEED` does not exceed the maximum rated speed at the supplied voltage.

### Programming the AVR®

1. Download the zip file or clone the repository to get the source code.

2. Open the `fw/motor_demo_eb.X`,  `fw/motor_demo_da.X` or  `fw/motor_demo_mega4809.X` project in MPLAB® X IDE.

3. Right click the project and select Set as Main Project.

<br><img src="images/set_main_project.png">

4. Edit the [`config.h`](#configurable-parameters) file, found in `motor_demo_eb.X`, `motor_demo_da.X` or `motor_demo_mega4809.X`, with the utilized motor parameters and drive options. See [Configuration Settings](#configuration-settings) for examples.

5. Build the `motor_demo_eb.X`, `motor_demo_da.X` or `motor_demo_mega4809.X` project by clicking **Clean and Build Project**.

<br><img src="images/clean_build_compile.png">

6. Click **Make and Program Device** to program the project to the board.

<br><img src="images/program_project.png">

### Console Interface

<br>The application has a console communication interface. To activate it, open a PC software terminal and select the UART protocol, 8N1, with a baud rate of 57600 bps.
<br> The serial interface provides information about the remote controller PWM input, potentiometer value, voltage bus value, motor current value, electrical rotations per minute (RPM) value and motor running state (ON/OFF).

<br><img src="images/console.png">

### PWM Input Interface
<br>The MPPB hardware and the software application support interfacing with a PWM Remote Controller (PWM-RC).
<br>The application measures both signal from the PWM-RC and on-board potentiometer, but the PWM-RC has priority over the potentiometer in controlling the motor.
<br>If the PWM-RC/PWM-IN signal is not detected, then on-board potentiometer is used for control.
<br><img src="images/pwm_in.png">

## Software Description

### Software Organization in Folders and Files

All the files shared by the three platforms are in the `common_files` folder. Each platform has its own `main.c` and `mcc_mapping.h` files.
```
   fw
    ├───common_files
    │   │   app.c
    │   │   config.h
    │   │
    │   ├───motor
    │   │       analog.c
    │   │       analog.h
    │   │       conversion_macros.h
    │   │       motor.c
    │   │       motor.h
    │   │
    │   └───utils
    │           button_led.c
    │           button_led.h
    │           dbg_logger.c
    │           dbg_logger.h
    │           dbg_pins.h
    │           precise_delay.h
    │           pwm_in.c
    │           pwm_in.h
    │           sw_timer.c
    │           sw_timer.h
    │
    ├───motor_demo_da.X
    │   │   main.c
    │   │   Makefile
    │   │   mcc_mapping.h
    │   │   motor_demo_da.mc3
    │   │
    │   ├───mcc_generated_files
    │   └───nbproject
    │           configurations.xml
    │           project.xml
    │
    ├───motor_demo_eb.X
    │   │   main.c
    │   │   Makefile
    │   │   mcc_mapping.h
    │   │   motor_demo_eb.mc3
    │   │
    │   ├───mcc_generated_files
    │   └───nbproject
    │           configurations.xml
    │           project.xml
    │
    └───motor_demo_mega4809.X
        │   main.c
        │   Makefile
        │   mcc_mapping.h
        │   motor_demo_mega4809.mc3
        │
        ├───mcc_generated_files
        └───nbproject
                configurations.xml
                project.xml
```

### MCC Maping

The `mcc_mapping.h` files are used to map all the port pins and low-level driver functions generated using the MPLAB® Code Configurator (MCC) to the abstract layers of the application. These layers include: motor, analog, LED/button, PWM-IN and other wrapper layers. The `mcc_mapping.h` files can be found in `fw/motor_demo_eb.X`, `fw/motor_demo_da.X` and `fw/motor_demo_mega4809.X`.

### Application Block Overview

<br><img src="images/application_block_overview.png">

### Application Flowchart

<br><img src="images/application_flowchart.png">

1. Short-press the button on the MPPB board. The motor starts spinning and enters the Running state. The LED from MPPB turns on. The speed can be adjusted using the potentiometer present on the MPPB board.
2. Short-press the button from MPPB again. The motor decelerates, comes to a complete stop and enters the Idle state. The LED from MPPB turns off.
3. Long-press the button (more than 1.5s) to restart the application.
4. If a Fault event occurs, the motor stops, the event is mentioned in the console and the application enters the Idle state. The LED blinks five times signalling the error, then stops.

### Application Programming Interface Functions

<br> The APIs from the Motor Control Stack found in `motor_control.h` are the following:

<br>• <b>`Motor_Initialize()`</b> - Initialization function, needs to be called before any other function
<br>• <b>`Motor_Start()`</b> - Starts the motor. If the motor is already spinning, the call is ignored
<br>• <b>`Motor_Stop()`</b> - Stops the motor. If the motor is already stopped, the call is ignored
<br>• <b>`Motor_Fault()`</b> - Stops the motor and then clears the Fault flags. It is registered in the application to be called by the Analog module in case of a fault situation.
<br>• <b>`Motor_CommandSet()`</b> - Has dual use. For speed regulation mode it receives the value of the target speed. For open-loop mode it receives the value of the drive amplitude (PWM duty cycle).
<br>• <b>`Motor_MaxAmpGet()`</b> - Returns the maximum possible PWM amplitude value
<br>• <b>`Motor_StatusGet()`</b> - Returns the ON/OFF state of the motor and possible fault events
<br>• <b>`Motor_ErpmGet()`</b> - Returns the electrical RPM value of the motor during run time
<br>• <b>`Motor_AmplitudeGet()`</b> - Gets the PWM amplitude value
<br>• <b>`Motor_TimeTick()`</b> - Needs to be called once every 1 ms, only in the context of an interrupt. It is required for internal synchronization

<b>Important:</b> Use only the public APIs from the `motor_control.h` file so as not to alter the library functionality in any way.

### Configurable Parameters

The parameters from the `config.h` file used to customize the application are the following:

<br><b> Analog Module Settings </b>

<br>• <b>`ADC_IIR_FILTER`</b> - Enables or disables a smoothing filter for analog measurements: potentiometer, voltage bus and current. This filter is used only for displaying values, not by fault or other mechanism that requires a fast response.

<br><b> PWM Input Settings </b>

<br>• <b>`PWM_IN_PERIOD`</b> - Represents the period of the PWM input signal, compatible with radio-controlled receivers, that can be used to set the speed reference in Closed-Loop, or the PWM amplitude reference in Open-Loop. The standard value of this parameter in 20 milliseconds.
<br>• <b>`PWM_IN_MAX_DCY`</b> - Represents the maximum `ON` time of the PWM input signal and is equivalent to setting the maximum reference. The standard value of this parameter is 2 milliseconds, but it can be tuned accordingly to eventual tolerances.
<br>• <b>`PWM_IN_MIN_DCY`</b> - Represents the minimum `ON` time of the PWM input signal and is equivalent to setting the minimum reference. The standard value of this parameter is 1 millisecond, but it can be tuned accordingly to eventual tolerances.

<br><b> Power Board Settigs </b>

<br>• <b>`CURRENT_SHUNT_RESISTANCE`</b> - The current sense shunt resistance, given in ohms, dependent on the power board
<br>• <b>`CURRENT_AMPLIFIER_GAIN`</b> - The current sense amplifier, dependent on the power board
<br>• <b>`VBUS_DIVIDER`</b> - The voltage divider, used to scale the V<sub>BUS</sub> to be able to measure it with the `ANALOG_REFERENCE` logic, dependent on the power board
<br>• <b>`ANALOG_REFERENCE`</b> - The voltage reference (this application has a 3V3 logic)
<br>• <b>`ADC_VBUS_TRIP`</b> - Sets the ADC trip level in case of an overvoltage protection, expressed in millivolts
<br>• <b>`ADC_CURRENT_TRIP`</b> - Sets the ADC trip level in case of an average overcurrent protection, expressed in milliamperes
<br>• <b>`COMPARATOR_CURRENT_TRIP`</b> - Sets the internal comparator's trip level in case of a peak overcurrent protection. This parameter does not have any effect for the external comparator configuration, specifically for the ATmega4809 configuration.
<br>• <b>`FAULT_COMPARATOR_EN`</b> - Enables or disables the comparator used for current trip. For AVR16EB32 and AVR128DA48, this mechanism is implemented using an internal comparator. For ATmega4809, the support is implemented for an external comparator, which must be added to use it.
<br>• <b>`BOARD_PHASE_RC_DELAY`</b> - Delay added to BEMF zero-cross detection by the RC filter present on the power board
<br>• <b>`BOARD_MOSFET_RDSON`</b> - The drain-source on-resistance value of the transistors present on the power board. This value is acquired from the transistor's datasheet.

<br><b> Motor Settings </b>

<br>• <b>`MOTOR_PHASE_ADVANCE`</b> - Sets the value of the phase drive advance, and takes values between `0` and `30` electrical degrees. This parameter is used to improve the motor efficiency and performance at higher speeds by advancing the phase of the applied voltage relative to the BEMF of the motor, effectively shifting the timing of the current flow. Tune this according to the motor used.
<br>• <b>`MOTOR_STARTUP_CURRENT`</b> - The amount of current supplied to the motor phases during the start-up phase, given in amperes
<br>• <b>`MOTOR_RPP`</b> - Motor resistance measured phase-to-phase
<br>• <b>`MOTOR_OPEN_LOOP_RAMP`</b> - Amplitude increase rate; the higher the number, the ramp is more aggresive
<br>• <b>`MOTOR_ALIGNMENT_DURATION`</b> - Initial alignment duration before start-up
<br>• <b>`MOTOR_STARTUP_TIME`</b> - This is the waiting time until the value from the `Motor_CommandSet()` is used to set the amplitude or reference speed. If this parameter is set to '-1', then the value written by `Motor_CommandSet()` is ignored.
<br>• <b>`MOTOR_STATRUP_SPEED`</b> - Sets the initial speed for start-up. Usually this is set to `0`, but fast motors with low inductance need a bigger initial speed, in the range of thousands of electrical RPM.

<br><b> Speed Regulator Settings </b>

<br>• <b>`MOTOR_SPEED_REGULATOR_EN`</b> - Enables or disables the Closed Loop speed regulator
<br>• <b>`REGULATOR_MAX_SPEED`</b> - Sets the maximum speed for the speed regulator
<br>• <b>`REGULATOR_MIN_SPEED`</b> - Sets the minimum speed for the speed regulator
<br>• <b>`REGULATOR_PI_KP`</b> - Proportional term constant parameter used by the speed regulator. It can have values between `0.0` and `1.0`. Tune this according to the motor used.
<br>• <b>`REGULATOR_PI_KI`</b> - Integral term constant parameter used by the speed regulator. It can have values between `0.0` and `1.0`. Tune this according to the motor used.
<br>• <b>`REGULATOR_PI_DT`</b> - Represents the time step or sample interval between consecutive speed controller calculations, with a resolution of 1 millisecond step increment. The smaller this value, the faster the regulator loop is called. Setting this to a very short period (smaller than 10 milliseconds) may cause oscillations and sistem instability.

<br><b> Drive Algorithm Settings </b>

<br>• <b>`DRIVE_FORCED`</b> - Setting this parameter to `true` enables only forced commutation. Setting it to `false` enables motor synchronization.
<br>• <b>`SINGLE_PULSE_MODE`</b> - Enables or disables Single Pulse mode at runtime
<br>• <b>`PWM_TO_SP_THRESHOLD`</b> - Threshold speed value for switching from PWM mode to Single Pulse mode
<br>• <b>`SP_TO_PWM_THRESHOLD`</b> - Threshold speed value for switching from Single Pulse mode to PWM mode
<br>• <b>`STALL_DETECTION_THRESHOLD`</b> - The number of reached stall conditions until the motor is stopped. It can take values between `0` and `255`.
<br>• <b>`STALL_DETECTION_ENABLED`</b> - Enables or disables the stall detection mechanism
<br>• <b>`STALL_MAXIMUM_ERPM`</b> - Limit speed value of the motor given in electrical RPM, when the algorithm might lose synchronization

<br> With the initial values, the motor will operate, although performance may not be optimal. However, these settings provide a good starting point for further tuning to meet the requirements of a custom application.

### Application Interrupt Window Time

<br><img src="images/interrupt_window_time.png">

Interrupts (ISRs) used by the application:

1. Sector timer interrupt - variable period, dependent on the RPM of the motor (handles drive, BEMF feedback measurement and motor synchronization)
2. Software timer interrupt - 1ms period (handles speed regulator, open loop controller, analog measurements, button and LED states).
3. Software timer in main loop - 50 ms period (handles reference commands scaling, amplitude in open loop and speed in closed loop, received from the potentiometer or external PWM input).

The duration of each ISR or loop in the aplication can be observed in the table below:

| MCU & XC8 OPTIONS | Sector Timer ISR [μs] | 1 ms ISR [μs] | 50 ms Software Timer [μs] | Speed Regulator Loop [μs]   |
|:-----------------:|:---------------------:|:-------------:|:-------------------------:|:---------------------------:|
|AVR16EB32 FREE     |    22.5               |   21.5        |   45                      |   5.5                       |
|AVR16EB32 PRO      |    20.5               |   17          |   36                      |   5                         |
|ATMEGA4809 FREE    |    22.5               |   21.5        |   45                      |   5.5                       |
|ATMEGA4809 PRO     |    20.5               |   17          |   35                      |   5                         |
|AVR128DA48 FREE    |    19                 |   17          |   38                      |   4                         |
|AVR128DA48 PRO     |    17                 |   14          |   30                      |   4                         |

`FREE` refers to the default  optimization `XC8` compiler version, available without license. `PRO` refers to the speed optimized `XC8` compiler version, available with license.

<br> <b>Note:</b> The Sector timer interrupt has a higher priority and will preempt running other interrupts increasing their overall execution time, or will delay other interrupts. One sector duration represents one sixth of one electrical revolution. The duration of one electrical revolution is inverse proportional with the rotational speed, expressed in revolutions per second. 

### Motor Drive Sequence

Drive sequence legend:

| Sector | Drive AH | Drive AL | Drive BH | Drive BL | Drive CH | Drive CL | Motor Phase A | Motor Phase B | Motor Phase C |
|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------------:|:-------------:|:-------------:|
|   S1   |    Low   |   Low    |   PWM    |   Low    |   Low    |   High   |   Floating    |  PWM Driven   |  Low Driven   |
|   S2   |    PWM   |   Low    |   Low    |   Low    |   Low    |   High   |   PWM Driven  |  Floating     |  Low Driven   |
|   S3   |    PWM   |   Low    |   Low    |   High   |   Low    |   Low    |   PWM Driven  |  Low Driven   |  Floating     |
|   S4   |    Low   |   Low    |   Low    |   High   |   PWM    |   Low    |   Floating    |  Low Driven   |  PWM Driven   |
|   S5   |    Low   |   High   |   Low    |   Low    |   PWM    |   Low    |   Low Driven  |  Floating     |  PWM Driven   |
|   S6   |    Low   |   High   |   PWM    |   Low    |   Low    |   Low    |   Low Driven  |  PWM Driven   |  Floating     |

<br>Drive AH, BH and CH pins are waveform output (WO) pins, that are controlled by a timer and change their duty cycle based on the control algorithm.
<br>Drive AL, BL and CL are general purpose input/output (GPIO) pins, that change their state based on the current sector.
<br>The drive sequence is the same in both PWM mode and Single Pulse mode, the difference consists in the way the AH, BH and CH signals are generated using the PWM timer.

#### PWM Mode

<br> This is the default drive mode. In this mode the sector timer has a variable period based on the speed of the motor and the PWM timer has a fixed period of 25.6 μs (~ 40 kHz switching frequency). In each sector there are multiple periods of the PWM timer. Using this mode high electrical speeds can be achieved (< 200,000 Electrical RPM). However, at very high speeds (> 200,000 Electrical RPM) due to switching losses and limited resolution of the PWM timer using a fixed period, this mode is not useful anymore. The solution is to switch to the Single Pulse mode when a threshold speed is achieved.

<h4> PWM Mode Drive Signals </h4>
<br><img src="images/drive_sequence_pwm.png">

#### Single Pulse Mode

<br>This mode must be activated using `SINGLE_PULSE_MODE` and setting values to `PWM_TO_SP_THRESHOLD` and `SP_TO_PWM_THRESHOLD` in `config.h` file before runtime.
<br>`PWM_TO_SP_THRESHOLD` and `SP_TO_PWM_THRESHOLD` represents the speed limits when the switch from one mode to the other happens. It can be observed that there is a difference between the two values, to avoid unwanted switches between the two modes, so a hysteresis mechanism is added.
<br>The reccomandation is to switch to Single Pulse mode, when the speed reaches a values big enough that there are fewer than five PWM timer periods per one sector. On the same principle it is recomanded to switch back to PWM mode when there are seven or more PWM timer periods per one sector.
<br>Single pulse mode has two advantages that allow it to reach higher speeds than PWM modes. The first one is that there are much fewer switching losses compared to PWM mode. There is just one big `ON` time and one big  `OFF` time in one electrical period of six sectors, for each phase. The second advantage is the increased timer resolution by having a variable period. This is observed at very high speeds, beacuse in PWM mode there can be sectors with different numbers of PWM timer periods. In Single Pulse mode, even at very high speeds the sectors are equal, because there is just one big `ON` time istead of multiple 'ON' times, as it is in PWM mode.

<h4> Single Pulse Mode Drive Signals </h4>
<br><img src="images/drive_sequence_sp.png">

#### Switch Between PWM And Single Pulse

<br> The Single Pulse has some advantages compared to PWM mode, but that only applies at very high speeds. At lower speeds PWM mode is much more reliable. Most motors can not even be started using Single Pulse mode, because of the very fast rise of the current through the windings. The working principle is to spin the motor in PWM mode until it reaches the maximum possible speed (< 200,000 Electrical RPM), and then swicth to Single Pulse mode to reach extreme speeds (>200,000 Electrical RPM).

<h4>PWM Mode To Single Pulse Mode Overview </h4>
<br><img src="images/pwm_to_sp_cross.png">

<br> It can be observed that the duty cycle (75% in this example) is kept the same after switching from one mode to the other, but it is scaled to the new period of the PWM timer.

### Motor Feedback Sensing

<br> Rotor position estimation in the Trapezoidal Sensorless Control mode is done by monitoring the BEMF signals from motor phases. For best efficiency, the BEMF signals must be in-phase with the current signals for each motor phase.

<h4> Drive, BEMF and Current Signals for One Motor Phase </h4>

<br><img src="images/phase_voltage_current.png">

<br> For sensorless feedback, the values for the BEMF signals for each motor phase are sampled with the Analog Comparator (AC) peripheral. During each sector, one of the three motor phases will be in Floating state, from where the BEMF can be read. All the PWM driving signals from that motor phase must be synchronously logically low `0`, the coil is not driven and the signal measured after all the propagation delays is the motor’s BEMF.

<br> The Analog Comparator is connected to the divided motor's phase signals at the positive input using a multiplexed input selection to switch from one motor phase to another and acquire the necessary data. The AC is connected to the motor, summing neutral at the negative input. The neutral is reconstructed using hardware components in a resistor star configuration. The signals are divided to be in the range of 0 to 3.3V, to be readable by the microcontroller (MCU). The values for the voltage dividers used in this application are the ones present on the MPPB.

<h4> BEMF Sensing Overview </h4>

<br><img src="images/mux_ac_bemf.png">

<h4> Sector Commutation Overview</h4>

<br><img src="images/commutation.png">

### Motor Synchronization Algorithm

<br> Synchronization is achieved using a simplified Proportional Integral Derivative (PID) algorithm that calculates the error between the ideal zero-cross of BEMF, which is always set to half of the timer's period, and the actual zero-cross, that is acquired using a timer's hardware capture mechanism. The algorithm only has the proportional and the integral terms, but no derivative. The algorithm also uses phase advance ranging between `0` and `30` electrical degrees, that is added to the ```setValue```, which is half of the period, because the goal is to have the zero-cross of the BEMF to fall exactly in the middle of the sector, after `30` electrical degrees.
<br>The advantage of this algorithm is that it is based on bit-shifting operations, and it does not add much CPU overload and interrupt time to process all the data. Using this algorithm greatly reduces the speed oscillations.

<h4> Synchronization Algorithm Timing </h4>

<br><img src="images/synchronization_pi_timing.png">

Above is an example where `MOTOR_PHASE_ADVANCE` is set to `7.5` electrical degrees (`0.5` represents half of the sector, meaning `30` electrical degrees, and `0.125` represents the phase advance of `7.5` electrical degrees, summing a total of `0.625` or `37.5` electrical degrees, the set point when the zero-cross is detected).
<br><b>Note:</b> The zero-cross detection is also affected by the RC constant, which is 10 μs. In this case, the zero-cross of BEMF is detected after `37.5` electrical degrees translated in time, based of sector's length, plus the RC delay.

<h4> Synchronization Algorithm Chart </h4>

<br><img src="images/synchronization_pi_chart.png">

<h4> Phase Advance </h4>

In order to have the best efficiency, the BEMF signals must be in phase with the current signals for each motor phase. Due to the motor’s inductance, at high RPM, the electrical time constant of the motor windings cause a delay in current buildup, causing the current signals to lag the voltage BEMF signals, so phase advance is used for switching the driving sequence in advance. Because the voltage is switched in advance, the current has time to reach the maximum point until the signal from BEMF has a transition that marks a sector change.

<br><img src="images/phase_advance.png">

### Motor Speed Regulator Algorithm

<br> Speed regulation in Closed-Loop is achieved using a simplified PID algorithm that calculates the error between the target speed and measured speed. The algorithm only has the proportional and the integral terms, but no derivative. The target speed value is in the range between `REGULATOR_MIN_SPEED` and `REGULATOR_MAX_SPEED`. The measured speed is acquired by counting the sector change events during a fixed period of time. The values of `REGULATOR_PI_KP` and `REGULATOR_PI_KI` constants can be tuned to achieve a desired behaviour, depending on the motor used. The values of the two constants must be positive.

<h4> Speed Regulator Algorithm Chart </h4>

<br><img src="images/speed_pi_chart.png">

## Results

Below are some captures of A2207 KV2500 drone motor, in PWM mode, Single Pulse mode and at full drive (maximum speed achieved at 100% duty cycle).<br>
Oscilloscope traces: 
  * Ch 1 (Blue Trace)  Phase A Current - current probe direction from the motor towards the board
  * Ch 2 (Cyan Trace)  Phase A Voltage - referenced to ground

|      Mode           |Supply Voltage [V]| Current Consumption [A] | Duty Cycle [%] | e-RPM    |
|:-------------------:|:----------------:|:-----------------------:|:--------------:|:--------:|
|     **PWM**         |     16           |     0.68                |  15            | 112,000  |

<img src="images/capture_pwm_mode.png">

<br>

|      Mode           |Supply Voltage [V]| Current Consumption [A] | Duty Cycle [%] | e-RPM    |
|:-------------------:|:----------------:|:-----------------------:|:--------------:|:--------:|
|   **Single Pulse**  |     16           |     2.00                |  38            | 250,000  |

<img src="images/capture_sp_mode.png">

<br>

|      Mode           |Supply Voltage [V]| Current Consumption [A] | Duty Cycle [%] | e-RPM    |
|:-------------------:|:----------------:|:-----------------------:|:--------------:|:--------:|
|    **Full Drive**   |     16           |     2.40                |  100           | 280,000  |

<img src="images/capture_full_drive.png">


<br>Results obtained with various motors used in this project:

| Motor      | Brief Specifications        | Supply Voltage [V] | Current Consumption [A] | e-RPM                    |
|:----------:|:---------------------------:|:------------------:|:-----------------------:|:------------------------:|
|ACT42BLF01  | 24V / 1.9A / 4pp* / 4kRPM   |    24              |      0.20  (no load)    |       15,000             |
|ACT57BLF02  | 24V / 7.8A / 4pp / 3kRPM    |    24              |      0.50  (no load)    |       12,000             |
|Hair Dryer  | 12V / 150W / 1pp / 130kRPM  |    12              |     11.0 (own fan)      |      120,000             |
|A2207 KV2500| 16.8V / 7pp / 42kRPM        |    16              |      2.2 (no load)      |      250,000             |
|A2212 KV2200| 12V / 6pp / 26kRPM          |    12              |      2.5 (no load)      |      180,000             |
|A10 KV2900  | 8.4V / 6pp / 23kRPM         |     9              |      1.5 (no load)      |      140,000             |

**Note:** *pp - pole pairs

## Summary

<br>This project provides support for spinning a BLDC/PMSM motor using the Trapezoidal Drive method and feedback from the BEMF ZCD to achieve motor synchronization in an Open-Loop configuration and speed control in Closed-Loop configuration. The control algorithm is straightforward and robust and it can be implemented on a variety of low-end MCUs that have a few timer capabilities, such as an analog comparator and an ADC.
