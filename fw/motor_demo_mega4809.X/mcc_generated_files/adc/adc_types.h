/**
 * ADC Type Definitions Header File
 *
 * @file adc_types.h
 *
 * @defgroup adc ADC
 *
 * @brief This header file provides type definitions for the ADC module.
 *
 * @version ADC Driver Version 2.0.0
 * 
 * @version ADC Package Version 5.0.0
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

#ifndef ADC_TYPES_H
#define	ADC_TYPES_H

#include <stdint.h>

/**
 * @ingroup adc
 * @typedef adc_result_t
 * @brief ADC conversion result type.
 */
typedef int16_t adc_result_t;

/**
 * @ingroup adc
 * @typedef adc_accumulate_t
 * @brief ADC conversion accumulator type.
 */
typedef int32_t adc_accumulate_t;

/**
 * @ingroup adc
 * @typedef adc_threshold_t
 * @brief ADC conversion threshold type.
 */
typedef int16_t adc_threshold_t;

/**
 * @ingroup adc
 * @enum adc_channel_t
 * @brief Enumeration defining all available analog channels for ADC conversion.
 */
typedef enum
{
    ADC0_CHANNEL_AIN0         = 0x0,   /**< PD0*/  
    ADC0_CHANNEL_AIN1         = 0x1,   /**< PD1*/  
    ADC0_CHANNEL_AIN2         = 0x2,   /**< PD2*/  
    ADC0_CHANNEL_AIN3         = 0x3,   /**< PD3*/  
    ADC0_CHANNEL_AIN4         = 0x4,   /**< PD4*/  
    ADC0_CHANNEL_AIN5         = 0x5,   /**< PD5*/  
    ADC0_CHANNEL_AIN6         = 0x6,   /**< PD6*/  
    ADC0_CHANNEL_AIN7         = 0x7,   /**< PD7*/  
    ADC0_CHANNEL_AIN8         = 0x8,   /**< PE0*/  
    ADC0_CHANNEL_AIN9         = 0x9,   /**< PE1*/  
    ADC0_CHANNEL_AIN10        = 0xa,   /**< PE2*/  
    ADC0_CHANNEL_AIN11        = 0xb,   /**< PE3*/  
    ADC0_CHANNEL_AIN12        = 0xc,   /**< PF2*/  
    ADC0_CHANNEL_AIN13        = 0xd,   /**< PF3*/  
    ADC0_CHANNEL_AIN14        = 0xe,   /**< PF4*/  
    ADC0_CHANNEL_AIN15        = 0xf,   /**< PF5*/  
    ADC0_CHANNEL_DACREF       = 0x1c,  /**< AC DAC Reference*/  
    ADC0_CHANNEL_TEMPSENSE    = 0x1e,  /**< Temperature sensor*/  
    ADC0_CHANNEL_GND          = 0x1f   /**< 0V (GND)*/  
} adc_channel_t;

/**
 * @ingroup adc
 * @typedef adc_computation_mode_t
 * @brief Enumeration for the ADC computation modes.
 */
typedef enum
{
    ADC_BASIC               = 0x00,     /**< No accumulation */
    ADC_SERIES_ACCUMULATE   = 0x01,     /**< Accumulate each sample */
} adc_computation_mode_t;

/**
 * @ingroup adc
 * @enum adc_repeat_count_t
 * @brief Enumeration for the ADC sample length values.
 */
typedef enum
{
    ADC_NO_ACCUMULATION           = 0x0,   /**< 1 ADC sample*/  
    ADC_2_SAMPLES_ACCUMULATED     = 0x1,   /**< Accumulate 2 samples*/  
    ADC_4_SAMPLES_ACCUMULATED     = 0x2,   /**< Accumulate 4 samples*/  
    ADC_8_SAMPLES_ACCUMULATED     = 0x3,   /**< Accumulate 8 samples*/  
    ADC_16_SAMPLES_ACCUMULATED    = 0x4,   /**< Accumulate 16 samples*/  
    ADC_32_SAMPLES_ACCUMULATED    = 0x5,   /**< Accumulate 32 samples*/  
    ADC_64_SAMPLES_ACCUMULATED    = 0x6    /**< Accumulate 64 samples*/  
} adc_repeat_count_t;

/**
 * @ingroup adc
 * @typedef adc_threshold_mode_t 
 * @brief Enumeration for the ADC window comparator modes.
 */
typedef enum
{
    ADC_NEVER_INTERRUPT                      = 0x0,   /**< No Window Comparison*/  
    ADC_BELOW_LOWER_THRESHOLD                = 0x1,   /**< Below Window*/  
    ADC_ABOVE_UPPER_THRESHOLD                = 0x2,   /**< Above Window*/  
    ADC_INSIDE_LOWER_AND_UPPER_THRESHOLD     = 0x3,   /**< Inside Window*/  
    ADC_OUTSIDE_LOWER_AND_UPPER_THRESHOLD    = 0x4    /**< Outside Window*/  
} adc_threshold_mode_t ;

#endif /* ADC_TYPES_H */