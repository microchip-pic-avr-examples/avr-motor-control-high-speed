/**
 *
 * @file evsys.c
 *
 * @ingroup evsys_driver
 *
 * @brief This file contains the API implementation for the EVSYS driver.
 *
 * @version EVSYS Driver Version 1.1.2
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

#include "../evsys.h"

int8_t EVSYS_Initialize()
{
    //
    EVSYS.CHANNEL0 = 0x0;
    //
    EVSYS.CHANNEL1 = 0x0;
    //
    EVSYS.CHANNEL2 = 0x0;
    //
    EVSYS.CHANNEL3 = 0x0;
    //
    EVSYS.CHANNEL4 = 0x0;
    //
    EVSYS.CHANNEL5 = 0x0;
    //
    EVSYS.USERCCLLUT0A = 0x0;
    //
    EVSYS.USERCCLLUT0B = 0x0;
    //
    EVSYS.USERCCLLUT1A = 0x0;
    //
    EVSYS.USERCCLLUT1B = 0x0;
    //
    EVSYS.USERCCLLUT2A = 0x0;
    //
    EVSYS.USERCCLLUT2B = 0x0;
    //
    EVSYS.USERCCLLUT3A = 0x0;
    //
    EVSYS.USERCCLLUT3B = 0x0;
    //
    EVSYS.CHANNEL6 = 0x0;
    //
    EVSYS.CHANNEL7 = 0x0;

	/* EVSYS MCC ISSUE */
	EVSYS.CHANNEL0 = EVSYS_GENERATOR_TCA0_OVF_LUNF_gc;
    EVSYS.USERADC0 = EVSYS_CHANNEL_CHANNEL0_gc;
    
    EVSYS.CHANNEL1 = EVSYS_GENERATOR_AC0_OUT_gc;
    EVSYS.USERTCB1 = EVSYS_CHANNEL_CHANNEL1_gc;

    EVSYS.USEREVOUTA = EVSYS_CHANNEL_CHANNEL1_gc;
    
    
    return 0;
}
