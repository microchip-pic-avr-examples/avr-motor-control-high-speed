/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  1.1.0
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

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

#ifndef PINS_H_INCLUDED
#define PINS_H_INCLUDED

#include <avr/io.h>
#include "./port.h"

//get/set BEMF_N aliases
#define BEMF_N_SetHigh() do { PORTD_OUTSET = 0x1; } while(0)
#define BEMF_N_SetLow() do { PORTD_OUTCLR = 0x1; } while(0)
#define BEMF_N_Toggle() do { PORTD_OUTTGL = 0x1; } while(0)
#define BEMF_N_GetValue() (VPORTD.IN & (0x1 << 0))
#define BEMF_N_SetDigitalInput() do { PORTD_DIRCLR = 0x1; } while(0)
#define BEMF_N_SetDigitalOutput() do { PORTD_DIRSET = 0x1; } while(0)
#define BEMF_N_SetPullUp() do { PORTD_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define BEMF_N_ResetPullUp() do { PORTD_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define BEMF_N_SetInverted() do { PORTD_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define BEMF_N_ResetInverted() do { PORTD_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define BEMF_N_DisableInterruptOnChange() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define BEMF_N_EnableInterruptForBothEdges() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define BEMF_N_EnableInterruptForRisingEdge() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define BEMF_N_EnableInterruptForFallingEdge() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define BEMF_N_DisableDigitalInputBuffer() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define BEMF_N_EnableInterruptForLowLevelSensing() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD0_SetInterruptHandler BEMF_N_SetInterruptHandler

//get/set BEMF_B aliases
#define BEMF_B_SetHigh() do { PORTD_OUTSET = 0x20; } while(0)
#define BEMF_B_SetLow() do { PORTD_OUTCLR = 0x20; } while(0)
#define BEMF_B_Toggle() do { PORTD_OUTTGL = 0x20; } while(0)
#define BEMF_B_GetValue() (VPORTD.IN & (0x1 << 5))
#define BEMF_B_SetDigitalInput() do { PORTD_DIRCLR = 0x20; } while(0)
#define BEMF_B_SetDigitalOutput() do { PORTD_DIRSET = 0x20; } while(0)
#define BEMF_B_SetPullUp() do { PORTD_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define BEMF_B_ResetPullUp() do { PORTD_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define BEMF_B_SetInverted() do { PORTD_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define BEMF_B_ResetInverted() do { PORTD_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define BEMF_B_DisableInterruptOnChange() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define BEMF_B_EnableInterruptForBothEdges() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define BEMF_B_EnableInterruptForRisingEdge() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define BEMF_B_EnableInterruptForFallingEdge() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define BEMF_B_DisableDigitalInputBuffer() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define BEMF_B_EnableInterruptForLowLevelSensing() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD5_SetInterruptHandler BEMF_B_SetInterruptHandler

//get/set CRT_P aliases
#define CRT_P_SetHigh() do { PORTD_OUTSET = 0x8; } while(0)
#define CRT_P_SetLow() do { PORTD_OUTCLR = 0x8; } while(0)
#define CRT_P_Toggle() do { PORTD_OUTTGL = 0x8; } while(0)
#define CRT_P_GetValue() (VPORTD.IN & (0x1 << 3))
#define CRT_P_SetDigitalInput() do { PORTD_DIRCLR = 0x8; } while(0)
#define CRT_P_SetDigitalOutput() do { PORTD_DIRSET = 0x8; } while(0)
#define CRT_P_SetPullUp() do { PORTD_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define CRT_P_ResetPullUp() do { PORTD_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define CRT_P_SetInverted() do { PORTD_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define CRT_P_ResetInverted() do { PORTD_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define CRT_P_DisableInterruptOnChange() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define CRT_P_EnableInterruptForBothEdges() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define CRT_P_EnableInterruptForRisingEdge() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define CRT_P_EnableInterruptForFallingEdge() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define CRT_P_DisableDigitalInputBuffer() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define CRT_P_EnableInterruptForLowLevelSensing() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD3_SetInterruptHandler CRT_P_SetInterruptHandler

//get/set POT aliases
#define POT_SetHigh() do { PORTD_OUTSET = 0x2; } while(0)
#define POT_SetLow() do { PORTD_OUTCLR = 0x2; } while(0)
#define POT_Toggle() do { PORTD_OUTTGL = 0x2; } while(0)
#define POT_GetValue() (VPORTD.IN & (0x1 << 1))
#define POT_SetDigitalInput() do { PORTD_DIRCLR = 0x2; } while(0)
#define POT_SetDigitalOutput() do { PORTD_DIRSET = 0x2; } while(0)
#define POT_SetPullUp() do { PORTD_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define POT_ResetPullUp() do { PORTD_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define POT_SetInverted() do { PORTD_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define POT_ResetInverted() do { PORTD_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define POT_DisableInterruptOnChange() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define POT_EnableInterruptForBothEdges() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define POT_EnableInterruptForRisingEdge() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define POT_EnableInterruptForFallingEdge() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define POT_DisableDigitalInputBuffer() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define POT_EnableInterruptForLowLevelSensing() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD1_SetInterruptHandler POT_SetInterruptHandler

//get/set BEMF_A aliases
#define BEMF_A_SetHigh() do { PORTD_OUTSET = 0x10; } while(0)
#define BEMF_A_SetLow() do { PORTD_OUTCLR = 0x10; } while(0)
#define BEMF_A_Toggle() do { PORTD_OUTTGL = 0x10; } while(0)
#define BEMF_A_GetValue() (VPORTD.IN & (0x1 << 4))
#define BEMF_A_SetDigitalInput() do { PORTD_DIRCLR = 0x10; } while(0)
#define BEMF_A_SetDigitalOutput() do { PORTD_DIRSET = 0x10; } while(0)
#define BEMF_A_SetPullUp() do { PORTD_PIN4CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define BEMF_A_ResetPullUp() do { PORTD_PIN4CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define BEMF_A_SetInverted() do { PORTD_PIN4CTRL  |= PORT_INVEN_bm; } while(0)
#define BEMF_A_ResetInverted() do { PORTD_PIN4CTRL  &= ~PORT_INVEN_bm; } while(0)
#define BEMF_A_DisableInterruptOnChange() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define BEMF_A_EnableInterruptForBothEdges() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define BEMF_A_EnableInterruptForRisingEdge() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define BEMF_A_EnableInterruptForFallingEdge() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define BEMF_A_DisableDigitalInputBuffer() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define BEMF_A_EnableInterruptForLowLevelSensing() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD4_SetInterruptHandler BEMF_A_SetInterruptHandler

//get/set BEMF_C aliases
#define BEMF_C_SetHigh() do { PORTD_OUTSET = 0x40; } while(0)
#define BEMF_C_SetLow() do { PORTD_OUTCLR = 0x40; } while(0)
#define BEMF_C_Toggle() do { PORTD_OUTTGL = 0x40; } while(0)
#define BEMF_C_GetValue() (VPORTD.IN & (0x1 << 6))
#define BEMF_C_SetDigitalInput() do { PORTD_DIRCLR = 0x40; } while(0)
#define BEMF_C_SetDigitalOutput() do { PORTD_DIRSET = 0x40; } while(0)
#define BEMF_C_SetPullUp() do { PORTD_PIN6CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define BEMF_C_ResetPullUp() do { PORTD_PIN6CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define BEMF_C_SetInverted() do { PORTD_PIN6CTRL  |= PORT_INVEN_bm; } while(0)
#define BEMF_C_ResetInverted() do { PORTD_PIN6CTRL  &= ~PORT_INVEN_bm; } while(0)
#define BEMF_C_DisableInterruptOnChange() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define BEMF_C_EnableInterruptForBothEdges() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define BEMF_C_EnableInterruptForRisingEdge() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define BEMF_C_EnableInterruptForFallingEdge() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define BEMF_C_DisableDigitalInputBuffer() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define BEMF_C_EnableInterruptForLowLevelSensing() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD6_SetInterruptHandler BEMF_C_SetInterruptHandler

//get/set VBUS aliases
#define VBUS_SetHigh() do { PORTF_OUTSET = 0x10; } while(0)
#define VBUS_SetLow() do { PORTF_OUTCLR = 0x10; } while(0)
#define VBUS_Toggle() do { PORTF_OUTTGL = 0x10; } while(0)
#define VBUS_GetValue() (VPORTF.IN & (0x1 << 4))
#define VBUS_SetDigitalInput() do { PORTF_DIRCLR = 0x10; } while(0)
#define VBUS_SetDigitalOutput() do { PORTF_DIRSET = 0x10; } while(0)
#define VBUS_SetPullUp() do { PORTF_PIN4CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define VBUS_ResetPullUp() do { PORTF_PIN4CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define VBUS_SetInverted() do { PORTF_PIN4CTRL  |= PORT_INVEN_bm; } while(0)
#define VBUS_ResetInverted() do { PORTF_PIN4CTRL  &= ~PORT_INVEN_bm; } while(0)
#define VBUS_DisableInterruptOnChange() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define VBUS_EnableInterruptForBothEdges() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define VBUS_EnableInterruptForRisingEdge() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define VBUS_EnableInterruptForFallingEdge() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define VBUS_DisableDigitalInputBuffer() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define VBUS_EnableInterruptForLowLevelSensing() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF4_SetInterruptHandler VBUS_SetInterruptHandler

//get/set EVSYS_OUT aliases
#define EVSYS_OUT_SetHigh() do { PORTA_OUTSET = 0x80; } while(0)
#define EVSYS_OUT_SetLow() do { PORTA_OUTCLR = 0x80; } while(0)
#define EVSYS_OUT_Toggle() do { PORTA_OUTTGL = 0x80; } while(0)
#define EVSYS_OUT_GetValue() (VPORTA.IN & (0x1 << 7))
#define EVSYS_OUT_SetDigitalInput() do { PORTA_DIRCLR = 0x80; } while(0)
#define EVSYS_OUT_SetDigitalOutput() do { PORTA_DIRSET = 0x80; } while(0)
#define EVSYS_OUT_SetPullUp() do { PORTA_PIN7CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define EVSYS_OUT_ResetPullUp() do { PORTA_PIN7CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define EVSYS_OUT_SetInverted() do { PORTA_PIN7CTRL  |= PORT_INVEN_bm; } while(0)
#define EVSYS_OUT_ResetInverted() do { PORTA_PIN7CTRL  &= ~PORT_INVEN_bm; } while(0)
#define EVSYS_OUT_DisableInterruptOnChange() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define EVSYS_OUT_EnableInterruptForBothEdges() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define EVSYS_OUT_EnableInterruptForRisingEdge() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define EVSYS_OUT_EnableInterruptForFallingEdge() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define EVSYS_OUT_DisableDigitalInputBuffer() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define EVSYS_OUT_EnableInterruptForLowLevelSensing() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PA7_SetInterruptHandler EVSYS_OUT_SetInterruptHandler

//get/set DRIVE_H0 aliases
#define DRIVE_H0_SetHigh() do { PORTA_OUTSET = 0x1; } while(0)
#define DRIVE_H0_SetLow() do { PORTA_OUTCLR = 0x1; } while(0)
#define DRIVE_H0_Toggle() do { PORTA_OUTTGL = 0x1; } while(0)
#define DRIVE_H0_GetValue() (VPORTA.IN & (0x1 << 0))
#define DRIVE_H0_SetDigitalInput() do { PORTA_DIRCLR = 0x1; } while(0)
#define DRIVE_H0_SetDigitalOutput() do { PORTA_DIRSET = 0x1; } while(0)
#define DRIVE_H0_SetPullUp() do { PORTA_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define DRIVE_H0_ResetPullUp() do { PORTA_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define DRIVE_H0_SetInverted() do { PORTA_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define DRIVE_H0_ResetInverted() do { PORTA_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define DRIVE_H0_DisableInterruptOnChange() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define DRIVE_H0_EnableInterruptForBothEdges() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define DRIVE_H0_EnableInterruptForRisingEdge() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define DRIVE_H0_EnableInterruptForFallingEdge() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define DRIVE_H0_DisableDigitalInputBuffer() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define DRIVE_H0_EnableInterruptForLowLevelSensing() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PA0_SetInterruptHandler DRIVE_H0_SetInterruptHandler

//get/set DRIVE_L0 aliases
#define DRIVE_L0_SetHigh() do { PORTA_OUTSET = 0x2; } while(0)
#define DRIVE_L0_SetLow() do { PORTA_OUTCLR = 0x2; } while(0)
#define DRIVE_L0_Toggle() do { PORTA_OUTTGL = 0x2; } while(0)
#define DRIVE_L0_GetValue() (VPORTA.IN & (0x1 << 1))
#define DRIVE_L0_SetDigitalInput() do { PORTA_DIRCLR = 0x2; } while(0)
#define DRIVE_L0_SetDigitalOutput() do { PORTA_DIRSET = 0x2; } while(0)
#define DRIVE_L0_SetPullUp() do { PORTA_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define DRIVE_L0_ResetPullUp() do { PORTA_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define DRIVE_L0_SetInverted() do { PORTA_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define DRIVE_L0_ResetInverted() do { PORTA_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define DRIVE_L0_DisableInterruptOnChange() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define DRIVE_L0_EnableInterruptForBothEdges() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define DRIVE_L0_EnableInterruptForRisingEdge() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define DRIVE_L0_EnableInterruptForFallingEdge() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define DRIVE_L0_DisableDigitalInputBuffer() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define DRIVE_L0_EnableInterruptForLowLevelSensing() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PA1_SetInterruptHandler DRIVE_L0_SetInterruptHandler

//get/set DRIVE_H1 aliases
#define DRIVE_H1_SetHigh() do { PORTA_OUTSET = 0x4; } while(0)
#define DRIVE_H1_SetLow() do { PORTA_OUTCLR = 0x4; } while(0)
#define DRIVE_H1_Toggle() do { PORTA_OUTTGL = 0x4; } while(0)
#define DRIVE_H1_GetValue() (VPORTA.IN & (0x1 << 2))
#define DRIVE_H1_SetDigitalInput() do { PORTA_DIRCLR = 0x4; } while(0)
#define DRIVE_H1_SetDigitalOutput() do { PORTA_DIRSET = 0x4; } while(0)
#define DRIVE_H1_SetPullUp() do { PORTA_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define DRIVE_H1_ResetPullUp() do { PORTA_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define DRIVE_H1_SetInverted() do { PORTA_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define DRIVE_H1_ResetInverted() do { PORTA_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define DRIVE_H1_DisableInterruptOnChange() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define DRIVE_H1_EnableInterruptForBothEdges() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define DRIVE_H1_EnableInterruptForRisingEdge() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define DRIVE_H1_EnableInterruptForFallingEdge() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define DRIVE_H1_DisableDigitalInputBuffer() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define DRIVE_H1_EnableInterruptForLowLevelSensing() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PA2_SetInterruptHandler DRIVE_H1_SetInterruptHandler

//get/set DRIVE_L1 aliases
#define DRIVE_L1_SetHigh() do { PORTA_OUTSET = 0x8; } while(0)
#define DRIVE_L1_SetLow() do { PORTA_OUTCLR = 0x8; } while(0)
#define DRIVE_L1_Toggle() do { PORTA_OUTTGL = 0x8; } while(0)
#define DRIVE_L1_GetValue() (VPORTA.IN & (0x1 << 3))
#define DRIVE_L1_SetDigitalInput() do { PORTA_DIRCLR = 0x8; } while(0)
#define DRIVE_L1_SetDigitalOutput() do { PORTA_DIRSET = 0x8; } while(0)
#define DRIVE_L1_SetPullUp() do { PORTA_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define DRIVE_L1_ResetPullUp() do { PORTA_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define DRIVE_L1_SetInverted() do { PORTA_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define DRIVE_L1_ResetInverted() do { PORTA_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define DRIVE_L1_DisableInterruptOnChange() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define DRIVE_L1_EnableInterruptForBothEdges() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define DRIVE_L1_EnableInterruptForRisingEdge() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define DRIVE_L1_EnableInterruptForFallingEdge() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define DRIVE_L1_DisableDigitalInputBuffer() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define DRIVE_L1_EnableInterruptForLowLevelSensing() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PA3_SetInterruptHandler DRIVE_L1_SetInterruptHandler

//get/set DRIVE_H2 aliases
#define DRIVE_H2_SetHigh() do { PORTA_OUTSET = 0x10; } while(0)
#define DRIVE_H2_SetLow() do { PORTA_OUTCLR = 0x10; } while(0)
#define DRIVE_H2_Toggle() do { PORTA_OUTTGL = 0x10; } while(0)
#define DRIVE_H2_GetValue() (VPORTA.IN & (0x1 << 4))
#define DRIVE_H2_SetDigitalInput() do { PORTA_DIRCLR = 0x10; } while(0)
#define DRIVE_H2_SetDigitalOutput() do { PORTA_DIRSET = 0x10; } while(0)
#define DRIVE_H2_SetPullUp() do { PORTA_PIN4CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define DRIVE_H2_ResetPullUp() do { PORTA_PIN4CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define DRIVE_H2_SetInverted() do { PORTA_PIN4CTRL  |= PORT_INVEN_bm; } while(0)
#define DRIVE_H2_ResetInverted() do { PORTA_PIN4CTRL  &= ~PORT_INVEN_bm; } while(0)
#define DRIVE_H2_DisableInterruptOnChange() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define DRIVE_H2_EnableInterruptForBothEdges() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define DRIVE_H2_EnableInterruptForRisingEdge() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define DRIVE_H2_EnableInterruptForFallingEdge() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define DRIVE_H2_DisableDigitalInputBuffer() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define DRIVE_H2_EnableInterruptForLowLevelSensing() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PA4_SetInterruptHandler DRIVE_H2_SetInterruptHandler

//get/set DRIVE_L2 aliases
#define DRIVE_L2_SetHigh() do { PORTA_OUTSET = 0x20; } while(0)
#define DRIVE_L2_SetLow() do { PORTA_OUTCLR = 0x20; } while(0)
#define DRIVE_L2_Toggle() do { PORTA_OUTTGL = 0x20; } while(0)
#define DRIVE_L2_GetValue() (VPORTA.IN & (0x1 << 5))
#define DRIVE_L2_SetDigitalInput() do { PORTA_DIRCLR = 0x20; } while(0)
#define DRIVE_L2_SetDigitalOutput() do { PORTA_DIRSET = 0x20; } while(0)
#define DRIVE_L2_SetPullUp() do { PORTA_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define DRIVE_L2_ResetPullUp() do { PORTA_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define DRIVE_L2_SetInverted() do { PORTA_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define DRIVE_L2_ResetInverted() do { PORTA_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define DRIVE_L2_DisableInterruptOnChange() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define DRIVE_L2_EnableInterruptForBothEdges() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define DRIVE_L2_EnableInterruptForRisingEdge() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define DRIVE_L2_EnableInterruptForFallingEdge() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define DRIVE_L2_DisableDigitalInputBuffer() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define DRIVE_L2_EnableInterruptForLowLevelSensing() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PA5_SetInterruptHandler DRIVE_L2_SetInterruptHandler

//get/set RX0 aliases
#define RX0_SetHigh() do { PORTC_OUTSET = 0x4; } while(0)
#define RX0_SetLow() do { PORTC_OUTCLR = 0x4; } while(0)
#define RX0_Toggle() do { PORTC_OUTTGL = 0x4; } while(0)
#define RX0_GetValue() (VPORTC.IN & (0x1 << 2))
#define RX0_SetDigitalInput() do { PORTC_DIRCLR = 0x4; } while(0)
#define RX0_SetDigitalOutput() do { PORTC_DIRSET = 0x4; } while(0)
#define RX0_SetPullUp() do { PORTC_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define RX0_ResetPullUp() do { PORTC_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define RX0_SetInverted() do { PORTC_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define RX0_ResetInverted() do { PORTC_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define RX0_DisableInterruptOnChange() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define RX0_EnableInterruptForBothEdges() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define RX0_EnableInterruptForRisingEdge() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define RX0_EnableInterruptForFallingEdge() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define RX0_DisableDigitalInputBuffer() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define RX0_EnableInterruptForLowLevelSensing() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PC2_SetInterruptHandler RX0_SetInterruptHandler

//get/set TX0 aliases
#define TX0_SetHigh() do { PORTC_OUTSET = 0x2; } while(0)
#define TX0_SetLow() do { PORTC_OUTCLR = 0x2; } while(0)
#define TX0_Toggle() do { PORTC_OUTTGL = 0x2; } while(0)
#define TX0_GetValue() (VPORTC.IN & (0x1 << 1))
#define TX0_SetDigitalInput() do { PORTC_DIRCLR = 0x2; } while(0)
#define TX0_SetDigitalOutput() do { PORTC_DIRSET = 0x2; } while(0)
#define TX0_SetPullUp() do { PORTC_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define TX0_ResetPullUp() do { PORTC_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define TX0_SetInverted() do { PORTC_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define TX0_ResetInverted() do { PORTC_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define TX0_DisableInterruptOnChange() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define TX0_EnableInterruptForBothEdges() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define TX0_EnableInterruptForRisingEdge() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define TX0_EnableInterruptForFallingEdge() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define TX0_DisableDigitalInputBuffer() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define TX0_EnableInterruptForLowLevelSensing() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PC1_SetInterruptHandler TX0_SetInterruptHandler

//get/set BUTTON aliases
#define BUTTON_SetHigh() do { PORTF_OUTSET = 0x40; } while(0)
#define BUTTON_SetLow() do { PORTF_OUTCLR = 0x40; } while(0)
#define BUTTON_Toggle() do { PORTF_OUTTGL = 0x40; } while(0)
#define BUTTON_GetValue() (VPORTF.IN & (0x1 << 6))
#define BUTTON_SetDigitalInput() do { PORTF_DIRCLR = 0x40; } while(0)
#define BUTTON_SetDigitalOutput() do { PORTF_DIRSET = 0x40; } while(0)
#define BUTTON_SetPullUp() do { PORTF_PIN6CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define BUTTON_ResetPullUp() do { PORTF_PIN6CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define BUTTON_SetInverted() do { PORTF_PIN6CTRL  |= PORT_INVEN_bm; } while(0)
#define BUTTON_ResetInverted() do { PORTF_PIN6CTRL  &= ~PORT_INVEN_bm; } while(0)
#define BUTTON_DisableInterruptOnChange() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define BUTTON_EnableInterruptForBothEdges() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define BUTTON_EnableInterruptForRisingEdge() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define BUTTON_EnableInterruptForFallingEdge() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define BUTTON_DisableDigitalInputBuffer() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define BUTTON_EnableInterruptForLowLevelSensing() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF6_SetInterruptHandler BUTTON_SetInterruptHandler

//get/set DBG_0 aliases
#define DBG_0_SetHigh() do { PORTF_OUTSET = 0x1; } while(0)
#define DBG_0_SetLow() do { PORTF_OUTCLR = 0x1; } while(0)
#define DBG_0_Toggle() do { PORTF_OUTTGL = 0x1; } while(0)
#define DBG_0_GetValue() (VPORTF.IN & (0x1 << 0))
#define DBG_0_SetDigitalInput() do { PORTF_DIRCLR = 0x1; } while(0)
#define DBG_0_SetDigitalOutput() do { PORTF_DIRSET = 0x1; } while(0)
#define DBG_0_SetPullUp() do { PORTF_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define DBG_0_ResetPullUp() do { PORTF_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define DBG_0_SetInverted() do { PORTF_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define DBG_0_ResetInverted() do { PORTF_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define DBG_0_DisableInterruptOnChange() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define DBG_0_EnableInterruptForBothEdges() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define DBG_0_EnableInterruptForRisingEdge() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define DBG_0_EnableInterruptForFallingEdge() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define DBG_0_DisableDigitalInputBuffer() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define DBG_0_EnableInterruptForLowLevelSensing() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF0_SetInterruptHandler DBG_0_SetInterruptHandler

//get/set DBG_1 aliases
#define DBG_1_SetHigh() do { PORTF_OUTSET = 0x2; } while(0)
#define DBG_1_SetLow() do { PORTF_OUTCLR = 0x2; } while(0)
#define DBG_1_Toggle() do { PORTF_OUTTGL = 0x2; } while(0)
#define DBG_1_GetValue() (VPORTF.IN & (0x1 << 1))
#define DBG_1_SetDigitalInput() do { PORTF_DIRCLR = 0x2; } while(0)
#define DBG_1_SetDigitalOutput() do { PORTF_DIRSET = 0x2; } while(0)
#define DBG_1_SetPullUp() do { PORTF_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define DBG_1_ResetPullUp() do { PORTF_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define DBG_1_SetInverted() do { PORTF_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define DBG_1_ResetInverted() do { PORTF_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define DBG_1_DisableInterruptOnChange() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define DBG_1_EnableInterruptForBothEdges() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define DBG_1_EnableInterruptForRisingEdge() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define DBG_1_EnableInterruptForFallingEdge() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define DBG_1_DisableDigitalInputBuffer() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define DBG_1_EnableInterruptForLowLevelSensing() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF1_SetInterruptHandler DBG_1_SetInterruptHandler

//get/set DBG_2 aliases
#define DBG_2_SetHigh() do { PORTF_OUTSET = 0x4; } while(0)
#define DBG_2_SetLow() do { PORTF_OUTCLR = 0x4; } while(0)
#define DBG_2_Toggle() do { PORTF_OUTTGL = 0x4; } while(0)
#define DBG_2_GetValue() (VPORTF.IN & (0x1 << 2))
#define DBG_2_SetDigitalInput() do { PORTF_DIRCLR = 0x4; } while(0)
#define DBG_2_SetDigitalOutput() do { PORTF_DIRSET = 0x4; } while(0)
#define DBG_2_SetPullUp() do { PORTF_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define DBG_2_ResetPullUp() do { PORTF_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define DBG_2_SetInverted() do { PORTF_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define DBG_2_ResetInverted() do { PORTF_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define DBG_2_DisableInterruptOnChange() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define DBG_2_EnableInterruptForBothEdges() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define DBG_2_EnableInterruptForRisingEdge() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define DBG_2_EnableInterruptForFallingEdge() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define DBG_2_DisableDigitalInputBuffer() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define DBG_2_EnableInterruptForLowLevelSensing() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF2_SetInterruptHandler DBG_2_SetInterruptHandler

//get/set DBG_3 aliases
#define DBG_3_SetHigh() do { PORTF_OUTSET = 0x8; } while(0)
#define DBG_3_SetLow() do { PORTF_OUTCLR = 0x8; } while(0)
#define DBG_3_Toggle() do { PORTF_OUTTGL = 0x8; } while(0)
#define DBG_3_GetValue() (VPORTF.IN & (0x1 << 3))
#define DBG_3_SetDigitalInput() do { PORTF_DIRCLR = 0x8; } while(0)
#define DBG_3_SetDigitalOutput() do { PORTF_DIRSET = 0x8; } while(0)
#define DBG_3_SetPullUp() do { PORTF_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define DBG_3_ResetPullUp() do { PORTF_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define DBG_3_SetInverted() do { PORTF_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define DBG_3_ResetInverted() do { PORTF_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define DBG_3_DisableInterruptOnChange() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define DBG_3_EnableInterruptForBothEdges() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define DBG_3_EnableInterruptForRisingEdge() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define DBG_3_EnableInterruptForFallingEdge() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define DBG_3_DisableDigitalInputBuffer() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define DBG_3_EnableInterruptForLowLevelSensing() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF3_SetInterruptHandler DBG_3_SetInterruptHandler

//get/set LED aliases
#define LED_SetHigh() do { PORTF_OUTSET = 0x20; } while(0)
#define LED_SetLow() do { PORTF_OUTCLR = 0x20; } while(0)
#define LED_Toggle() do { PORTF_OUTTGL = 0x20; } while(0)
#define LED_GetValue() (VPORTF.IN & (0x1 << 5))
#define LED_SetDigitalInput() do { PORTF_DIRCLR = 0x20; } while(0)
#define LED_SetDigitalOutput() do { PORTF_DIRSET = 0x20; } while(0)
#define LED_SetPullUp() do { PORTF_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define LED_ResetPullUp() do { PORTF_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define LED_SetInverted() do { PORTF_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define LED_ResetInverted() do { PORTF_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define LED_DisableInterruptOnChange() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define LED_EnableInterruptForBothEdges() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define LED_EnableInterruptForRisingEdge() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define LED_EnableInterruptForFallingEdge() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define LED_DisableDigitalInputBuffer() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define LED_EnableInterruptForLowLevelSensing() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF5_SetInterruptHandler LED_SetInterruptHandler

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize();

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for BEMF_N pin. 
 *        This is a predefined interrupt handler to be used together with the BEMF_N_SetInterruptHandler() method.
 *        This handler is called every time the BEMF_N ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void BEMF_N_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for BEMF_N pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for BEMF_N at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void BEMF_N_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for BEMF_B pin. 
 *        This is a predefined interrupt handler to be used together with the BEMF_B_SetInterruptHandler() method.
 *        This handler is called every time the BEMF_B ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void BEMF_B_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for BEMF_B pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for BEMF_B at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void BEMF_B_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for CRT_P pin. 
 *        This is a predefined interrupt handler to be used together with the CRT_P_SetInterruptHandler() method.
 *        This handler is called every time the CRT_P ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void CRT_P_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for CRT_P pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for CRT_P at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void CRT_P_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for POT pin. 
 *        This is a predefined interrupt handler to be used together with the POT_SetInterruptHandler() method.
 *        This handler is called every time the POT ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void POT_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for POT pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for POT at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void POT_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for BEMF_A pin. 
 *        This is a predefined interrupt handler to be used together with the BEMF_A_SetInterruptHandler() method.
 *        This handler is called every time the BEMF_A ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void BEMF_A_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for BEMF_A pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for BEMF_A at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void BEMF_A_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for BEMF_C pin. 
 *        This is a predefined interrupt handler to be used together with the BEMF_C_SetInterruptHandler() method.
 *        This handler is called every time the BEMF_C ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void BEMF_C_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for BEMF_C pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for BEMF_C at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void BEMF_C_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for VBUS pin. 
 *        This is a predefined interrupt handler to be used together with the VBUS_SetInterruptHandler() method.
 *        This handler is called every time the VBUS ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void VBUS_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for VBUS pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for VBUS at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void VBUS_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for EVSYS_OUT pin. 
 *        This is a predefined interrupt handler to be used together with the EVSYS_OUT_SetInterruptHandler() method.
 *        This handler is called every time the EVSYS_OUT ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void EVSYS_OUT_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for EVSYS_OUT pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for EVSYS_OUT at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void EVSYS_OUT_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for DRIVE_H0 pin. 
 *        This is a predefined interrupt handler to be used together with the DRIVE_H0_SetInterruptHandler() method.
 *        This handler is called every time the DRIVE_H0 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void DRIVE_H0_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for DRIVE_H0 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for DRIVE_H0 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void DRIVE_H0_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for DRIVE_L0 pin. 
 *        This is a predefined interrupt handler to be used together with the DRIVE_L0_SetInterruptHandler() method.
 *        This handler is called every time the DRIVE_L0 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void DRIVE_L0_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for DRIVE_L0 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for DRIVE_L0 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void DRIVE_L0_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for DRIVE_H1 pin. 
 *        This is a predefined interrupt handler to be used together with the DRIVE_H1_SetInterruptHandler() method.
 *        This handler is called every time the DRIVE_H1 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void DRIVE_H1_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for DRIVE_H1 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for DRIVE_H1 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void DRIVE_H1_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for DRIVE_L1 pin. 
 *        This is a predefined interrupt handler to be used together with the DRIVE_L1_SetInterruptHandler() method.
 *        This handler is called every time the DRIVE_L1 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void DRIVE_L1_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for DRIVE_L1 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for DRIVE_L1 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void DRIVE_L1_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for DRIVE_H2 pin. 
 *        This is a predefined interrupt handler to be used together with the DRIVE_H2_SetInterruptHandler() method.
 *        This handler is called every time the DRIVE_H2 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void DRIVE_H2_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for DRIVE_H2 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for DRIVE_H2 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void DRIVE_H2_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for DRIVE_L2 pin. 
 *        This is a predefined interrupt handler to be used together with the DRIVE_L2_SetInterruptHandler() method.
 *        This handler is called every time the DRIVE_L2 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void DRIVE_L2_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for DRIVE_L2 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for DRIVE_L2 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void DRIVE_L2_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for RX0 pin. 
 *        This is a predefined interrupt handler to be used together with the RX0_SetInterruptHandler() method.
 *        This handler is called every time the RX0 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void RX0_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for RX0 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for RX0 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void RX0_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for TX0 pin. 
 *        This is a predefined interrupt handler to be used together with the TX0_SetInterruptHandler() method.
 *        This handler is called every time the TX0 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void TX0_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for TX0 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for TX0 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void TX0_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for BUTTON pin. 
 *        This is a predefined interrupt handler to be used together with the BUTTON_SetInterruptHandler() method.
 *        This handler is called every time the BUTTON ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void BUTTON_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for BUTTON pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for BUTTON at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void BUTTON_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for DBG_0 pin. 
 *        This is a predefined interrupt handler to be used together with the DBG_0_SetInterruptHandler() method.
 *        This handler is called every time the DBG_0 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void DBG_0_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for DBG_0 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for DBG_0 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void DBG_0_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for DBG_1 pin. 
 *        This is a predefined interrupt handler to be used together with the DBG_1_SetInterruptHandler() method.
 *        This handler is called every time the DBG_1 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void DBG_1_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for DBG_1 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for DBG_1 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void DBG_1_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for DBG_2 pin. 
 *        This is a predefined interrupt handler to be used together with the DBG_2_SetInterruptHandler() method.
 *        This handler is called every time the DBG_2 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void DBG_2_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for DBG_2 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for DBG_2 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void DBG_2_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for DBG_3 pin. 
 *        This is a predefined interrupt handler to be used together with the DBG_3_SetInterruptHandler() method.
 *        This handler is called every time the DBG_3 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void DBG_3_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for DBG_3 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for DBG_3 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void DBG_3_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for LED pin. 
 *        This is a predefined interrupt handler to be used together with the LED_SetInterruptHandler() method.
 *        This handler is called every time the LED ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void LED_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for LED pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for LED at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void LED_SetInterruptHandler(void (* interruptHandler)(void)) ; 
#endif /* PINS_H_INCLUDED */
