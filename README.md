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
  - [Motor Feedback Sensing](#motor-feedback-sensing)
  - [Motor Synchronization Algorithm](#motor-synchronization-algorithm)
  - [Motor Speed Regulator Algorithm](#motor-speed-regulator-algorithm)
- [Results](#results)
- [Summary](#summary)

## Motor Control With AVR®

This repository contains a Motor Control application focused on high-speed Trapezoidal Sensorless control, using three implementations of the AVR family: AVR16EB32, AVR128DA48 and ATmega4809 devices. Check the [*Release Notes*](#release-notes) section to see the available functionality of the current release. The aim of this application is keeping stability at the high count of electrical rotations per minute (>150 000 Electrical RPM ), using a simplified Proportional-Integral (PI) algorithm. All the three code examples have the same functionality; the only difference is the used device.

- <b>AVR EB</b> has two new peripherals, the Timer Counter type E (TCE) and a Waveform Extension (WEX), that have new hardware capabilities meant to take over software functions usually used in motor control, as described in [Getting Started with the TCE and WEX](https://onlinedocs.microchip.com/oxy/GUID-8FB8D192-E8C9-4748-B991-D4D842E01591-en-US-1/index.html) and in the [AVR® EB Data Sheet](https://www.microchip.com/en-us/product/avr16eb32#document-table)

- <b>AVR DA</b> offers more memory and a bit more CPU frequency and pins, as described in the [AVR® DA Data Sheet](https://www.microchip.com/en-us/product/avr128da48#document-table)

- <b>ATmega</b> incorporates features from both AVR EB and AVR DA families, offering a well-balanced combination of hardware capabilities, memory, and pin count, as described in the [AVR® ATmega Data Sheet](https://www.microchip.com/en-us/product/atmega4809#document-table)
  
- The application's functionality is to obtain a trapezoidal (6-step block commutation) with motor synchronization and support for sensorless feedback type. The focus is on Brushless Direct Current (BLDC) motors and Permanent Magnet Synchronous Motors (PMSMs)

- The Sensorless feedback and synchronization are achieved using the Zero-Cross Detections (ZCDs) of Back-Electromotive Forces (BEMFs) of each of the three phases of the motor. The BEMFs are captured using hardware peripherals, thus improving the accuracy of zero-cross detections at high speeds. The motor synchronization is achieved using a Proportional-Integral (PI) algorithm, that calculates the error between the measured ZCD and the ideal ZCD.

## Release Notes

Current version 1.1.0 features:

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

- [MPLAB® X IDE v6.25 or newer](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_AVR-EB&utm_content=avr16eb32-bldc-pmsm-motor-control-library-github&utm_bu=MCU08)
- [AVR-Ex DFP v2.11.221 or newer](https://packs.download.microchip.com/)
- [AVR-Dx DFP v2.7.321 or newer](https://packs.download.microchip.com/)
- [AVR-ATmega DFP v3.4.282 or newer](https://packs.download.microchip.com/)
- [MPLAB® XC8 compiler v3.00 or newer](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_AVR-EB&utm_content=avr16eb32-bldc-pmsm-motor-control-library-github&utm_bu=MCU08)
- [MPLAB Code Configurator (MCC) v5.6.2 or newer](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator)

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
  - ACT57BLF02
  - SZSPEED 2207 KV 2500
  - 130K RPM 12V low cost hair-dryer motor
  - Hurst DMA0204024B101
  - Hurst DMA0002024C1010

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

| Pin Name       | AVR16EB32 Curiosity Nano Board | AVR128DA48 Curiosity Nano Board | ATmega4809 Curiosity Nano Board | MPPB Board                  |
|----------------|--------------------------------|---------------------------------|---------------------------------|-----------------------------|
|Drive A High    |Pin 9 -  PA0                    |Pin 7 -  PA0                     |Pin 7 -   PA0                    |Pin 26                       |
|Drive A Low     |Pin 10 - PA1                    |Pin 20 - PB0                     |Pin 10 -  PA3                    |Pin 25                       |
|Drive B High    |Pin 7 -  PA2                    |Pin 8 -  PA1                     |Pin 8 -   PA1                    |Pin 24                       |
|Drive B Low     |Pin 8 -  PA3                    |Pin 21 - PB1                     |Pin 11 -  PA4                    |Pin 23                       |
|Drive C High    |Pin 11 - PA4                    |Pin 36 - PA2                     |Pin 9 -   PA2                    |Pin 22                       |
|Drive C Low     |Pin 12 - PA5                    |Pin 22 - PB2                     |Pin 12 -  PA5                    |Pin 21                       |
|Feedback A      |Pin 35 - PD4                    |Pin 49 - PD6                     |Pin 45 -  PD2                    |Pin 12                       |
|Feedback B      |Pin 36 - PD5                    |Pin 48 - PD2                     |Pin 47 -  PD4                    |Pin 10                       |
|Feedback C      |Pin 29 - PD6                    |Pin 44 - PD4                     |Pin 49 -  PD6                    |Pin 8                        |
|Feedback N      |Pin 31 - PD0                    |Pin 50 - PD7                     |Pin 50 -  PD7                    |Pin 4                        |
|Current Sense   |Pin 34 - PD3                    |Pin 40 - PE2                     |Pin 43 -  PD0                    |Pin 7                        |
|Current Trip    |Pin 34 - PD3                    |Pin 40 - PE2                     |Pin 41 -  PC7                    | -                           |
|V Supply Monitor|Pin 27 - PF4                    |Pin 46 - PD0                     |Pin 25 -  PE0                    |Pin 9                        |
|Potentiometer   |Pin 32 - PD1                    |Pin 47 - PD1                     |Pin 27 -  PE2                    |Pin 29                       |
|LED             |Pin 21 - PF5                    |Pin 27 - PC6                     |Pin 32 -  PF5                    |Pin 33                       |
|Switch          |Pin 20 - PF6                    |Pin 28 - PC7                     |Pin 54 -  PF6                    |Pin 35                       |
|PWM IN          |Pin 23 - PF0                    |Pin 37 - PA3                     |Pin 28  - PE3                    |Pin 18                       |
|TXC             |Pin 16 - PC1                    |Pin 25 - PC0                     |Pin 20 -  PB0                    | -                           |
|RXC             |Pin 17 - PC2                    |Pin 26 - PC1                     |Pin 21 -  PB1                    | -                           |
|3V3             |Pin 37                          |Pin 51                           |Pin 51                           |Pin 39                       |
|VOFF            |Pin 41                          |Pin 55                           |Pin 55                           |Pin 38                       |
|GND             |Pins 38, 28, 15                 |Pins 52, 42, 33, 24, 15          |Pins 52, 42, 33, 24, 15          |Pins 40, 28, 27, 14, 13, 2, 1|

<br><b>Note:</b> In this repository, schematics for all three platforms are provided in the `pdf` folder:
 - AVR16EB32_MPPB_Mapping
 - AVR128DA48_MPPB_Mapping
 - ATMEGA4809_MPPB_Mapping
</br>

### Necessary Hardware Tweaks

<br> This demo requires adding three SMD capacitors of 3.3 nF each with the size of 0402 on the MPPB board, one for each motor phases, as explained below.

<br> Because this demo counts on capturing the BEMF using a hardware capture mechanism of a timer, the captured signals need filtering to remove false zero-cross detection. The easiest method to do this is by using a RC low-pass filter. The MPPB board has placeholder pads for the capacitors that need to be added. The capacitor for virtual neutral point is already in place, and the capacitor values for phases A, B and C must have the value of 3.3 nF (three times smaller than the one from virtual neutral, which has 10 nF). With these capacitor values, the resulted RC filters will add a 30 µs delay to the zero-cross detection.

<h3> Capacitors location marked with green rectangles </h3>

<br><br><img src="images/rc_caps_add.png">

<h3> Capacitors location zoomed in</h3>

<br><br><img src="images/hardware_rc_zoomed.png">

### Configuration Settings

<br>This is a set of configuration settings, apart from the default values, needed to run the demo in the Trapezoidal Sensorless mode with the ACT42BLF01 motor.
<br>In the configuration file [`config.h`](#configurable-parameters) edit the settings according to the usage scenario. 

<br><h3> Configuration Settings for the ACT42BLF01 Motor </h3>

```c

/* Analog module settings */
#define ADC_IIR_FILTER                  true         /* Smoothing filter on ADC functions: POT, VBUS, current */

/* Application settings */
#define PWM_IN_PERIOD                   (20.0)       /* ms */
#define PWM_IN_MAX_DCY                  ( 2.1)       /* ms */
#define PWM_IN_MIN_DCY                  ( 0.9)       /* ms */

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
```

<br><b>Note:</b> In the `config_examples` folder there are `config.h` example files, one for each motor used in testing this demo. Copy the variant of the `config.h` file corresponding to the desired motor and place it in one of the following projects: `fw/motor_demo_eb.X`, `fw/motor_demo_da.X` or `fw/motor_demo_eb.X`. The copied configuration file will overwrite the old one.</br>

## Application Usage

### Let's Spin the Motor

After all the steps from [Quick Start Guide](#quick-start-guide) are completed, turn the MPPB potentiometer to 50%, then press the MPPB button to spin the motor.
The spinning direction depends on the wiring of the phases.

### Tunning Guide

After following all the steps from [Quick Start Guide](#quick-start-guide) and the motor is not yet spining, or an error message is displayed in the console, these are some useful steps to try to tune the application for a new motor:

1. Measure the phase-to-phase resistance between any two wires of the motor. Put this value in `MOTOR_RPP`, from the `config.h` file.
2. Disable the speed regulator by setting `MOTOR_SPEED_REGULATOR_EN` to `false`.
3. The initial value for `MOTOR_STARTUP_CURRENT` can be close to the rated current of the motor.
4. If the motor is not spinning after the first two steps and reprogramming, set `MOTOR_STARTUP_TIME` to `-1` and `MOTOR_FORCED` to `true`, to put the motor in Forced Commutation mode. Try to increase `MOTOR_STARTUP_CURRENT` by 0.5A and reprogram until the motor starts spinning. After the motor is spinning in Forced mode without vibrations, set `MOTOR_STARTUP_TIME` to the initial value and `MOTOR_FORCED` back to `false`.
5. `MOTOR_ALIGNMENT_DURATION` can also be adjusted. For example, for a drone motor with low inductance, the alignment period is much smaller compared to a motor with high inductance. Try to increase or decrease the duration with steps not greater than 10 ms at a time.
6. `MOTOR_AMPRAMP_STEP_INTERVAL` can also be adjusted. This parameter establishes how aggresive the ramp-up process is. Lower values of this parameter means more aggresive ramp. For motors with low inductance and high speeds, the ramp can be more aggresive compared to a motor with high inductance. Try to increase or decrease the duration with steps no greater than 5 ms at a time.
7. After getting the motor spinning, set back the parameter `MOTOR_SPEED_REGULATOR_EN` to `true`.
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

All the files shared by the three platforms are in the `common_files` folder. Each platform has its own `main.c`, `config.h` and `mcc_mapping.h` files.
```
   fw
    ├───common_files
    │   │   app.c
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
    │   │   config.h
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
    │   │   config.h
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
        │   config.h
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

<br><b> Motor Settings </b>

<br>• <b>`MOTOR_PHASE_ADVANCE`</b> - Sets the value of the phase drive advance, and takes values between `0` and `30` electrical degrees. This parameter is used to improve the motor efficiency and performance at higher speeds by advancing the phase of the applied voltage relative to the BEMF of the motor, effectively shifting the timing of the current flow. Tune this according to the motor used.
<br>• <b>`MOTOR_STARTUP_CURRENT`</b> - The amount of current supplied to the motor phases during the start-up phase, given in amperes
<br>• <b>`MOTOR_RPP`</b> - Motor resistance measured phase-to-phase
<br>• <b>`MOTOR_AMP_RAMP_RATE`</b> - Amplitude increase rate; the higher the number, the slower the rate is
<br>• <b>`MOTOR_ALIGNMENT_DURATION`</b> - Initial alignment duration before start-up
<br>• <b>`MOTOR_MAXIMUM_ERPM`</b> - Limit speed value of the motor given in electrical RPM
<br>• <b>`MOTOR_SPEED_REGULATOR_EN`</b> - Enables or disables the Closed Loop speed regulator
<br>• <b>`REGULATOR_MAX_SPEED`</b> - Sets the maximum speed for the speed regulator
<br>• <b>`REGULATOR_MIN_SPEED`</b> - Sets the minimum speed for the speed regulator
<br>• <b>`REGULATOR_PI_KP`</b> - Proportional term constant parameter used by the speed regulator. It can have values between `0.0` and `1.0`. Tune this according to the motor used.
<br>• <b>`REGULATOR_PI_KI`</b> - Integral term constant parameter used by the speed regulator. It can have values between `0.0` and `1.0`. Tune this according to the motor used.
<br>• <b>`MOTOR_STARTUP_TIME`</b> - This is the waiting time until the value from the `Motor_CommandSet()` is used to set the amplitude or reference speed. If this parameter is set to '-1', then the value written by `Motor_CommandSet()` is ignored.
<br>• <b>`MOTOR_FORCED`</b> - Setting this parameter to `true` enables only forced commutation. Setting it to `false` enables motor synchronization.
<br>• <b>`STALL_DETECTION_DISABLED`</b> - Enables or disables the stall detection mechanism
<br>• <b>`STALL_DETECTION_THRESHOLD`</b> - The number of reached stall conditions until the motor is stopped. It can take values between `0` and `255`.

<br><b> Power Board and Analog Settigs </b>

<br>• <b>`CURRENT_SHUNT_RESISTANCE`</b> - The current sense shunt resistance, given in ohms, dependent on the power board
<br>• <b>`CURRENT_AMPLIFIER_GAIN`</b> - The current sense amplifier, dependent on the power board
<br>• <b>`VBUS_DIVIDER`</b> - The voltage divider, used to scale the V<sub>BUS</sub> to be able to measure it with the `ANALOG_REFERENCE` logic, dependent on the power board
<br>• <b>`ANALOG_REFERENCE`</b> - The voltage reference (this application has a 3V3 logic)
<br>• <b>`CURRENT_AMPLIFIER_OFFSET`</b> - Typical offset is half of `ANALOG_REFERENCE`. This parameter is used when calculating the current value. For the MPPB board, the limit values of the current are between [-7.33A, +7.33A].
<br>• <b>`ADC_VBUS_TRIP`</b> - Sets the ADC trip level in case of an overvoltage protection, expressed in millivolts
<br>• <b>`ADC_CURRENT_TRIP`</b> - Sets the ADC trip level in case of an average overcurrent protection, expressed in milliamperes
<br>• <b>`COMPARATOR_CURRENT_TRIP`</b> - Sets the internal comparator's trip level in case of a peak overcurrent protection. This parameter does not have any effect for the external comparator configuration, specifically for the ATmega4809 configuration.
<br>• <b>`FAULT_COMPARATOR_EN`</b> - Enables or disables the comparator used for current trip. For AVR16EB32 and AVR128DA48, this mechanism is implemented using an internal comparator. For ATmega4809, the support is implemented for an external comparator, which must be added to use it.
<br>• <b>`ADC_IIR_FILTER`</b> - Enables or disables a smoothing filter for analog measurements: potentiometer, voltage bus and current. This filter is used only for displaying values, not by fault or other mechanism that requires a fast response.
<br>• <b>`PWM_IN_PERIOD`</b> - Represents the period of the PWM input signal, compatible with radio-controlled receivers, that can be used to set the speed reference in Closed-Loop, or the PWM amplitude reference in Open-Loop. The standard value of this parameter in 20 milliseconds.
<br>• <b>`PWM_IN_MAX_DCY`</b> - Represents the maximum `ON` time of the PWM input signal and is equivalent to setting the maximum reference. The standard value of this parameter is 2 milliseconds, but it can be tuned accordingly to eventual tolerances.
<br>• <b>`PWM_IN_MIN_DCY`</b> - Represents the minimum `ON` time of the PWM input signal and is equivalent to setting the minimum reference. The standard value of this parameter is 1 millisecond, but it can be tuned accordingly to eventual tolerances.

<br> With the initial values, the motor will operate, although performance may not be optimal. However, these settings provide a good starting point for further tuning to meet the requirements of a custom application.

### Application Interrupt Window Time

<br><img src="images/interrupt_window_time.png">

<br> <b>Note:</b> The Sector Change interrupt has a higher priority and will preempt running other interrupts increasing their overall execution time, or will delay other interrupts. One sector duration represents one sixth of one electrical revolution. The duration of one electrical revolution is inverse proportional with the rotational speed, expressed in revolutions per second. 

### Motor Drive Sequence

<br><img src="images/drive_sequence.png">

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

<br> Synchronization is achieved using a simplified Proportional Integral Derivative (PID) algorithm that calculates the error between the ideal zero-cross of BEMF, which is always set to half of the timer's period, and the actual zero-cross, that is acquired using a timer's hardware capture mechanism. The algorithm only has the proportional and the integral terms, but no derivative. The algorithm also uses a little bit of phase advance ```(timerPeriod >> 3)``` that is added to the ```setValue```, which is half of the period.
<br>The advantage of this algorithm is that it is based on bit-shifting operations, and it does not add much CPU overload and interrupt time to process all the data. Using this algorithm greatly reduces the speed oscillations.

<h4> Synchronization Algorithm Timing </h4>

<br><img src="images/synchronization_pi_timing.png">

<h4> Synchronization Algorithm Chart </h4>

<br><img src="images/synchronization_pi_chart.png">

### Motor Speed Regulator Algorithm

<br> Speed regulation in Closed-Loop is achieved using a simplified PID algorithm that calculates the error between the target speed and measured speed. The algorithm only has the proportional and the integral terms, but no derivative. The target speed value is in the range between `REGULATOR_MIN_SPEED` and `REGULATOR_MAX_SPEED`. The measured speed is acquired by counting the sector change events during a fixed period of time. The values of `REGULATOR_PI_KP` and `REGULATOR_PI_KI` constants can be tuned to achieve a desired behaviour, depending on the motor used. The values of the two constants must be positive and lower than or equal to `1.0`.

<h4> Speed Regulator Algorithm Chart </h4>

<br><img src="images/speed_pi_chart.png">

## Results
|   | Ch 1 (Yellow Trace)  Phase Voltage    |     | Ch 2 (Blue Trace) Phase Current       |
|---|---------------------------------------|-----|---------------------------------------|
| A | <img src="images/ACT42BLF01.png">     |  B  | <img src="images/ACT57BLF02.png">     |
| C | <img src="images/HD_12V_130KRPM.png"> |  D  | <img src="images/SZSPEED_2500KV.png"> |

| Motor    | Brief Specifications        | Supply Voltage [V] | Current Consumption [A] | e-RPM at 100% Duty Cycle | Voltage  Graphs |
|:--------:|:---------------------------:|:------------------:|:-----------------------:|:------------------------:|----------------:|
|ACT42BLF01| 24V/1.9A/4ppoles/4kRPM      |    24              |      0.205 (no load)    |       22,500             |  Fig A          |
|ACT57BLF02| 24V/4.0A/4ppoles/3kRPM      |    24              |      0.530 (no load)    |       18,000             |  Fig B          |
|Hair Dryer| 12V/150W/1ppole/130kRPM     |     8              |      8.5 (original fan) |      120,000             |  Fig C          |
|A2207 KV2500| 16.8V/920W/7ppoles/30kRPM |     6              |      1.3 (no load)      |      106,000             |  Fig D          |

## Summary

<br>This project provides support for spinning a BLDC/PMSM motor using the Trapezoidal Drive method and feedback from the BEMF ZCD to achieve motor synchronization in an Open-Loop configuration. The control algorithm is straightforward and robust and it can be implemented on a variety of low-end MCUs that have a few timer capabilities, such as an analog comparator and an ADC.
