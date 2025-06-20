/**
 * TCB0 Generated Driver API Header File
 *
 * @file tcb0.h
 *
 * @defgroup tcb0 TCB0
 *
 * @brief This file contains the API prototypes and custom data types for the TCB0 driver.
 *
 * @version TCB0 Driver Version 1.2.0
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

#ifndef TCB0_H
#define TCB0_H

#include "../system/utils/compiler.h"
#include "./timer_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const struct TIMER_INTERFACE Timer_TCB0;

/**
 * @ingroup tcb0
 * @typedef void * TCB0_cb_t
 * @brief Function pointer to callback function called by the TCB. The default value is set to NULL which means that no callback function will be used.
 */
typedef void (* TCB0_cb_t)(void);

/**
 * @ingroup tcb0
 * @brief Registers a callback function to be called at Capture event.
 * @param TCB0_cb_t callback - Callback function for Capture event.
 * @return None.
 */
void TCB0_CaptureCallbackRegister(TCB0_cb_t const callback);

/**
 * @ingroup tcb0
 * @brief Initializes the TCB module
 * @param None.
 * @return None.
 */
void TCB0_Initialize(void);

/**
 * @ingroup tcb0
 * @brief Deinitializes the TCB module
 * @param None.
 * @return None.
 */
void TCB0_Deinitialize(void);

/**
 * @ingroup tcb0
 * @brief Starts the TCB counter.
 * @param None.
 * @return None.
 */
void TCB0_Start(void);

/**
 * @ingroup tcb0
 * @brief Stops the TCB counter.
 * @param None.
 * @return None.
 */
void TCB0_Stop(void);

/**
 * @ingroup tcb0
 * @brief Writes the 16-bit Counter value to the TCB.
 * @param uint16_t value - 16-bit Counter value to write
 * @return None.
 */
void TCB0_Write(uint16_t const value);

/**
 * @ingroup tcb0
 * @brief Reads the 16-bit Counter value of the TCB.
 * @param None.
 * @return uint16_t
 */
uint16_t TCB0_Read(void);

/**
 * @ingroup tcb0
 * @brief Writes the 16-bit Capture/Compare value to the TCB.
 * @param uint16_t value - 16-bit Capture/Compare value to write
 * @return None.
 */
void TCB0_CaptureCompareWrite(uint16_t const value);

/**
 * @ingroup tcb0
 * @brief Reads the 16-bit Capture/Compare value of the TCB.
 * @param None.
 * @return uint16_t
 */
uint16_t TCB0_CaptureCompareRead(void);

/**
 * @ingroup tcb0
 * @brief Enables the Capture Interrupt for the TCB.
 * @param None.
 * @return None.
 */
void TCB0_EnableCaptInterrupt(void);

/**
 * @ingroup tcb0
 * @brief Enables the Overflow Interrupt for the TCB.
 * @param None.
 * @return None.
 */
void TCB0_EnableOvfInterrupt(void);

/**
 * @ingroup tcb0
 * @brief Disables the Capture Interrupt for the TCB.
 * @param None.
 * @return None.
 */
void TCB0_DisableCaptInterrupt(void);

/**
 * @ingroup tcb0
 * @brief Disables the Overflow Interrupt for the TCB.
 * @param None.
 * @return None.
 */
void TCB0_DisableOvfInterrupt(void);

/**
 * @ingroup tcb0
 * @brief Checks if the Capture Interrupt flag is set.
 * @param None.
 * @return bool Whether the Capture Interrupt flag is set or not.
 */
bool TCB0_IsCaptInterruptFlagSet(void);

/**
 * @ingroup tcb0
 * @brief Checks if the Overflow Interrupt flag is set.
 * @param None.
 * @return bool Whether the Overflow Interrupt flag is set or not.
 */
bool TCB0_IsOvfInterruptFlagSet(void);

/**
 * @ingroup tcb0
 * @brief Clears the Capture Interrupt flag.
 * @param None.
 * @return None.
 */
void TCB0_ClearCaptInterruptFlag(void);

/**
 * @ingroup tcb0
 * @brief Clears the Overflow Interrupt flag.
 * @param None.
 * @return None.
 */
void TCB0_ClearOvfInterruptFlag(void);

/**
 * @ingroup tcb0
 * @brief Checks if the Capture Interrupt is enabled.
 * @param None.
 * @return bool Whether the Capture Interrupt is enabled or not.
 */
bool TCB0_IsCaptInterruptEnabled(void);

/**
 * @ingroup tcb0
 * @brief Checks if the Overflow Interrupt is enabled.
 * @param None.
 * @return bool Whether the Overflow Interrupt is enabled or not.
 */
bool TCB0_IsOvfInterruptEnabled(void);


#ifdef __cplusplus
}
#endif


#endif /* TCB0_H */
