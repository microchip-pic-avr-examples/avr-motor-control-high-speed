/**
 * AC1 Generated Driver File
 * 
 * @file ac1.c
 * 
 * @ingroup  ac1
 * 
 * @brief Contains the API implementation for the AC1 driver.
 *
 * @version AC1 Driver Version 1.0.0
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

#include <util/atomic.h>
#include "../ac1.h"

static ac_cb_t AC1_cb = NULL;

int8_t AC1_Initialize(void) 
{
    //WINSEL Window function disabled; 
    AC1.CTRLB = 0x0;

    //DACREF 0; 
    AC1.DACREF = 0x0;
    
    //CMP disabled; INTMODE Positive and negative inputs crosses; 
    AC1.INTCTRL = 0x0;
    
    //INITVAL LOW; INVERT disabled; MUXNEG Negative Pin 2; MUXPOS Positive Pin 3;   
    AC1.MUXCTRL = 0x1A;
    
    //ENABLE enabled; HYSMODE No hysteresis; OUTEN disabled; POWER Power profile 0, Shortest response time, highest consumption; RUNSTDBY disabled; 
    AC1.CTRLA = 0x1;

    return 0;
}

ISR(AC1_AC_vect)
{
    /* Insert your AC interrupt handling code here */

    /* The interrupt flag has to be cleared manually */
    AC1.STATUS = AC_CMPIF_bm;
    if (AC1_cb != NULL)
    {
        AC1_cb();
    }    
}

void AC1_MuxSet(uint8_t Mode)
{
    uint8_t temp;
    temp = AC1.MUXCTRL;
    temp &= ~(AC_MUXPOS_gm | AC_MUXNEG_gm);
    temp |= Mode;
    AC1.MUXCTRL = temp;
}

bool AC1_Read(void)
{
    return ((AC1.STATUS & AC_CMPSTATE_bm) != 0 );
}

void AC1_CallbackRegister(ac_cb_t comparator_cb)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    	{
    		AC1_cb = comparator_cb;
	}
}

void AC1_DACRefValueSet (uint8_t value)
{ 
    AC1.DACREF = value;
}
