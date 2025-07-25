/**
 * @file wex0.c
 *
 * @brief Waveform Extension Driver API Source File
 *
 * @ingroup wex0
 *
 * @version WEX0 Driver Version 1.0.1
 *
 * @copyright © 2025 Microchip Technology Inc. and its subsidiaries.
 *
 * Subject to your compliance with these terms, you may use Microchip software
 * and any derivatives exclusively with Microchip products. You're responsible
 * for complying with 3rd party license terms applicable to your use of 3rd
 * party software (including open source software) that may accompany
 * Microchip software.
 *
 * SOFTWARE IS "AS IS." NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 * APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF
 * NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS
 * RELATED TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID
 * DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 **/


#include "../wex0.h"

#include <stddef.h>

#include <avr/interrupt.h>
#include <util/atomic.h>



void WEX0_Initialize(void)
{
    // DTI0EN true; DTI1EN true; DTI2EN true; DTI3EN false; PGM true; INMX DIRECT; 
    WEX0.CTRLA = 0x87;
    // UPDSRC TCPWM0; 
    WEX0.CTRLB = 0x0;
    // CMD NONE; 
    WEX0.CTRLC = 0x0;
    // BLANK disabled; FAULTEI disabled; FILTER ZERO; 
    WEX0.EVCTRLA = 0x0;
    // BLANK disabled; FAULTEI disabled; FILTER ZERO; 
    WEX0.EVCTRLB = 0x0;
    // BLANK disabled; FAULTEI disabled; FILTER ZERO; 
    WEX0.EVCTRLC = 0x0;
    // BLANKPRESC DIV1; BLANKTRIG NONE; 
    WEX0.BLANKCTRL = 0x0;
    // BLANKTIME 0; 
    WEX0.BLANKTIME = 0x0;
    // FAULTDRV0 disabled; FAULTDRV1 disabled; FAULTDRV2 disabled; FAULTDRV3 disabled; FAULTDRV4 disabled; FAULTDRV5 disabled; FAULTDRV6 disabled; FAULTDRV7 disabled; 
    WEX0.FAULTDRV = 0x0;
    // FAULTOUT0 disabled; FAULTOUT1 disabled; FAULTOUT2 disabled; FAULTOUT3 disabled; FAULTOUT4 disabled; FAULTOUT5 disabled; FAULTOUT6 disabled; FAULTOUT7 disabled; 
    WEX0.FAULTOUT = 0x0;
    // FDACT 0; FDDBD FAULT; FDMODE LATCHED; 
    WEX0.FAULTCTRL = 0x0;
    // STATUS
    WEX0.STATUS = 0x0;
    // DTLS 0; 
    WEX0.DTLS = 0x0;
    // DTHS 0; 
    WEX0.DTHS = 0x0;
    // SWAP0 false; SWAP1 false; SWAP2 false; SWAP3 false; 
    WEX0.SWAP = 0x0;
    // PGMOVR0 disabled; PGMOVR1 enabled; PGMOVR2 disabled; PGMOVR3 enabled; PGMOVR4 disabled; PGMOVR5 enabled; PGMOVR6 disabled; PGMOVR7 disabled; 
    WEX0.PGMOVR = 0x2A;
    // PGMOUT0 disabled; PGMOUT1 disabled; PGMOUT2 disabled; PGMOUT3 disabled; PGMOUT4 disabled; PGMOUT5 disabled; PGMOUT6 disabled; PGMOUT7 disabled; 
    WEX0.PGMOUT = 0x0;
    // OUTOVEN0 enabled; OUTOVEN1 enabled; OUTOVEN2 enabled; OUTOVEN3 enabled; OUTOVEN4 enabled; OUTOVEN5 enabled; OUTOVEN6 disabled; OUTOVEN7 disabled; 
    WEX0.OUTOVEN = 0x3F;
    // DTLSBV disabled; DTHSBV disabled; SWAPBV disabled; PGMOVRBV disabled; PGMOUTBV disabled; 
    WEX0.BUFCTRL = 0x0;
    // FAULTDET disabled; 
    WEX0.INTCTRL = 0x0;
    // FAULTDET disabled; FDFEVA disabled; FDFEVB disabled; FDFEVC disabled; 
    WEX0.INTFLAGS = WEX0.INTFLAGS;
}

void WEX0_Deinitialize(void)
{
    WEX0.CTRLA     = 0x00;
    WEX0.CTRLB     = 0x00;
    WEX0.CTRLC     = 0x00;
    WEX0.EVCTRLA   = 0x00;
    WEX0.EVCTRLB   = 0x00;
    WEX0.EVCTRLC   = 0x00;
    WEX0.BLANKCTRL = 0x00;
    WEX0.BLANKTIME = 0x00;
    WEX0.FAULTCTRL = 0x00;
    WEX0.FAULTDRV  = 0x00;
    WEX0.FAULTOUT  = 0x00;
    WEX0.STATUS    = 0x00;
    WEX0.DTHS      = 0x00;
    WEX0.DTLS      = 0x00;
    WEX0.DTBOTH    = 0x00;
    WEX0.SWAP      = 0x00;
    WEX0.PGMOVR    = 0x00;
    WEX0.PGMOUT    = 0x00;
    WEX0.OUTOVEN   = 0x00;
    WEX0.INTCTRL   = 0x00;
    WEX0.DTHSBUF   = 0x00;
    WEX0.DTLSBUF   = 0x00;
    WEX0.DTBOTHBUF = 0x00;
    WEX0.SWAPBUF   = 0x00;
    WEX0.PGMOVRBUF = 0x00;
    WEX0.PGMOUTBUF = 0x00;
    WEX0.BUFCTRL   = 0x00;
    WEX0.INTFLAGS  = WEX0.INTFLAGS;
}

uint8_t WEX0_StatusRegisterGet(void)
{
    return WEX0.STATUS;
}

void WEX0_PatternGenerationMode(bool mode)
{
    if (mode == true)
    {
        WEX0.CTRLA |= WEX_PGM_bm;
    }
    else
    {
        WEX0.CTRLA &= ~WEX_PGM_bm;
    }
}

bool WEX0_IsPatternGenerationSet(void)
{
    return ((WEX0.CTRLA & WEX_PGM_bm) != 0);
}

void WEX0_InputMatrixSet(WEX_INMX_t config)
{
    uint8_t temp;
    temp = (WEX0.CTRLA & ~WEX_INMX_gm) |
           (config     &  WEX_INMX_gm);
    WEX0.CTRLA = temp;
}

void WEX0_DeadTimeInsertionSet(uint8_t channels)
{
    uint8_t temp;
    temp = (WEX0.CTRLA & ~(WEX_DTI0EN_bm | WEX_DTI1EN_bm | WEX_DTI2EN_bm | WEX_DTI3EN_bm)) |
           (channels   &  (WEX_DTI0EN_bm | WEX_DTI1EN_bm | WEX_DTI2EN_bm | WEX_DTI3EN_bm));
    WEX0.CTRLA = temp;
}

void WEX0_UpdateSourceSet(WEX_UPDSRC_t config)
{
    uint8_t temp;
    temp = (WEX0.CTRLB & ~WEX_UPDSRC_gm) |
           (config     &  WEX_UPDSRC_gm);
    WEX0.CTRLB = temp;
}

void WEX0_SoftwareCommand(WEX_CMD_t command)
{
    uint8_t temp;
    temp = (WEX0.CTRLC & ~WEX_CMD_gm) |
           (command    &  WEX_CMD_gm);
    WEX0.CTRLC = temp;
}

void WEX0_FaultAEventFilter(WEX_FILTER_t samples)
{
    uint8_t temp;
    temp = (WEX0.EVCTRLA & ~WEX_FILTER_gm) |
           (samples      &  WEX_FILTER_gm);
    WEX0.EVCTRLA = temp;
}

void WEX0_FaultAEventBlankingEnable(bool en)
{
    if (en == true)
    {
        WEX0.EVCTRLA |= WEX_BLANK_bm;
    }
    else
    {
        WEX0.EVCTRLA &= ~WEX_BLANK_bm;
    }
}

void WEX0_FaultAEventInputEnable(bool en)
{
    if (en == true)
    {
        WEX0.EVCTRLA |= WEX_FAULTEI_bm;
    }
    else
    {
        WEX0.EVCTRLA &= ~WEX_FAULTEI_bm;
    }
}

void WEX0_FaultBEventFilter(WEX_FILTER_t samples)
{
    uint8_t temp;
    temp = (WEX0.EVCTRLB & ~WEX_FILTER_gm) |
           (samples      &  WEX_FILTER_gm);
    WEX0.EVCTRLB = temp;
}

void WEX0_FaultBEventBlankingEnable(bool en)
{
    if (en == true)
    {
        WEX0.EVCTRLB |= WEX_BLANK_bm;
    }
    else
    {
        WEX0.EVCTRLB &= ~WEX_BLANK_bm;
    }
}

void WEX0_FaultBEventInputEnable(bool en)
{
    if (en == true)
    {
        WEX0.EVCTRLB |= WEX_FAULTEI_bm;
    }
    else
    {
        WEX0.EVCTRLB &= ~WEX_FAULTEI_bm;
    }
}

void WEX0_FaultCEventFilter(WEX_FILTER_t samples)
{
    uint8_t temp;
    temp = (WEX0.EVCTRLC & ~WEX_FILTER_gm) |
           (samples      &  WEX_FILTER_gm);
    WEX0.EVCTRLC = temp;
}

void WEX0_FaultCEventBlankingEnable(bool en)
{
    if (en == true)
    {
        WEX0.EVCTRLC |= WEX_BLANK_bm;
    }
    else
    {
        WEX0.EVCTRLC &= ~WEX_BLANK_bm;
    }
}

void WEX0_FaultCEventInputEnable(bool en)
{
    if (en == true)
    {
        WEX0.EVCTRLC |= WEX_FAULTEI_bm;
    }
    else
    {
        WEX0.EVCTRLC &= ~WEX_FAULTEI_bm;
    }
}

void WEX0_BlankingPrescaler(WEX_BLANKPRESC_t prescaler)
{
    uint8_t temp;
    temp = (WEX0.BLANKCTRL & ~WEX_BLANKPRESC_gm) |
           (prescaler      &  WEX_BLANKPRESC_gm);
    WEX0.BLANKCTRL = temp;
}

void WEX0_BlankingTrigger(WEX_BLANKTRIG_t trig)
{
    uint8_t temp;
    temp = (WEX0.BLANKCTRL & ~WEX_BLANKTRIG_gm) |
           (trig           &  WEX_BLANKTRIG_gm);
    WEX0.BLANKCTRL = temp;
}

void WEX0_BlankingTimeSet(uint8_t cnt)
{
    WEX0.BLANKTIME = cnt;
}

uint8_t WEX0_BlankingTimeGet(void)
{
    return WEX0.BLANKTIME;
}

void WEX0_FaultDetectionDebugBreak(WEX_FDDBD_t mode)
{
    uint8_t temp;
    temp = (WEX0.FAULTCTRL & ~WEX_FDDBD_bm) |
           (mode           &  WEX_FDDBD_bm);
    WEX0.FAULTCTRL = temp;
}

void WEX0_FaultDetectionRestartMode(WEX_FDMODE_t mode)
{
    uint8_t temp;
    temp = (WEX0.FAULTCTRL & ~WEX_FDMODE_bm) |
           (mode           &  WEX_FDMODE_bm);
    WEX0.FAULTCTRL = temp;
}

void WEX0_FaultDetectionAction(WEX_FDACT_t action)
{
    uint8_t temp;
    temp = (WEX0.FAULTCTRL & ~WEX_FDACT_gm) |
           (action         &  WEX_FDACT_gm);
    WEX0.FAULTCTRL = temp;
}

void WEX0_FaultDriveSet(uint8_t channels)
{
    WEX0.FAULTDRV = channels;
}

void WEX0_FaultOutputSet(uint8_t channels)
{
    WEX0.FAULTOUT = channels;
}

void WEX0_FaultEnable(void)
{
    WEX0.INTCTRL |= WEX_FAULTDET_bm;
}

bool WEX0_IsFaultEnabled(void)
{
    return ((WEX0.INTCTRL & WEX_FAULTDET_bm) != 0);
}

void WEX0_FaultDisable(void)
{
    WEX0.INTCTRL &= ~WEX_FAULTDET_bm;
}

void WEX0_FaultFlagsClear(uint8_t flags)
{
    WEX0.INTFLAGS = flags & (WEX_FAULTDET_bm | WEX_FDFEVA_bm | WEX_FDFEVB_bm | WEX_FDFEVC_bm);
}

uint8_t WEX0_FaultFlagsGet(void)
{
    return (WEX0.INTFLAGS & (WEX_FAULTDET_bm | WEX_FDFEVA_bm | WEX_FDFEVB_bm | WEX_FDFEVC_bm));
}

void WEX0_DeadTimeLowSideSet(uint8_t cnt)
{
    WEX0.DTLS = cnt;
}

void WEX0_DeadTimeHighSideSet(uint8_t cnt)
{
    WEX0.DTHS = cnt;
}

void WEX0_DeadTimeBothSidesSet(uint8_t cnt)
{
    WEX0.DTBOTH = cnt;
}

void WEX0_SwapChannelSet(uint8_t channels)
{
    uint8_t temp;
    temp = (WEX0.SWAP & ~(WEX_SWAP0_bm | WEX_SWAP1_bm | WEX_SWAP2_bm | WEX_SWAP3_bm)) |
           (channels  &  (WEX_SWAP0_bm | WEX_SWAP1_bm | WEX_SWAP2_bm | WEX_SWAP3_bm));
    WEX0.SWAP = temp;
}

void WEX0_PatternGenerationOverrideSet(uint8_t channels)
{
    WEX0.PGMOVR = channels;
}

void WEX0_PatternGenerationOutputSet(uint8_t channels)
{
    WEX0.PGMOUT = channels;
}

void WEX0_OutputOverrideEnable(uint8_t channels)
{
    WEX0.OUTOVEN = channels;
}

void WEX0_DeadTimeLowSideBufferSet(uint8_t buff)
{
    WEX0.DTLSBUF = buff;
}

void WEX0_DeadTimeHighSideBufferSet(uint8_t buff)
{
    WEX0.DTHSBUF = buff;
}

void WEX0_DeadTimeBothSidesBufferSet(uint8_t buff)
{
    WEX0.DTBOTHBUF = buff;
}

void WEX0_SwapChannelBufferSet(uint8_t buff)
{
    WEX0.SWAPBUF = buff;
}

void WEX0_PatternGenerationOverrideBufferSet(uint8_t buff)
{
    WEX0.PGMOVRBUF = buff;
}

void WEX0_PatternGenerationOutputBufferSet(uint8_t buff)
{
    WEX0.PGMOUTBUF = buff;
}
