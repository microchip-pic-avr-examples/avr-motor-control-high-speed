/**
  * TCB1 Generated Driver File
  *
  * @file tcb1.c
  *
  * @ingroup tcb1
  *
  * @brief This file contains the API implementation for the TCB1 module driver.
  *
  * @version TCB1 Driver Version 1.2.0
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

#include "../tcb1.h"

const struct TIMER_INTERFACE Timer_TCB1 = {
    .Initialize = TCB1_Initialize,
    .Deinitialize = TCB1_Deinitialize,
    .Start = TCB1_Start,
    .Stop = TCB1_Stop,
    .PeriodSet = TCB1_CaptureCompareWrite,
    .PeriodCountSet = TCB1_Write,
    .PeriodGet = TCB1_CaptureCompareRead,
    .CounterGet = TCB1_Read,
    .InterruptPrioritySet = NULL,
    .Tasks = NULL,
    .TimeoutCallbackRegister = NULL
};

void TCB1_Initialize(void)
{
    // CCMP 20000; 
    TCB1.CCMP = 0x4E20;

    // CNT 0x0; 
    TCB1.CNT = 0x0;

    // ASYNC false; CCMPEN disabled; CCMPINIT disabled; CNTMODE CAPT; 
    TCB1.CTRLB = 0x2;

    // CNTSIZE 16BITS; 
    TCB1.CTRLC = 0x0;

    // DBGRUN disabled; 
    TCB1.DBGCTRL = 0x0;

    // CAPTEI enabled; EDGE enabled; FILTER enabled; 
    TCB1.EVCTRL = 0x51;

    // CAPT disabled; OVF disabled; 
    TCB1.INTFLAGS = TCB1.INTFLAGS;

    // CAPT disabled; OVF disabled; 
    TCB1.INTCTRL = 0x0;

    // CASCADE disabled; ENABLE enabled; CLKSEL DIV1; RUNSTDBY disabled; SYNCUPD disabled; 
    TCB1.CTRLA = 0x1;
}

void TCB1_Deinitialize(void)
{
    TCB1.CTRLA = 0x00;

    TCB1.INTCTRL = 0x00;

    TCB1.INTFLAGS = TCB1.INTFLAGS;

    TCB1.CCMP = 0x0000;

    TCB1.CNT = 0x0000;

    TCB1.CTRLB = 0x00;

    TCB1.CTRLC = 0x00;

    TCB1.DBGCTRL = 0x00;

    TCB1.EVCTRL = 0x00;
}

void TCB1_Start(void)
{
    TCB1.CTRLA |= TCB_ENABLE_bm;
}

void TCB1_Stop(void)
{
    TCB1.CTRLA &= ~TCB_ENABLE_bm;
}

void TCB1_Write(uint16_t const value)
{
    TCB1.CNT = value;
}

uint16_t TCB1_Read(void)
{
    uint16_t const readValue = TCB1.CNT;

    return readValue;
}

void TCB1_CaptureCompareWrite(uint16_t const value)
{
    TCB1.CCMP = value;
}

uint16_t TCB1_CaptureCompareRead(void)
{
    uint16_t const readValue = TCB1.CCMP;

    return readValue;
}

void TCB1_EnableCaptInterrupt(void)
{
    TCB1.INTCTRL |= TCB_CAPT_bm;
}

void TCB1_EnableOvfInterrupt(void)
{
	TCB1.INTCTRL |= TCB_OVF_bm;
}

void TCB1_DisableCaptInterrupt(void)
{
    TCB1.INTCTRL &= ~TCB_CAPT_bm;
}

void TCB1_DisableOvfInterrupt(void)
{
	TCB1.INTCTRL &= ~TCB_OVF_bm;
}

bool TCB1_IsCaptInterruptFlagSet(void)
{
    return ( (TCB1.INTFLAGS & TCB_CAPT_bm) != 0 );
}

bool TCB1_IsOvfInterruptFlagSet(void)
{
    return ( (TCB1.INTFLAGS & TCB_OVF_bm) != 0 );
}

void TCB1_ClearCaptInterruptFlag(void)
{
    TCB1.INTFLAGS = TCB_CAPT_bm;
}

void TCB1_ClearOvfInterruptFlag(void)
{
	TCB1.INTFLAGS = TCB_OVF_bm;
}

bool TCB1_IsCaptInterruptEnabled(void)
{
    return ( (TCB1.INTCTRL & TCB_CAPT_bm) != 0 );
}

bool TCB1_IsOvfInterruptEnabled(void)
{
    return ( (TCB1.INTCTRL & TCB_OVF_bm) != 0 );
}

