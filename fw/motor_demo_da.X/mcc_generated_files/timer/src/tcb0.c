
/**
  * TCB0 Generated Driver File
  *
  * @file tcb0.c
  *
  * @ingroup tcb0
  *
  * @brief This file contains the API implementation for the TCB0 module driver.
  *
  * @version TCB0 Driver Version 2.0.0
  *
  * @version Package Version 6.0.0
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

#include "../tcb0.h"


/**
 * Section: Global Variables Definitions
*/
static void (*TCB0_OVF_isr_cb)(void);
static void TCB0_DefaultOverflowCallback(void);
static void (*TCB0_CAPT_isr_cb)(void);
static void TCB0_DefaultCaptureCallback(void);

void TCB0_Initialize(void)
{
    TCB0.CTRLA &= ~TCB_ENABLE_bm; /* Stop Timer */

    TCB0.CTRLB = (0 << TCB_ASYNC_bp)   // ASYNC disabled
        | (0 << TCB_CCMPEN_bp)   // CCMPEN disabled
        | (0 << TCB_CCMPINIT_bp)   // CCMPINIT disabled
        | (TCB_CNTMODE_INT_gc);  // CNTMODE INT

    TCB0.DBGCTRL = (0 << TCB_DBGRUN_bp);  // DBGRUN disabled

    TCB0.EVCTRL = (0 << TCB_CAPTEI_bp)   // CAPTEI disabled
        | (0 << TCB_EDGE_bp)   // EDGE disabled
        | (0 << TCB_FILTER_bp);  // FILTER disabled

    TCB0.CCMP = 0xFFFFU;  // CCMP 0xFFFF

    TCB0.CNT = 0x0;  // CNT 0xNAN

    TCB0.INTFLAGS = (0 << TCB_CAPT_bp)   // CAPT disabled
        | (0 << TCB_OVF_bp);  // OVF disabled
    
	/* cppcheck-suppress misra-c2012-8.7 */
    TCB0_OverflowCallbackRegister(TCB0_DefaultOverflowCallback);
	/* cppcheck-suppress misra-c2012-8.7 */
    TCB0_CaptureCallbackRegister(TCB0_DefaultCaptureCallback);

    TCB0.INTCTRL = (1 << TCB_CAPT_bp)   // CAPT enabled
        | (0 << TCB_OVF_bp);  // OVF disabled

    TCB0.CTRLA = (0 << TCB_CASCADE_bp)   // CASCADE disabled
        | (TCB_CLKSEL_DIV1_gc)   // CLKSEL DIV1
        | (1 << TCB_ENABLE_bp)   // ENABLE enabled
        | (0 << TCB_RUNSTDBY_bp)   // RUNSTDBY disabled
        | (0 << TCB_SYNCUPD_bp);  // SYNCUPD disabled
}

void TCB0_Deinitialize(void)
{
    TCB0.CTRLA &= ~TCB_ENABLE_bm; /* Stop Timer */
    
    TCB0.CCMP = 0x0;

    TCB0.CNT = 0x0;
    
    TCB0.CTRLB = 0x0;

    TCB0.DBGCTRL = 0x0;

    TCB0.EVCTRL = 0x0;

    TCB0.INTCTRL = 0x0;

    TCB0.TEMP = 0x0;

    TCB0.CTRLA = 0x0;
    
    TCB0.INTFLAGS = ~0x0;
}

void TCB0_Start(void)
{
    TCB0.CTRLA |= TCB_ENABLE_bm; /* Start Timer */
}

void TCB0_Stop(void)
{
    TCB0.CTRLA &= ~TCB_ENABLE_bm; /* Stop Timer */
}

void TCB0_CounterSet(uint16_t timerVal)
{
    TCB0.CNT = timerVal;
}

uint16_t TCB0_CounterGet(void)
{
    uint16_t readVal;

    readVal = TCB0.CNT;

    return readVal;
}
void TCB0_PeriodSet(uint16_t periodVal)
{
    TCB0.CCMP = (uint16_t) periodVal;
}

uint16_t TCB0_PeriodGet(void)
{
    return (uint16_t)TCB0.CCMP;
}

uint16_t TCB0_MaxCountGet(void)
{
    return TCB0_MAX_COUNT;
}

void TCB0_CAPTInterruptEnable(void)
{
    TCB0.INTCTRL |= TCB_CAPT_bm; /* Capture or Timeout: enabled */
}

void TCB0_CAPTInterruptDisable(void)
{
    TCB0.INTCTRL &= ~TCB_CAPT_bm; /* Capture or Timeout: disabled */
}

void TCB0_OVFInterruptEnable(void)
{
	TCB0.INTCTRL |= TCB_OVF_bm; /* Overflow Interrupt: enabled */
}

void TCB0_OVFInterruptDisable(void)
{
	TCB0.INTCTRL &= ~TCB_OVF_bm; /* Overflow Interrupt: disabled */
}


bool TCB0_IsCaptInterruptEnabled(void)
{
    return ((TCB0.INTCTRL & TCB_CAPT_bm) > 0);
}

bool TCB0_IsOvfInterruptEnabled(void)
{
    return ((TCB0.INTCTRL & TCB_OVF_bm) > 0);
}


/* cppcheck-suppress misra-c2012-8.7 */
void TCB0_OverflowCallbackRegister(void (* CallbackHandler)(void))
{
	TCB0_OVF_isr_cb = CallbackHandler;
}

static void TCB0_DefaultOverflowCallback(void)
{
    //Add your interrupt code here or
    //Use TCB0_OverflowCallbackRegister function to use Custom ISR
}

/* cppcheck-suppress misra-c2012-8.7 */
void TCB0_CaptureCallbackRegister(void (* CallbackHandler)(void))
{
	TCB0_CAPT_isr_cb = CallbackHandler;
}

static void TCB0_DefaultCaptureCallback(void)
{
    //Add your Capture interrupt code here or
    //Use TCB0_CaptureCallbackRegister function to use Custom ISR
}

/* cppcheck-suppress misra-c2012-2.7 */
/* cppcheck-suppress misra-c2012-8.2 */
/* cppcheck-suppress misra-c2012-8.4 */
ISR(TCB0_INT_vect)
{
	if (0U != (TCB0.INTFLAGS & TCB_CAPT_bm))
    {
        if (TCB0_CAPT_isr_cb != NULL)
        {
            (*TCB0_CAPT_isr_cb)();
        }
        TCB0.INTFLAGS = TCB_CAPT_bm;
    }
    if (0U != (TCB0.INTFLAGS & TCB_OVF_bm))
    {
        if (TCB0_OVF_isr_cb != NULL)
        {
            (*TCB0_OVF_isr_cb)();
        }
        TCB0.INTFLAGS = TCB_OVF_bm;
    }
}

