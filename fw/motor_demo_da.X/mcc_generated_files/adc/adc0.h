/**
 * ADC0 Generated Driver API Header File
 * 
 * @file adc0.h
 * 
 * @defgroup  adc0 Analog-to-Digital Converter (ADC0)
 * 
 * @brief This file contains the API prototypes and data types for the ADC0 driver.
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


#ifndef ADC0_H
#define ADC0_H

#include "../system/utils/compiler.h"
#include "./adc_types.h"

/**
 * @ingroup adc0
 * @brief Defines the Custom Name pin mapping for channels in @ref adc_channel_t
 */
#define VBUS ADC0_CHANNEL_AIN0

/**
 * @ingroup adc0
 * @brief Defines the Custom Name pin mapping for channels in @ref adc_channel_t
 */
#define POT ADC0_CHANNEL_AIN1

/**
 * @ingroup adc0
 * @brief Defines the Custom Name pin mapping for channels in @ref adc_channel_t
 */
#define BEMF_B ADC0_CHANNEL_AIN2

/**
 * @ingroup adc0
 * @brief Defines the Custom Name pin mapping for channels in @ref adc_channel_t
 */
#define BEMF_C ADC0_CHANNEL_AIN4

/**
 * @ingroup adc0
 * @brief Defines the Custom Name pin mapping for channels in @ref adc_channel_t
 */
#define BEMF_A ADC0_CHANNEL_AIN6

/**
 * @ingroup adc0
 * @brief Defines the Custom Name pin mapping for channels in @ref adc_channel_t
 */
#define CRT ADC0_CHANNEL_AIN10

/**
 * @ingroup adc0
 * @brief Initializes the registers based on the configurable options in the MPLABÂ® Code Configurator (MCC) Melody UI for the Analog-to-Digital Converter (ADC) operation.
 * @param None.
 * @return None.
 */
void ADC0_Initialize(void);

/**
 * @ingroup adc0
 * @brief Deinitializes the registers to Power-on Reset values.
 * @param None.
 * @return None.
 */
void ADC0_Deinitialize(void);

/**
 * @ingroup adc0
 * @brief Sets the ADC Enable bit to `1`.
 * @param None.
 * @return None.
 */
void ADC0_Enable(void);

/**
 * @ingroup adc0
 * @brief Sets the ADC Enable bit to `0`.
 * @param None.
 * @return None.
 */
void ADC0_Disable(void);

/**
 * @ingroup adc0
 * @brief Sets the channel to use for the ADC conversion.
 * @param channel Desired analog channel. Refer to the @ref adc_channel_t enum for the list of available analog channels.
 * @return None.
 */
void ADC0_ChannelSelect(adc_channel_t channel);

/**
 * @ingroup adc0
 * @brief Starts the ADC conversion on a selected channel. 
 * @pre Select the channel using @ref ADC0_ChannelSelect and 
 * call @ref ADC0_Initialize(void) to initialize the ADC module before using this API.
 * @return None.
 */
void ADC0_ConversionStart(void);

/**
 * @ingroup adc0
 * @brief Sets the Result Ready Interrupt Enable (RESRDY) bit to `1`.
 * @param None.
 * @return None.
 */
void ADC0_ConversionDoneInterruptEnable(void);

/**
 * @ingroup adc0
 * @brief Sets the Result Ready Interrupt Enable (RESRDY) bit to `0`.
 * @param None.
 * @return None.
 */
void ADC0_ConversionDoneInterruptDisable(void);

/**
 * @ingroup adc0
 * @brief Checks if the ongoing ADC conversion is complete.
 * @param None.
 * @retval True - The conversion is complete
 * @retval False - The conversion is ongoing
 */
bool ADC0_IsConversionDone(void);

/**
 * @ingroup adc0
 * @brief Retrieves the result of the latest conversion.
 * @param None.
 * @return adc_result_t - The result of the conversion
 */
adc_result_t ADC0_ConversionResultGet(void);

/**
 * @ingroup adc0
 * @brief Sets the callback function for the Result Ready Interrupt (RESRDY).
 * @param *callback The pointer to the function to be executed
 * @return None.
 */
void ADC0_ConversionDoneCallbackRegister(void (*callback)(void));

/**
 * @ingroup adc0
 * @brief Starts the conversion and retrieves the result of one conversion on the selected channel. 
 * @param channel Desired analog channel. Refer to the @ref adc_channel_t enum for the list of available analog channels.
 * @return adc_result_t - The result of the conversion
 */
adc_result_t ADC0_ChannelSelectAndConvert(adc_channel_t channel);

/**
 * @ingroup adc0
 * @brief Returns the resolution of the ADC module.
 * @param None.
 * @return uint8_t - Resolution value
 */
uint8_t ADC0_ResolutionGet(void);

/**
 * @ingroup adc0
 * @brief Stops the ongoing ADC conversion.
 * @param None.
 * @return None.
 */
void ADC0_ConversionStop(void);

/**
 * @ingroup adc0
 * @brief Loads the Sample Length with the specified value.
 * @param repeatCount Repeat count value. Refer to the @ref adc_repeat_count_t enum for the list of available repeat count values.
 * @return None.
 */
void ADC0_SampleRepeatCountSet(adc_repeat_count_t repeatCount);

/**
 * @ingroup adc0
 * @brief Sets the Computation mode. 
 * @param computationMode Desired computation mode. Refer to the @ref adc_computation_mode_t enum for the list of available computation modes.
 * @return None.
 */
void ADC0_ComputationModeSet(adc_computation_mode_t computationMode);

/**
 * @ingroup adc0
 * @brief Sets the value of the Window Comparator High Threshold (WINHT) register.
 * @param upperThreshold Upper threshold value of the @ref adc_threshold_t type
 * @return None.
 */
void ADC0_UpperThresholdSet(adc_threshold_t upperThreshold);

/**
 * @ingroup adc0
 * @brief Sets the value of the Window Comparator Low Threshold (WINLT) register.
 * @param lowerThreshold Lower threshold value of the @ref adc_threshold_t type
 * @return None.
 */
void ADC0_LowerThresholdSet(adc_threshold_t upperThreshold);

/**
 * @ingroup adc0
 * @brief Sets the Window Comparator mode.
 * @param thresholdMode Desired threshold mode. Refer to the @ref adc_threshold_mode_t enum for the list of available threshold modes.
 * @return None.
 */
void ADC0_ThresholdModeSet(adc_threshold_mode_t thresholdMode);

/**
 * @ingroup adc0
 * @brief Sets the Window Comparator Interrupt Enable (WCMP) bit to `1`.
 * @param None.
 * @return None.
 */
void ADC0_ThresholdInterruptEnable(void);

/**
 * @ingroup adc0
 * @brief Sets the Window Comparator Interrupt Enable (WCMP) bit to `0`.
 * @param None.
 * @return None.
 */
void ADC0_ThresholdInterruptDisable(void);

/**
 * @ingroup adc0
 * @brief Retrieves the value of the accumulated conversions.
 * @param None.
 * @return adc_accumulate_t - The value of accumulated conversions
 */
adc_accumulate_t ADC0_AccumulatedResultGet(void);

/**
 * @ingroup adc0
 * @brief Sets the callback function for the Window Comparator Interrupt (WCMP).
 * @param *callback The pointer to the function to be executed
 * @return None.
 */
void ADC0_ThresholdCallbackRegister(void (*callback)(void));

/**
 * @ingroup adc0
 * @brief Sets the Free-Running (FREERUN) bit to `1`.
 * @param None.
 * @return None.
 */
void ADC0_ContinuousConversionEnable(void);

/**
 * @ingroup adc0
 * @brief Sets the Free-Running (FREERUN) bit to `0`.
 * @param None.
 * @return None.
 */
void ADC0_ContinuousConversionDisable(void);

/**
 * @ingroup adc0
 * @brief Sets the Start Event Input (STARTEI) bit to `1`.
 * @param None.
 * @return None.
 */
void ADC0_AutoTriggerEnable(void);

/**
 * @ingroup adc0
 * @brief Sets the Start Event Input (STARTEI) bit to `0`.
 * @param None.
 * @return None.
 */
void ADC0_AutoTriggerDisable(void);

/**
 * @ingroup adc0
 * @brief Checks the Result Ready Interrupt (RESRDY) flag status.
 * @param None.
 * @retval True - RESRDY flag is set
 * @retval False - RESRDY flag is not set
 */
bool ADC0_IsConversionDoneInterruptFlagSet(void);

/**
 * @ingroup adc0
 * @brief Clears the Result Ready Interrupt (RESRDY) flag.
 * @param None.
 * @return None.
 */
void ADC0_ConversionDoneInterruptFlagClear(void);

/**
 * @ingroup adc0
 * @brief Checks the Window Comparator Interrupt (WCMP) flag status.
 * @param None.
 * @retval True - WCMP flag is set
 * @retval False - WCMP flag is not set
 */
bool ADC0_IsThresholdInterruptFlagSet(void);

/**
 * @ingroup adc0
 * @brief Clears the Window Comparator Interrupt (WCMP) flag.
 * @param None.
 * @return None.
 */
void ADC0_ThresholdInterruptFlagClear(void);

#endif /* ADC0_H */