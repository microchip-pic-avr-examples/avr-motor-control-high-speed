/**
 * ADC Type Definitions Header File
 *
 * @file adc_types.h
 *
 * @defgroup adc ADC
 *
 * @brief This header file provides the type definitions for the ADC module operation.
 *
 * @version ADC Driver Version 2.0.0
 *
 * @version ADC Module Version 2.0.0
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
#define ADC_TYPES_H

/**
 @ingroup adc
 @brief ADC 8-bit resolution value.
*/
#define ADC_RESOLUTION_8BIT 8U

/**
 @ingroup adc
 @brief ADC 12-bit resolution value.
*/
#define ADC_RESOLUTION_12BIT 12U


/**
 @ingroup adc
 @brief ADC bit set value.
*/
#define ADC_BIT_SET 1U

/**
 @ingroup adc
 @brief ADC bit clear value.
*/
#define ADC_BIT_CLEAR 0U

/**
 * @ingroup adc
 * @typedef adc_result_t
 * @brief ADC conversion result type.
*/
typedef int16_t adc_result_t;

/**
 * @ingroup adc
 * @typedef adc_threshold_t
 * @brief ADC conversion threshold type.
*/
typedef int16_t adc_threshold_t;

/**
 * @ingroup adc
 * @typedef adc_accumulate_t
 * @brief ADC conversion accumulator type.
*/
typedef int32_t adc_accumulate_t;

/**
 * @ingroup adc
 * @typedef adc_computation_mode_t
 * @brief Enumeration for the ADC computation modes.
 */
typedef enum
{
    ADC_MODE_SINGLE_8BIT = 0x0, /**< Single Conversion with 8-bit resolution*/
    ADC_MODE_SINGLE_12BIT = 0x1, /**< Single Conversion with 12-bit resolution*/
    ADC_MODE_SERIES = 0x2, /**< Series with accumulation, separate trigger for every 12-bit conversion*/
    ADC_MODE_SERIES_SCALING = 0x3, /**< Series with accumulation and scaling, separate trigger for every 12-bit conversion*/
    ADC_MODE_BURST = 0x4, /**< Burst with accumulation, one trigger will run SAMPNUM 12-bit conversions*/
    ADC_MODE_BURST_SCALING = 0x5 /**< Burst with accumulation and scaling, one trigger will run SAMPNUM 12-bit conversions*/
} adc_computation_mode_t;

/**
 * @ingroup adc
 * @enum adc_gain_t
 * @brief Enumeration defining the available gain settings for the PGA.
*/
typedef enum
{
    ADC_GAIN_1X = 0x0, /**< PGA 1x gain*/  
    ADC_GAIN_2X = 0x1, /**< PGA 2x gain*/  
    ADC_GAIN_4X = 0x2, /**< PGA 4x gain*/  
    ADC_GAIN_8X = 0x3, /**< PGA 8x gain*/  
    ADC_GAIN_16X = 0x4 /**< PGA 16x gain*/  
} adc_gain_t;

/**
 * @ingroup adc
 * @enum adc_pga_bias_sel_t
 * @brief Enumeration defining the available bias currents supplied to the PGA.
*/
typedef enum
{
    ADC_PGABIASSEL_100PCT = 0x0, /**< PGA 100% BIAS current.*/  
    ADC_PGABIASSEL_75PCT = 0x1, /**< PGA 75% BIAS current. Usable for CLK_ADC<4.5MHz*/  
    ADC_PGABIASSEL_50PCT = 0x2, /**< PGA 50% BIAS current. Usable for CLK_ADC<3MHz*/  
    ADC_PGABIASSEL_25PCT = 0x3 /**< PGA 25% BIAS current. Usable for CLK_ADC<1.5MHz*/  
} adc_pga_bias_sel_t;

/**
 * @ingroup adc
 * @enum adc_channel_t
 * @brief Enumeration defining all available analog channels for the ADC conversion.
*/
typedef enum
{
    ADC0_CHANNEL_AIN0 = 0x0, /**< PD0*/
    ADC0_CHANNEL_AIN1 = 0x1, /**< PD1*/
    ADC0_CHANNEL_AIN2 = 0x2, /**< PD2*/
    ADC0_CHANNEL_AIN3 = 0x3, /**< PD3*/
    ADC0_CHANNEL_AIN4 = 0x4, /**< PD4*/
    ADC0_CHANNEL_AIN5 = 0x5, /**< PD5*/
    ADC0_CHANNEL_AIN6 = 0x6, /**< PD6*/
    ADC0_CHANNEL_AIN7 = 0x7, /**< PD7*/
    ADC0_CHANNEL_AIN16 = 0x10, /**< PF0*/
    ADC0_CHANNEL_AIN17 = 0x11, /**< PF1*/
    ADC0_CHANNEL_AIN18 = 0x12, /**< PF2*/
    ADC0_CHANNEL_AIN19 = 0x13, /**< PF3*/
    ADC0_CHANNEL_AIN20 = 0x14, /**< PF4*/
    ADC0_CHANNEL_AIN21 = 0x15, /**< PF5*/
    ADC0_CHANNEL_AIN22 = 0x16, /**< PA2*/
    ADC0_CHANNEL_AIN23 = 0x17, /**< PA3*/
    ADC0_CHANNEL_AIN24 = 0x18, /**< PA4*/
    ADC0_CHANNEL_AIN25 = 0x19, /**< PA5*/
    ADC0_CHANNEL_AIN26 = 0x1a, /**< PA6*/
    ADC0_CHANNEL_AIN27 = 0x1b, /**< PA7*/
    ADC0_CHANNEL_AIN28 = 0x1c, /**< PC0*/
    ADC0_CHANNEL_AIN29 = 0x1d, /**< PC1*/
    ADC0_CHANNEL_AIN30 = 0x1e, /**< PC2*/
    ADC0_CHANNEL_AIN31 = 0x1f, /**< PC3*/
    ADC0_CHANNEL_GND = 0x30, /**< Ground*/
    ADC0_CHANNEL_VDD10 = 0x31, /**< VDD Divided by 10*/
    ADC0_CHANNEL_TEMPSENSE = 0x32, /**< Temperature Sensor*/
    ADC1_CHANNEL_GND = 0x30, /**< Ground*/
    ADC1_CHANNEL_VDD10 = 0x31, /**< VDD Divided by 10*/
    ADC1_CHANNEL_TEMPSENSE = 0x32 /**< Temperature Sensor*/
} adc_channel_t;


/**
 * @ingroup adc
 * @typedef adc_threshold_mode_t 
 * @brief Enumeration for the ADC window comparator modes.
 */
typedef enum
{
    ADC_NEVER_INTERRUPT = 0x0, /**< No Window Comparison*/
    ADC_BELOW_LOWER_THRESHOLD = 0x1, /**< Below Window*/
    ADC_ABOVE_UPPER_THRESHOLD = 0x2, /**< Above Window*/
    ADC_INSIDE_LOWER_AND_UPPER_THRESHOLD = 0x3, /**< Inside Window*/
    ADC_OUTSIDE_LOWER_AND_UPPER_THRESHOLD = 0x4 /**< Outside Window*/
} adc_threshold_mode_t;

/**
 * @ingroup adc
 * @typedef adc_trigger_source_t 
 * @brief Enumeration for the ADC auto-trigger sources.
 */
typedef enum
{
    ADC_MUXPOS_WRITE = ADC_START_MUXPOS_WRITE_gc,
    ADC_MUXNEG_WRITE = ADC_START_MUXNEG_WRITE_gc,
    ADC_EVENT_TRIGGER = ADC_START_EVENT_TRIGGER_gc
} adc_trigger_source_t;

/**
 * @ingroup adc
 * @typedef adc_repeat_count_t
 * @brief Enumeration for the ADC sample length values.
*/
typedef enum 
{
    ADC_NO_ACCUMULATION = 0x0, /**< No accumulation*/
    ADC_2_SAMPLES_ACCUMULATED = 0x1, /**< 2 samples accumulated*/
    ADC_4_SAMPLES_ACCUMULATED = 0x2, /**< 4 samples accumulated*/
    ADC_8_SAMPLES_ACCUMULATED = 0x3, /**< 8 samples accumulated*/
    ADC_16_SAMPLES_ACCUMULATED = 0x4, /**< 16 samples accumulated*/
    ADC_32_SAMPLES_ACCUMULATED = 0x5, /**< 32 samples accumulated*/
    ADC_64_SAMPLES_ACCUMULATED = 0x6, /**< 64 samples accumulated*/
    ADC_128_SAMPLES_ACCUMULATED = 0x7, /**< 128 samples accumulated*/
    ADC_256_SAMPLES_ACCUMULATED = 0x8, /**< 256 samples accumulated*/
    ADC_512_SAMPLES_ACCUMULATED = 0x9 /**< 512 samples accumulated*/
} adc_repeat_count_t;


#endif // ADC_TYPES_H