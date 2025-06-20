/**
  * Generated Driver File
  *
  * @file timer_interface.h
  *
  * @brief This file contains API prototypes and other datatypes for the timer modules' drivers.
  *
  * @defgroup timer_interface Timer Interface
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

#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

#include <stdint.h>
#include <stddef.h>

/**
 * @ingroup timer_interface
 * @typedef struct TIMER_INTERFACE
 * @brief This structure contains the interfaces to a timer module
 */
struct TIMER_INTERFACE
{
    void (* Initialize)(void);
    void (* Deinitialize)(void);
    void (* Start)(void);
    void (* Stop)(void);
    void (* PeriodSet)(uint16_t);
    void (* PeriodCountSet)(uint16_t);
    uint16_t (* PeriodGet)(void);
    uint16_t (* CounterGet)(void);
    void (* InterruptPrioritySet)(size_t);
    void (* Tasks)(void);
    void (* TimeoutCallbackRegister)(void (*)(void));
};

#endif //TIMER_INTERFACE_H
