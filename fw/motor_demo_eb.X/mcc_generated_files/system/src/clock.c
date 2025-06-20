
/**
  * CLKCTRL Generated Driver File
  *
  * @file clkctrl.c
  *
  * @ingroup clkctrl
  *
  * @brief This file contains the API implementation for the CLKCTRL driver.
  *
  * version CLKCTRL Driver Version 1.0.1
  *
  * @version Package Version 1.0.2
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


#include "../clock.h"

void CLOCK_Initialize(void)
{
    ccp_write_io((void*)&(CLKCTRL.MCLKCTRLB),CLKCTRL_PDIV_DIV6_gc   // PDIV Divide by 6
            | CLKCTRL_PBDIV_NONE_gc   // PBDIV No division
            | (0 << CLKCTRL_PEN_bp)   // PEN disabled
            );
    ccp_write_io((void*)&(CLKCTRL.MCLKTIMEBASE),0x14   // TIMEBASE 20
            );
    ccp_write_io((void*)&(CLKCTRL.OSC32KCTRLA),(0 << CLKCTRL_RUNSTDBY_bp)   // RUNSTDBY disabled
            );
    ccp_write_io((void*)&(CLKCTRL.OSCHFCTRLA),CLKCTRL_AUTOTUNE_OFF_gc   // AUTOTUNE OFF
            | (0 << CLKCTRL_RUNSTDBY_bp)   // RUNSTDBY disabled
            );
    ccp_write_io((void*)&(CLKCTRL.OSCHFTUNE),0x0   // TUNE 0x0
            );
    ccp_write_io((void*)&(CLKCTRL.PLLCTRLA),CLKCTRL_MULFAC_OFF_gc   // MULFAC PLL Disabled
            | (0 << CLKCTRL_RUNSTDBY_bp)   // RUNSTDBY disabled
            | CLKCTRL_SOURCE_OSCHF_gc   // SOURCE OSCHF
            | CLKCTRL_SOURCEDIV_DIV1_gc   // SOURCEDIV DIV1
            );
    ccp_write_io((void*)&(CLKCTRL.PLLCTRLB),CLKCTRL_CLKDIV_NONE_gc   // CLKDIV NONE
            );
    ccp_write_io((void*)&(CLKCTRL.XOSC32KCTRLA),CLKCTRL_CSUT_1K_gc   // CSUT 1k cycles
            | (0 << CLKCTRL_ENABLE_bp)   // ENABLE disabled
            | (0 << CLKCTRL_LPMODE_bp)   // LPMODE disabled
            | (0 << CLKCTRL_RUNSTDBY_bp)   // RUNSTDBY disabled
            | (0 << CLKCTRL_SEL_bp)   // SEL disabled
            );
    ccp_write_io((void*)&(CLKCTRL.MCLKCTRLA),(0 << CLKCTRL_CLKOUT_bp)   // CLKOUT disabled
            | CLKCTRL_CLKSEL_OSCHF_gc   // CLKSEL Internal high-frequency oscillator
            );
    // System clock stability check by polling the status register.
    while(!(CLKCTRL.MCLKSTATUS & CLKCTRL_OSCHFS_bm))
    {
    }
}

/**
 End of File
*/