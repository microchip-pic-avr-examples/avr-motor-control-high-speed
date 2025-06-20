/**
 * ADC0 Generated Driver File
 *
 * @file adc0.c
 * 
 * @ingroup adc0 
 * 
 * @brief This file contains the API implementations for the ADC0 driver.
 * 
 * @version ADC0 Driver Version 2.0.0
 * 
 * @version ADC0 Package Version 5.0.0
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

#include "../adc0.h"

static void (*ADC0_ConversionDoneCallback)(void);
static void (*ADC0_ThresholdCallback)(void);

void ADC0_Initialize(void)
{
    // Disable ADC0 module
    ADC0.CTRLA &= ~(ADC_ENABLE_bm);
    // Disable ADC0 interrupts
    ADC0.INTCTRL &= ~(ADC_RESRDY_bm | ADC_WCMP_bm);
    // Clear ADC0 interrupt flags
    ADC0.INTFLAGS = (ADC_RESRDY_bm | ADC_WCMP_bm);
    // Reset interrupt callback handlers
    ADC0_ConversionDoneCallback = NULL;
    ADC0_ThresholdCallback = NULL;

    // Configure ADC0 module registers
    ADC0.CTRLB = (ADC_SAMPNUM_ACC1_gc);             /* SAMPNUM (1 ADC sample) */
    ADC0.CTRLC = (ADC_PRESC_DIV16_gc)               /* PRESC (CLK_PER divided by 16) */
				|(ADC_REFSEL_VDDREF_gc)             /* REFSEL (VDDREF) */
				|(1 << ADC_SAMPCAP_bp);             /* SAMPCAP (enabled) */
    ADC0.CTRLD = (ADC_ASDV_ASVOFF_gc)               /* ASDV (ASVOFF) */
				|(ADC_INITDLY_DLY0_gc)              /* INITDLY (DLY0) */
				|0x0;                               /* SAMPDLY (0x0) */
    ADC0.CTRLE = (ADC_WINCM_NONE_gc);               /* WINCM (No Window Comparison) */
    ADC0.SAMPCTRL = 0x3;                               /* SAMPLEN (0x3) */
    ADC0.MUXPOS = (ADC_MUXPOS_AIN0_gc);              /* MUXPOS (AIN0) */
    ADC0.COMMAND = (0 << ADC_STCONV_bp);              /* STCONV (disabled) */
    ADC0.EVCTRL = (1 << ADC_STARTEI_bp);             /* STARTEI (enabled) */
    ADC0.DBGCTRL = (0 << ADC_DBGRUN_bp);              /* DBGRUN (disabled) */
    ADC0.WINHT = 0x7FFF;                            /* WINHT (0x7FFF) */
    ADC0.WINLT = 0x0;                               /* WINLT (0x0) */
    ADC0.CALIB = (ADC_DUTYCYC_DUTY25_gc);           /* DUTYCYC (DUTY25) */
    ADC0.INTCTRL = (1 << ADC_RESRDY_bp)               /* RESRDY (enabled) */
				|(0 << ADC_WCMP_bp);                /* WCMP (disabled) */

    ADC0.CTRLA = (1 << ADC_ENABLE_bp)               /* ENABLE (enabled) */
				|(0 << ADC_FREERUN_bp)              /* FREERUN (disabled) */
				|(ADC_RESSEL_10BIT_gc)              /* RESSEL (10-bit mode) */
				|(0 << ADC_RUNSTBY_bp);             /* RUNSTBY (disabled) */
}

void ADC0_Deinitialize(void)
{
    ADC0.CTRLA = 0x0;
    ADC0.INTCTRL = 0x0;
    ADC0.INTFLAGS = 0x0;
    ADC0.CTRLB = 0x0;
    ADC0.CTRLC = 0x0;
    ADC0.CTRLD = 0x0;
    ADC0.CTRLE = 0x0;
    ADC0.SAMPCTRL = 0x0;
    ADC0.MUXPOS = 0x0;
    ADC0.COMMAND = 0x0;
    ADC0.EVCTRL = 0x0;
    ADC0.DBGCTRL = 0x0;
    ADC0.WINHT = 0x0;
    ADC0.WINLT = 0x0;
    ADC0.CALIB = 0x1;
}

void ADC0_Enable(void)
{
    ADC0.CTRLA |= ADC_ENABLE_bm;
}

void ADC0_Disable(void)
{
    ADC0.CTRLA &= ~ADC_ENABLE_bm;
}

void ADC0_ChannelSelect(adc_channel_t channel)
{
    ADC0.MUXPOS = channel;
}

void ADC0_ConversionStart(void)
{
    ADC0.COMMAND |= ADC_STCONV_bm;
}

void ADC0_ConversionDoneInterruptEnable(void)
{
    ADC0.INTCTRL |= ADC_RESRDY_bm;
}

void ADC0_ConversionDoneInterruptDisable(void)
{
    ADC0.INTCTRL &= ~ADC_RESRDY_bm;
}

bool ADC0_IsConversionDone(void)
{
    return (bool)(!(ADC0.COMMAND & ADC_STCONV_bm));
}

adc_result_t ADC0_ConversionResultGet(void)
{
    return (adc_result_t)(ADC0.RES);
}

void ADC0_ConversionDoneCallbackRegister(void (*callback)(void))
{
    ADC0_ConversionDoneCallback = callback;
}

adc_result_t ADC0_ChannelSelectAndConvert(adc_channel_t channel)
{
    ADC0.MUXPOS = channel;
    ADC0.COMMAND |= ADC_STCONV_bm;

    while (0U != (ADC0.COMMAND & ADC_STCONV_bm))
    {
        // Wait for conversion to finish
    }

    return (adc_result_t)(ADC0.RES);
}

uint8_t ADC0_ResolutionGet(void)
{
    return (ADC0.CTRLA & ADC_RESSEL_8BIT_gc) ? 8U : 10U;
}

void ADC0_ConversionStop(void)
{
    ADC0.COMMAND &= ~ADC_STCONV_bm;
}

void ADC0_SampleRepeatCountSet(adc_repeat_count_t repeatCount)
{
    ADC0.CTRLB = (ADC_SAMPNUM_gm & repeatCount);
}

void ADC0_ComputationModeSet(adc_computation_mode_t computationMode)
{
    if (ADC_BASIC == computationMode)
    {
        ADC0.CTRLB = ADC_NO_ACCUMULATION;
    }
    else
    {
        if (ADC_NO_ACCUMULATION == (ADC0.CTRLB & ADC_SAMPNUM_gm))
        {
            ADC0.CTRLB = ADC_2_SAMPLES_ACCUMULATED;
        }
        else
        {
            // Do nothing
        }
    }
}

void ADC0_UpperThresholdSet(adc_threshold_t upperThreshold)
{
    ADC0.WINHT = upperThreshold;
}

void ADC0_LowerThresholdSet(adc_threshold_t lowerThreshold)
{
    ADC0.WINLT = lowerThreshold;
}

void ADC0_ThresholdModeSet(adc_threshold_mode_t thresholdMode)
{
    ADC0.CTRLE = thresholdMode;
}

void ADC0_ThresholdInterruptEnable(void)
{
    ADC0.INTCTRL |= ADC_WCMP_bm;
}

void ADC0_ThresholdInterruptDisable(void)
{
    ADC0.INTCTRL &= ~ADC_WCMP_bm;
}

adc_accumulate_t ADC0_AccumulatedResultGet(void)
{
    return (adc_accumulate_t)(ADC0.RES);
}

void ADC0_ThresholdCallbackRegister(void (*callback)(void))
{
    ADC0_ThresholdCallback = callback;
}

void ADC0_ContinuousConversionEnable(void)
{
    ADC0.CTRLA |= ADC_FREERUN_bm;
}

void ADC0_ContinuousConversionDisable(void)
{
    ADC0.CTRLA &= ~ADC_FREERUN_bm;
}

void ADC0_AutoTriggerEnable(void)
{
    ADC0.EVCTRL |= ADC_STARTEI_bm;
}

void ADC0_AutoTriggerDisable(void)
{
    ADC0.EVCTRL &= ~ADC_STARTEI_bm;
}

bool ADC0_IsConversionDoneInterruptFlagSet(void)
{
    return (bool)(ADC0.INTFLAGS & ADC_RESRDY_bm);
}

void ADC0_ConversionDoneInterruptFlagClear(void)
{
    ADC0.INTFLAGS = ADC_RESRDY_bm;
}

bool ADC0_IsThresholdInterruptFlagSet(void)
{
    return (bool)(ADC0.INTFLAGS & ADC_WCMP_bm);
}

void ADC0_ThresholdInterruptFlagClear(void)
{
    ADC0.INTFLAGS = ADC_WCMP_bm;
}

/* cppcheck-suppress misra-c2012-2.7 */
/* cppcheck-suppress misra-c2012-8.2 */
/* cppcheck-suppress misra-c2012-8.4 */
/* cppcheck-suppress misra-c2012-8.6 */
ISR(ADC0_RESRDY_vect)
{
    // Clear result ready interrupt flag
    ADC0.INTFLAGS = ADC_RESRDY_bm;

    if (NULL != ADC0_ConversionDoneCallback)
    {
        ADC0_ConversionDoneCallback();
    }
    else
    {
        // Do nothing
    }
}

/* cppcheck-suppress misra-c2012-2.7 */
/* cppcheck-suppress misra-c2012-8.2 */
/* cppcheck-suppress misra-c2012-8.4 */
/* cppcheck-suppress misra-c2012-8.6 */
ISR(ADC0_WCOMP_vect)
{
    // Clear window comparator interrupt flag
    ADC0.INTFLAGS = ADC_WCMP_bm;
    
    if (NULL != ADC0_ThresholdCallback)
    {
        ADC0_ThresholdCallback();
    }
    else
    {
        // Do nothing
    }
}
