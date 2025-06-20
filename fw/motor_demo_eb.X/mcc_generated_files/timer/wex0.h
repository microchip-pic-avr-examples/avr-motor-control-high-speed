/**
 * @file wex0.h
 *
 * @brief Waveform Extension Driver API Header File
 *
 * @defgroup wex0 WEX0
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


#ifndef WEX0_H
#define WEX0_H


#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>


/**
 * @ingroup wex0
 * @brief Converts from nanoseconds to clock increments. Used for setting the dead-time or blanking time.
 * @note The macro arguments:
 * - VALUE must be a constant number rather than a variable
 * - F_CLOCK is the WEX Peripheral Clock Frequency
 * - WEX_PRESCALER can be 1, 2, 4, 8, 16, 64, 256, or 1024
 */
#define WEX0_NS_TO_TICKS(VALUE, F_CLOCK, WEX_PRESCALER) (uint8_t)( (float)(VALUE) / ( (1000000000.0 / (F_CLOCK) ) * (WEX_PRESCALER) ) + 0.5)

/**
 * @ingroup wex0
 * @brief This is the function pointer that accesses the callback function, whenever an interrupt occurs or a fault is detected.
 */
typedef void (* WEX0_cb_t)(void);


/**
 * @ingroup wex0
 * @brief Sets the Fault Interrupt callback for the WEX0 module.
 * @param[in] callback Pointer to custom callback
 * @return None.
 */
void WEX0_FAULTIsrCallbackRegister(WEX0_cb_t callback);

/**
 * @ingroup wex0
 * @brief Initializes the WEX0 module.
 * @param None.
 * @return None.
 */
void WEX0_Initialize(void);

/**
 * @ingroup wex0
 * @brief Deinitializes the WEX0 module.
 * @param None.
 * @return None.
 */
void WEX0_Deinitialize(void);

/**
 * @ingroup wex0
 * @brief Gets the status of the WEX0's blanking or fault detection.
 * @param None.
 * @return The current status
 */
uint8_t WEX0_StatusRegisterGet(void);

/**
 * @ingroup wex0
 * @brief Enables or disables the Pattern Generation mode of the WEX0 module.
 * @param[in] mode Enable or disable:
 * - @c true - Enable Pattern Generation mode
 * - @c false - Disable Pattern Generation mode
 * @return None.
 */
void WEX0_PatternGenerationMode(bool mode);

/**
 * @ingroup wex0
 * @brief Returns the Pattern Generation mode status of the WEX0 module.
 * @param None.
 * @return Whaether the Pattern Generation mode is enabled or not
 * @retval true Pattern Generation mode is enabled
 * @retval false Pattern Generation mode is disabled
 */
bool WEX0_IsPatternGenerationSet(void);

/**
 * @ingroup wex0
 * @brief Selects the Input Matrix mode of the WEX0 module.
 * @param[in] config Input Matrix:
 * - @c WEX_INMX_DIRECT_gc - Direct Input
 * - @c WEX_INMX_CWCMA_gc - Common Waveform Channel Mode A. Waveform output on a single PWM channel
 * - @c WEX_INMX_CWCMB_gc - Common Waveform Channel Mode B. Waveform output on two PWM channels
 * @return None.
 */
void WEX0_InputMatrixSet(WEX_INMX_t config);

/**
 * @ingroup wex0
 * @brief Enables the dead-time insertion on each of the Waveform Output channels. 
 * @param[in] channels Bitmask value for the channels
 * @return None.
 */
void WEX0_DeadTimeInsertionSet(uint8_t channels);

/**
 * @ingroup wex0
 * @brief Selects the update source for the WEX0 module.
 * @param[in] config Update Source:
 * - @c WEX_UPDSRC_TCPWM0_gc - Timer/Counter Type E
 * - @c WEX_UPDSRC_SW_gc - Software Commands
 * @return None.
 */
void WEX0_UpdateSourceSet(WEX_UPDSRC_t config);

/**
 * @ingroup wex0
 * @brief Sends software commands to the WEX0 module.
 * @param[in] command Command:
 * - @c WEX_CMD_NONE_gc - No Command
 * - @c WEX_CMD_UPDATE_gc - Update buffered registers
 * - @c WEX_CMD_FAULTSET_gc - Set fault detection
 * - @c WEX_CMD_FAULTCLR_gc - Clear fault detection
 * - @c WEX_CMD_BLANKSET_gc - Set software blanking
 * - @c WEX_CMD_BLANKCLR_gc - Clear software blanking
 * @return None.
 */
void WEX0_SoftwareCommand(WEX_CMD_t command);

/**
 * @ingroup wex0
 * @brief Sets the Fault Event A Filter for the WEX0 module.
 * @param[in] samples Number of samples:
 * - @c WEX_FILTER_ZERO_gc - No filtering
 * - @c WEX_FILTER_SAMPLE1_gc - One sample
 * - @c WEX_FILTER_SAMPLE2_gc - Two samples
 * - @c WEX_FILTER_SAMPLE3_gc - Three samples
 * - @c WEX_FILTER_SAMPLE4_gc - Four samples
 * - @c WEX_FILTER_SAMPLE5_gc - Five samples
 * - @c WEX_FILTER_SAMPLE6_gc - Six samples
 * - @c WEX_FILTER_SAMPLE7_gc - Seven samples
 * @return None.
 */
void WEX0_FaultAEventFilter(WEX_FILTER_t samples);

/**
 * @ingroup wex0
 * @brief Enables or disables Fault Event Blanking A for the WEX0 module.
 * @param[in] en Enable or disable:
 * - @c true - Enable fault event blanking
 * - @c false - Disable fault event blanking
 * @return None.
 */
void WEX0_FaultAEventBlankingEnable(bool en);

/**
 * @ingroup wex0
 * @brief Enables or disables Fault Event Input A for the WEX0 module.
 * @param[in] en Enable or disable:
 * - @c true - Enable fault event input
 * - @c false - Disable fault event input
 * @return None.
 */
void WEX0_FaultAEventInputEnable(bool en);

/**
 * @ingroup wex0
 * @brief Sets the Fault Event B Filter for the WEX0 module.
 * @param[in] samples Number of samples:
 * - @c WEX_FILTER_ZERO_gc - No filtering
 * - @c WEX_FILTER_SAMPLE1_gc - One sample
 * - @c WEX_FILTER_SAMPLE2_gc - Two samples
 * - @c WEX_FILTER_SAMPLE3_gc - Three samples
 * - @c WEX_FILTER_SAMPLE4_gc - Four samples
 * - @c WEX_FILTER_SAMPLE5_gc - Five samples
 * - @c WEX_FILTER_SAMPLE6_gc - Six samples
 * - @c WEX_FILTER_SAMPLE7_gc - Seven samples
 * @return None.
 */
void WEX0_FaultBEventFilter(WEX_FILTER_t samples);

/**
 * @ingroup wex0
 * @brief Enables or disables Fault Event Blanking B for the WEX0 module.
 * @param[in] en Enable or disable:
 * - @c true - Enable fault event blanking
 * - @c false - Disable fault event blanking
 * @return None.
 */
void WEX0_FaultBEventBlankingEnable(bool en);

/**
 * @ingroup wex0
 * @brief Enables or disables Fault Event Input B for the WEX0 module.
 * @param[in] en Enable or disable:
 * - @c true - Enable fault event input
 * - @c false - Disable fault event input
 * @return None.
 */
void WEX0_FaultBEventInputEnable(bool en);

/**
 * @ingroup wex0
 * @brief Sets the Fault Event C Filter for the WEX0 module.
 * @param[in] samples Number of samples:
 * - @c WEX_FILTER_ZERO_gc - No filtering
 * - @c WEX_FILTER_SAMPLE1_gc - One sample
 * - @c WEX_FILTER_SAMPLE2_gc - Two samples
 * - @c WEX_FILTER_SAMPLE3_gc - Three samples
 * - @c WEX_FILTER_SAMPLE4_gc - Four samples
 * - @c WEX_FILTER_SAMPLE5_gc - Five samples
 * - @c WEX_FILTER_SAMPLE6_gc - Six samples
 * - @c WEX_FILTER_SAMPLE7_gc - Seven samples
 * @return None.
 */
void WEX0_FaultCEventFilter(WEX_FILTER_t samples);

/**
 * @ingroup wex0
 * @brief Enables or disables Fault Event Blanking C for the WEX0 module.
 * @param[in] en Enable or disable:
 * - @c true - Enable fault event blanking
 * - @c false - Disable fault event blanking
 * @return None.
 */
void WEX0_FaultCEventBlankingEnable(bool en);

/**
 * @ingroup wex0
 * @brief Enables or disables Fault Event Input C for the WEX0 module.
 * @param[in] en Enable or disable:
 * - @c true - Enable fault event input
 * - @c false - Disable fault event input
 * @return None.
 */
void WEX0_FaultCEventInputEnable(bool en);

/**
 * @ingroup wex0
 * @brief Sets the Blanking Prescaler for the WEX0 module.
 * @param[in] prescaler Prescaler:
 * - @c WEX_BLANKPRESC_DIV1_gc - No prescaler
 * - @c WEX_BLANKPRESC_DIV4_gc - Prescaler 4
 * - @c WEX_BLANKPRESC_DIV16_gc - Prescaler 16
 * - @c WEX_BLANKPRESC_DIV64_gc - Prescaler 64
 * @return None.
 */
void WEX0_BlankingPrescaler(WEX_BLANKPRESC_t prescaler);

/**
 * @ingroup wex0
 * @brief Sets the Blanking Trigger source for the WEX0 module.
 * @param[in] trig Blanking Trigger:
 * - @c WEX_BLANKTRIG_NONE_gc - Software command only
 * - @c WEX_BLANKTRIG_TCE0UPD_gc - Timer/Counter Type E Update Condition
 * - @c WEX_BLANKTRIG_TCE0CMP0_gc - Timer/Counter Type E Compare 0 Condition
 * - @c WEX_BLANKTRIG_TCE0CMP1_gc - Timer/Counter Type E Compare 1 Condition
 * - @c WEX_BLANKTRIG_TCE0CMP2_gc - Timer/Counter Type E Compare 2 Condition
 * - @c WEX_BLANKTRIG_TCE0CMP3_gc - Timer/Counter Type E Compare 3 Condition
 * @return None.
 */
void WEX0_BlankingTrigger(WEX_BLANKTRIG_t trig);

/**
 * @ingroup wex0
 * @brief Sets the Blanking Time for the WEX0 module.
 * @param[in] cnt Blanking Time in clock cycles
 * @return None.
 */
void WEX0_BlankingTimeSet(uint8_t cnt);

/**
 * @ingroup wex0
 * @brief Gets the Blanking Time for the WEX0 module.
 * @param None.
 * @return Blanking Time in clock cycles
 */
uint8_t WEX0_BlankingTimeGet(void);

/**
 * @ingroup wex0
 * @brief Sets the Fault Detection on Debug Break Detection for the WEX0 module.
 * @param[in] mode Mode:
 * - @c WEX_FDDBD_FAULT_gc - If fault protection is enabled, the fault is triggered on debug request
 * - @c WEX_FDDBD_IGNORE_gc - Debug request isn't going to trigger a fault
 * @return None.
 */
void WEX0_FaultDetectionDebugBreak(WEX_FDDBD_t mode);

/**
 * @ingroup wex0
 * @brief Sets the Fault Detection Restart Mode for the WEX0 module.
 * @param[in] mode Mode:
 * - @c WEX_FDMODE_LATCHED_gc - Latched mode -> Output will remain in a Fault state until the fault condition is no longer active and the fault is cleared by software
 * - @c WEX_FDMODE_CBC_gc - Cycle-by-Cycle mode -> Output will remain in the fault state until the fault condition is no longer active
 * @return None.
 */
void WEX0_FaultDetectionRestartMode(WEX_FDMODE_t mode);

/**
 * @ingroup wex0
 * @brief Sets the Fault Detection Action for the WEX0 module.
 * @param[in] action Action:
 * - @c WEX_FDACT_NONE_gc - Fault protection is disabled
 * - @c WEX_FDACT_LOW_gc - Fault protection is enabled and the output is driven low
 * - @c WEX_FDACT_CUSTOM_gc - Fault protection is enabled and drive all pins to setting defined by FAULTDRV and FAULTOUT registers
 * @return None.
 */
void WEX0_FaultDetectionAction(WEX_FDACT_t action);

/**
 * @ingroup wex0
 * @brief Sets if an output channel is tri-stated or overwritten by the custom fault value defined by the user in case a fault is detected.
 * @param[in] channels Bitmask value for the channels
 * @return None.
 */
void WEX0_FaultDriveSet(uint8_t channels);

/**
 * @ingroup wex0
 * @brief Sets the output values of the channels in case of a fault detection.
 * @param[in] channels Bitmask value for the channels
 * @return None.
 */
void WEX0_FaultOutputSet(uint8_t channels);

/**
 * @ingroup wex0
 * @brief Enables the Fault Interrupt on the WEX0 module.
 * @param None.
 * @return None.
 */
void WEX0_FaultEnable(void);

/**
 * @ingroup wex0
 * @brief Returns the status of the Fault Interrupt on the WEX0 module.
 * @param None.
 * @return bool Whether the fault is enabled or not
 * @retval true Fault interrupt is enabled
 * @retval false Fault interrupt is disabled
 */
bool WEX0_IsFaultEnabled(void);

/**
 * @ingroup wex0
 * @brief Disables the Fault Interrupt on the WEX0 module.
 * @param None.
 * @return None.
 */
void WEX0_FaultDisable(void);

/**
 * @ingroup wex0
 * @brief Clears interrupt flags on the WEX0 module.
 * @param[in] flags Bitmask value for the channels
 * @return None.
 */
void WEX0_FaultFlagsClear(uint8_t flags);

/**
 * @ingroup wex0
 * @brief Returns the interrupt flags on the WEX0 module.
 * @param None.
 * @return Interrupt flag status:
 * - Bit 0 is set by the the Fault Interrupt
 * - Bit 2 is set by the the Fault Detection Flag Event Input A
 * - Bit 3 is set by the the Fault Detection Flag Event Input B
 * - Bit 4 is set by the the Fault Detection Flag Event Input C
 */
uint8_t WEX0_FaultFlagsGet(void);

/**
 * @ingroup wex0
 * @brief Sets the dead-time on the low side of the output channels on the WEX0 module.
 * @param[in] cnt Dead-time in clock cycles
 * @return None.
 */
void WEX0_DeadTimeLowSideSet(uint8_t cnt);

/**
 * @ingroup wex0
 * @brief Sets the dead-time on the high side of the output channels on the WEX0 module.
 * @param[in] cnt Dead-time in clock cycles
 * @return None.
 */
void WEX0_DeadTimeHighSideSet(uint8_t cnt);

/**
 * @ingroup wex0
 * @brief Sets the dead-time on both sides of the side output channels on the WEX0 module.
 * @param[in] cnt Dead-time in clock cycles
 * @return None.
 */
void WEX0_DeadTimeBothSidesSet(uint8_t cnt);

/**
 * @ingroup wex0
 * @brief Sets which pair channels will have the output swapped (output [2n] with output [2n+1]) on the WEX0 module.
 * @param[in] channels Bitmask value for the channels
 * @return None.
 */
void WEX0_SwapChannelSet(uint8_t channels);

/**
 * @ingroup wex0
 * @brief Sets which channels will have the output overridden by the Pattern Generation Mode on the WEX0 module.
 * @param[in] channels Bitmask value for the channels
 * @return None.
 */
void WEX0_PatternGenerationOverrideSet(uint8_t channels);

/**
 * @ingroup wex0
 * @brief Sets the output values of the channels in the Pattern Generation Mode on the WEX0 module.
 * @param[in] channels Bitmask value for the channels
 * @return None.
 */
void WEX0_PatternGenerationOutputSet(uint8_t channels);

/**
 * @ingroup wex0
 * @brief Enables or disables the output override on the WEX0 module.
 * @param[in] channels Bitmask value for the channels
 * @return None.
 */
void WEX0_OutputOverrideEnable(uint8_t channels);

/**
 * @ingroup wex0
 * @brief Sets the dead-time on the low side of the output channels using a buffer register on the WEX0 module.
 * @param[in] buff Dead-time in clock cycles
 * @return None.
 */
void WEX0_DeadTimeLowSideBufferSet(uint8_t buff);

/**
 * @ingroup wex0
 * @brief Sets the dead-time on the high side of the output channels using a buffer register on the WEX0 module.
 * @param[in] buff Dead-time in clock cycles
 * @return None.
 */
void WEX0_DeadTimeHighSideBufferSet(uint8_t buff);

/**
 * @ingroup wex0
 * @brief Sets the dead-time on both sides of the output channels using a buffer register on the WEX0 module.
 * @param[in] buff Dead-time in clock cycles
 * @return None.
 */
void WEX0_DeadTimeBothSidesBufferSet(uint8_t buff);

/**
 * @ingroup wex0
 * @brief Sets which pair channels will have the output swapped (output [2n] with output [2n+1]) using a buffer register on the WEX0 module.
 * @param[in] buff Bitmask value for the channels
 * @return None.
 */
void WEX0_SwapChannelBufferSet(uint8_t buff);

/**
 * @ingroup wex0
 * @brief Sets which channels will have the output overridden by the Pattern Generation Mode using a buffer register on the WEX0 module.
 * @param[in] buff Bitmask value for the channels
 * @return None.
 */
void WEX0_PatternGenerationOverrideBufferSet(uint8_t buff);

/**
 * @ingroup wex0
 * @brief Sets the output values of the channels in the Pattern Generation Mode using a buffer register on the WEX0 module.
 * @param[in] buff Bitmask value for the channels
 * @return None.
 */
void WEX0_PatternGenerationOutputBufferSet(uint8_t buff);


#endif /* WEX0_H */
