/**
 *  Timer/Counter F Embedded Driver API Source File
 *
 *  @file tcf0.c
 *
 *  @defgroup tcf0 TCF0
 *
 *  @brief This document contains the implementation of public and private functions for the Timer Counter F module.
 *
 *  @version TCF0 Driver Version 1.0.1
 *
 *  @copyright (c) 2023 Microchip Technology Inc. and its subsidiaries.
 *
 *  Subject to your compliance with these terms, you may use Microchip software
 *  and any derivatives exclusively with Microchip products. You're responsible
 *  for complying with 3rd party license terms applicable to your use of 3rd
 *  party software (including open source software) that may accompany
 *  Microchip software.
 *
 *  SOFTWARE IS "AS IS." NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 *  APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF
 *  NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 *  INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 *  WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 *  BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 *  FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS
 *  RELATED TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID
 *  DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 */


#include "../tcf0.h"

#include <avr/interrupt.h>
#include <util/atomic.h>

#include <stddef.h>


/**
 * @ingroup tcf0
 * @brief Function pointers that store the callback addresses.
 */
static TCF0_cb_t TCF0_OVF_isr_cb  = NULL;

/**
 * @ingroup tcf0
 * @brief Boolean that is true when the timer is active.
 */
static volatile bool timerActive = false;

/**
 * @ingroup tcf0
 * @brief Internal variable that replicates TCF_WGMODE_t enum to reflect the active mode.
 */
static volatile uint8_t timerMode = TCF_WGMODE_FRQ_gc;


/**
 * @ingroup tcf0
 * @brief This function blocks the execution until the CMP0 register is no longer busy.
 * @pre None.
 * @param None.
 * @return None.
 */
static inline void TCF0_WaitWhile_CMP0_IsBusy(void)
{
    while ( (TCF0.STATUS & TCF_CMP0BUSY_bm) != 0 ) { }
}

/**
 * @ingroup tcf0
 * @brief This function blocks the execution until the CMP1 register is no longer busy.
 * @pre None.
 * @param None.
 * @return None.
 */
static inline void TCF0_WaitWhile_CMP1_IsBusy(void)
{
    while ( (TCF0.STATUS & TCF_CMP1BUSY_bm) != 0 ) { }
}

/**
 * @ingroup tcf0
 * @brief This function blocks the execution until the CTRLA register is no longer busy.
 * @pre None.
 * @param None.
 * @return None.
 */
static inline void TCF0_WaitWhile_CTRLA_IsBusy(void)
{
    while ( (TCF0.STATUS & TCF_CTRLABUSY_bm) != 0 ) { }
}

/**
 * @ingroup tcf0
 * @brief This function blocks the execution until the CTRLC register is no longer busy.
 * @pre None.
 * @param None.
 * @return None.
 */
static inline void TCF0_WaitWhile_CTRLC_IsBusy(void)
{
    while ( (TCF0.STATUS & TCF_CTRLCBUSY_bm) != 0 ) { }
}

/**
 * @ingroup tcf0
 * @brief This function blocks the execution until the CTRLD register is no longer busy.
 * @pre None.
 * @param None.
 * @return None.
 */
static inline void TCF0_WaitWhile_CTRLD_IsBusy(void)
{
    while ( (TCF0.STATUS & TCF_CTRLDBUSY_bm) != 0 ) { }
}

/**
 * @ingroup tcf0
 * @brief This function blocks the execution until the PER register is no longer busy.
 * @pre None.
 * @param None.
 * @return None.
 */
static inline void TCF0_WaitWhile_PER_IsBusy(void)
{
    while ( (TCF0.STATUS & TCF_PERBUSY_bm) != 0 ) { }
}

/**
 * @ingroup tcf0
 * @brief This function blocks the execution until the CNT register is no longer busy.
 * @pre None.
 * @param None.
 * @return None.
 */
static inline void TCF0_WaitWhile_CNT_IsBusy(void)
{
    while ( (TCF0.STATUS & TCF_CNTBUSY_bm) != 0 ) { }
}

/**
 * @ingroup tcf0
 * @brief This private function starts the timer. It is used only within the driver.
 * @pre None.
 * @param None.
 * @return None.
 */
static inline void TCF0_Internal_Start(void)
{
    TCF0_WaitWhile_CTRLA_IsBusy();
    TCF0.CTRLA |= TCF_ENABLE_bm;
}

/**
 * @ingroup tcf0
 * @brief This private function stops the timer. It is used only within the driver.
 * @pre None.
 * @param None.
 * @return None.
 */
static inline void TCF0_Internal_Stop(void)
{
    TCF0_WaitWhile_CTRLA_IsBusy();
    TCF0.CTRLA &= ~TCF_ENABLE_bm;
}

/**
 * @ingroup tcf0
 * @brief Interrupt Service Routine (ISR).
 * @pre None.
 * @param None.
 * @return None.
 */
ISR(TCF0_INT_vect)
{
    if ( (TCF0.INTFLAGS & TCF_OVF_bm) != 0 )
    {
        TCF0.INTFLAGS = TCF_OVF_bm;
        if(TCF0_OVF_isr_cb != NULL)
        {
            TCF0_OVF_isr_cb();
        }
    }
}

void TCF0_OverflowCallbackRegister(TCF0_cb_t callback)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        TCF0_OVF_isr_cb = callback;
    }
}

void TCF0_Initialize(void)
{
    timerActive = true;
    timerMode = TCF_WGMODE_FRQ_gc;

    // CMP0 disabled; CMP1 disabled; OVF enabled; 
    TCF0.INTCTRL = 0x1;

    // Interrupt Flags
    TCF0.INTFLAGS = TCF0.INTFLAGS;

    TCF0_OVF_isr_cb  = NULL;

    TCF0_WaitWhile_CMP0_IsBusy();
    // Compare Register
    TCF0.CMP = 0xD6D7;

    TCF0_WaitWhile_CNT_IsBusy();
    // Counter Register
    TCF0.CNT = 0x0;

    // CLKSEL CLKPER; CMP0EV PULSE; CMP1EV PULSE; WGMODE FRQ; 
    TCF0.CTRLB = 0x0;

    TCF0_WaitWhile_CTRLC_IsBusy();
    // WGPULSE CLK1; WO0EN 0; WO1EN 0; WO0POL NORMAL; WO1POL NORMAL; 
    TCF0.CTRLC = 0x0;

    TCF0_WaitWhile_CTRLD_IsBusy();
    // CMD NONE; 
    TCF0.CTRLD = 0x0;

    // CNTAEI disabled; EVACTA RESTART; FILTERA disabled; 
    TCF0.EVCTRL = 0x0;

    // DBGRUN disabled; 
    TCF0.DBGCTRL = 0x0;

    TCF0_WaitWhile_CTRLA_IsBusy();
    // PRESC DIV2; ENABLE enabled; RUNSTDBY disabled; 
    TCF0.CTRLA = 0x3;
}

void TCF0_Deinitialize(void)
{
    timerActive = false;
    timerMode = TCF_WGMODE_FRQ_gc;

    TCF0.INTCTRL = 0x00;

    TCF0.INTFLAGS = TCF0.INTFLAGS;

    TCF0_OVF_isr_cb  = NULL;

    TCF0_WaitWhile_CMP0_IsBusy();
    TCF0.CMP = 0x000000;

    TCF0_WaitWhile_CNT_IsBusy();
    TCF0.CNT = 0x000000;

    TCF0.CTRLB = 0x00;

    TCF0_WaitWhile_CTRLC_IsBusy();
    TCF0.CTRLC = 0x00;

    TCF0_WaitWhile_CTRLD_IsBusy();
    TCF0.CTRLD = 0x00;

    TCF0.DBGCTRL = 0x00;

    TCF0.EVCTRL = 0x00;

    TCF0_WaitWhile_CTRLA_IsBusy();
    TCF0.CTRLA = 0x00;
}

TCF0_status_t TCF0_StatusGet(void)
{
    TCF0_status_t retVal;
    TCF0_WaitWhile_CTRLA_IsBusy();

    if ( (TCF0.CTRLA & TCF_ENABLE_bm) != 0 )
    {
       retVal = TCF_STATUS_RUNNING;
    }
    else
    {
       retVal = TCF_STATUS_IDLE;
    }

    return retVal;
}

void TCF0_Start(void)
{
    TCF0_WaitWhile_CTRLA_IsBusy();
    TCF0.CTRLA |= TCF_ENABLE_bm;
    timerActive = true;
}

void TCF0_Stop(void)
{
    TCF0_WaitWhile_CTRLA_IsBusy();
    TCF0.CTRLA &= ~TCF_ENABLE_bm;
    timerActive = false;
}

void TCF0_PrescalerSet(TCF_PRESC_t config)
{
    uint8_t temp;
    TCF0_WaitWhile_CTRLA_IsBusy();
    temp = TCF0.CTRLA;
    temp &= ~TCF_PRESC_gm;
    temp |= config;
    TCF0.CTRLA = temp;
}

void TCF0_StandBySleep(bool state)
{
    uint8_t temp;
    TCF0_WaitWhile_CTRLA_IsBusy();
    temp = TCF0.CTRLA;

    if (state == true)
    {
        temp |= TCF_RUNSTDBY_bm;
    }
    else
    {
        temp &= ~TCF_RUNSTDBY_bm;
    }

    TCF0.CTRLA = temp;
}

void TCF0_ModeSet(TCF_WGMODE_t mode)
{
    uint8_t temp;

    if ((mode == TCF_WGMODE_FRQ_gc)    ||
        (mode == TCF_WGMODE_NCOPF_gc)  ||
        (mode == TCF_WGMODE_NCOFDC_gc) ||
        (mode == TCF_WGMODE_PWM8_gc))
    {
        temp = TCF0.CTRLB;
        temp &= ~TCF_WGMODE_gm;
        temp |= mode;

        if (timerActive)
        {
            TCF0_Internal_Stop();
            TCF0.CTRLB = temp;
            TCF0_Internal_Start();
        }
        else
        {
            TCF0.CTRLB = temp;
        }

        timerMode = mode;
    }
}

void TCF0_ClockSet(TCF_CLKSEL_t config)
{
    uint8_t temp;
    temp = (TCF0.CTRLB & ~TCF_CLKSEL_gm) |
           (config     &  TCF_CLKSEL_gm);

    if (timerActive)
    {
        TCF0_Internal_Stop();
        TCF0.CTRLB = temp;
        TCF0_Internal_Start();
    }
    else
    {
        TCF0.CTRLB = temp;
    }
}

void TCF0_Event_OutputMode(uint8_t value)
{
    uint8_t temp;

    temp = (TCF0.CTRLB & ~(TCF_CMP0EV_bm | TCF_CMP1EV_bm)) |
           (value      &  (TCF_CMP0EV_bm | TCF_CMP1EV_bm));

    if(timerActive)
    {
        TCF0_Internal_Stop();
        TCF0.CTRLB = temp;
        TCF0_Internal_Start();
    }
    else
    {
        TCF0.CTRLB = temp;
    }
}

void TCF0_OutputsSet(uint8_t value)
{
    uint8_t temp;

    TCF0_WaitWhile_CTRLC_IsBusy();
    temp = (TCF0.CTRLC & ~(TCF_WO0EN_bm | TCF_WO1EN_bm | TCF_WO0POL_bm | TCF_WO1POL_bm)) |
           (value      &  (TCF_WO0EN_bm | TCF_WO1EN_bm | TCF_WO0POL_bm | TCF_WO1POL_bm));

    TCF0.CTRLC = temp;
}

void TCF0_SoftwareCommand(TCF_CMD_t command)
{
    TCF0_WaitWhile_CTRLD_IsBusy();
    TCF0.CTRLD = command & TCF_CMD_gm;
}

void TCF0_Event_InputConfig(uint8_t config)
{
    uint8_t temp;
    temp = (TCF0.EVCTRL & ~(TCF_CNTAEI_bm | TCF_EVACTA_gm | TCF_FILTERA_bm)) |
           (config      &  (TCF_CNTAEI_bm | TCF_EVACTA_gm | TCF_FILTERA_bm));

    if (timerActive)
    {
        TCF0_Internal_Stop();
        TCF0.EVCTRL = temp;
        TCF0_Internal_Start();
    }
    else
    {
        TCF0.EVCTRL = temp;
    }
}

void TCF0_Interrupts_Enable(uint8_t mask)
{
    TCF0.INTCTRL |= (mask & (TCF_OVF_bm | TCF_CMP0_bm | TCF_CMP1_bm));
}

void TCF0_Interrupts_Disable(uint8_t mask)
{
    TCF0.INTCTRL &= ~(mask & (TCF_OVF_bm | TCF_CMP0_bm | TCF_CMP1_bm));
}

uint8_t TCF0_Interrupts_FlagsGet(void)
{
    return TCF0.INTFLAGS;
}

void TCF0_Interrupts_FlagsClear(uint8_t mask)
{
    TCF0.INTFLAGS = mask & (TCF_OVF_bm | TCF_CMP0_bm | TCF_CMP1_bm);
}

uint32_t TCF0_CounterGet(void)
{
    TCF0_WaitWhile_CNT_IsBusy();
    return TCF0.CNT;
}

void TCF0_CounterSet(uint32_t value)
{
    TCF0_WaitWhile_CNT_IsBusy();

    if (timerMode != TCF_WGMODE_PWM8_gc)
    {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            TCF0.CNT = value;
        }
    }
    else
    {
        TCF0.CNT0 = (uint8_t) value;
    }
}

void TCF0_CompareSet(uint32_t value)
{
    if (timerMode != TCF_WGMODE_PWM8_gc)
    {
        TCF0_WaitWhile_CMP0_IsBusy();
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            TCF0.CMP = value;
        }
    }
}

void TCF0_NCO_PulseLengthSet(TCF_WGPULSE_t config)
{
    uint8_t temp;

    if (timerMode == TCF_WGMODE_NCOPF_gc)
    {
        TCF0_WaitWhile_CTRLC_IsBusy();
        temp = (TCF0.CTRLC & ~TCF_WGPULSE_gm) |
               (config     &  TCF_WGPULSE_gm);
        TCF0.CTRLC = temp;
    }
}

void TCF0_PWM_DutyCycle0Set(uint8_t value)
{
    if (timerMode == TCF_WGMODE_PWM8_gc)
    {
        TCF0_WaitWhile_CMP0_IsBusy();
        TCF0.CMP0 = value;
    }
}

void TCF0_PWM_DutyCycle1Set(uint8_t value)
{
    if (timerMode == TCF_WGMODE_PWM8_gc)
    {
        TCF0_WaitWhile_CMP1_IsBusy();
        TCF0.CMP1 = value;
    }
}

void TCF0_PWM_PeriodSet(uint8_t value)
{
    if (timerMode == TCF_WGMODE_PWM8_gc)
    {
        TCF0_WaitWhile_PER_IsBusy();
        TCF0.CNT1 = value;
    }
}
