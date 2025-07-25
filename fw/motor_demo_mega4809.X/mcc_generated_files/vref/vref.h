/**
 * VREF Generated Driver API Header File
 * 
 * @file vref.h
 * 
 * @defgroup  vref VREF
 * 
 * @brief This is the generated header file for the VREF module.
 *
 * @version VREF Driver Version 1.0.0
*/
/*
� [2025] Microchip Technology Inc. and its subsidiaries.

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


#ifndef VREF_H_INCLUDED
#define VREF_H_INCLUDED

/**
  Section: Included Files
*/

#include "../system/utils/compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  Section: VREF APIs
*/

/**
 * @ingroup vref
 * @brief  This routine initializes the VREF and must be called only once during system initialization.
 * @param int8_t
 * @return void
 */
int8_t VREF_Initialize(void);

#ifdef __cplusplus
}
#endif

#endif /* VREF_H_INCLUDED */
/**
 End of File
*/
