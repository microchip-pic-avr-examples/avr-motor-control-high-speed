/**
  * TCB0 Generated Driver File
  *
  * @file tcb0.c
  *
  * @ingroup tcb0
  *
  * @brief This file contains the API implementation for the TCB0 module driver.
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

#include "../tcb0.h"

const struct TIMER_INTERFACE Timer_TCB0 = {
    .Initialize = TCB0_Initialize,
    .Deinitialize = TCB0_Deinitialize,
    .Start = TCB0_Start,
    .Stop = TCB0_Stop,
    .PeriodSet = TCB0_CaptureCompareWrite,
    .PeriodCountSet = TCB0_Write,
    .PeriodGet = TCB0_CaptureCompareRead,
    .CounterGet = TCB0_Read,
    .InterruptPrioritySet = NULL,
    .Tasks = NULL,
    .TimeoutCallbackRegister = NULL
};

void (*TCB0_CAPT_isr_cb)(void) = NULL;

void TCB0_CaptureCallbackRegister(TCB0_cb_t const callback)
{
	TCB0_CAPT_isr_cb = callback;
}

ISR(TCB0_INT_vect)
{
	/* Insert your TCB interrupt handling code */

	/*
	 *  The Capture interrupt flag is cleared by writing a 1 to it or when the
	 *  Capture register is read in Capture mode
	 */
	if (TCB0.INTFLAGS & TCB_CAPT_bm)
    {
        if (TCB0_CAPT_isr_cb != NULL)
        {
            (*TCB0_CAPT_isr_cb)();
        }

        TCB0.INTFLAGS = TCB_CAPT_bm;
    }

}

void TCB0_Initialize(void)
{
    // CCMP 65535; 
    TCB0.CCMP = 0xFFFF;

    // CNT 0x0; 
    TCB0.CNT = 0x0;

    // ASYNC false; CCMPEN disabled; CCMPINIT disabled; CNTMODE INT; 
    TCB0.CTRLB = 0x0;

    // CNTSIZE 16BITS; 
    TCB0.CTRLC = 0x0;

    // DBGRUN disabled; 
    TCB0.DBGCTRL = 0x0;

    // CAPTEI disabled; EDGE disabled; FILTER disabled; 
    TCB0.EVCTRL = 0x0;

    // CAPT disabled; OVF disabled; 
    TCB0.INTFLAGS = TCB0.INTFLAGS;

    // CAPT enabled; OVF disabled; 
    TCB0.INTCTRL = 0x1;

    // CASCADE disabled; ENABLE enabled; CLKSEL DIV1; RUNSTDBY disabled; SYNCUPD disabled; 
    TCB0.CTRLA = 0x1;
}

void TCB0_Deinitialize(void)
{
    TCB0.CTRLA = 0x00;

    TCB0.INTCTRL = 0x00;

    TCB0.INTFLAGS = TCB0.INTFLAGS;

    TCB0.CCMP = 0x0000;

    TCB0.CNT = 0x0000;

    TCB0.CTRLB = 0x00;

    TCB0.CTRLC = 0x00;

    TCB0.DBGCTRL = 0x00;

    TCB0.EVCTRL = 0x00;

    TCB0_CAPT_isr_cb = NULL;
}

void TCB0_Start(void)
{
    TCB0.CTRLA |= TCB_ENABLE_bm;
}

void TCB0_Stop(void)
{
    TCB0.CTRLA &= ~TCB_ENABLE_bm;
}

void TCB0_Write(uint16_t const value)
{
    TCB0.CNT = value;
}

uint16_t TCB0_Read(void)
{
    uint16_t const readValue = TCB0.CNT;

    return readValue;
}

void TCB0_CaptureCompareWrite(uint16_t const value)
{
    TCB0.CCMP = value;
}

uint16_t TCB0_CaptureCompareRead(void)
{
    uint16_t const readValue = TCB0.CCMP;

    return readValue;
}

void TCB0_EnableCaptInterrupt(void)
{
    TCB0.INTCTRL |= TCB_CAPT_bm;
}

void TCB0_EnableOvfInterrupt(void)
{
	TCB0.INTCTRL |= TCB_OVF_bm;
}

void TCB0_DisableCaptInterrupt(void)
{
    TCB0.INTCTRL &= ~TCB_CAPT_bm;
}

void TCB0_DisableOvfInterrupt(void)
{
	TCB0.INTCTRL &= ~TCB_OVF_bm;
}

bool TCB0_IsCaptInterruptFlagSet(void)
{
    return ( (TCB0.INTFLAGS & TCB_CAPT_bm) != 0 );
}

bool TCB0_IsOvfInterruptFlagSet(void)
{
    return ( (TCB0.INTFLAGS & TCB_OVF_bm) != 0 );
}

void TCB0_ClearCaptInterruptFlag(void)
{
    TCB0.INTFLAGS = TCB_CAPT_bm;
}

void TCB0_ClearOvfInterruptFlag(void)
{
	TCB0.INTFLAGS = TCB_OVF_bm;
}

bool TCB0_IsCaptInterruptEnabled(void)
{
    return ( (TCB0.INTCTRL & TCB_CAPT_bm) != 0 );
}

bool TCB0_IsOvfInterruptEnabled(void)
{
    return ( (TCB0.INTCTRL & TCB_OVF_bm) != 0 );
}

