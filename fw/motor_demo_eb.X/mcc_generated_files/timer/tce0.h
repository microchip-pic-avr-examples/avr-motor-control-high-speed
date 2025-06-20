/**
 * @file tce0.h
 *
 * @brief Timer/Counter Type E Driver API Header File
 *
 * @defgroup tce0 TCE0
 *
 * @version TCE0 Driver Version 1.0.1
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


#ifndef TCE0_H
#define TCE0_H


#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>



/**
 * @ingroup tce0
 * @brief Converts from microseconds to clock increments for setting the period.
 */
#define TCE0_PER_US_TO_TICKS(US, F_CLOCK, TCE_PRESCALER) (uint16_t)(((float)(F_CLOCK) * (float)(US)) / (1000000.0 * (float)(TCE_PRESCALER)) + 0.5) - 1

/**
 * @ingroup tce0
 * @brief Converts from milliseconds to clock increments for setting the period.
 */
#define TCE0_PER_MS_TO_TICKS(MS, F_CLOCK, TCE_PRESCALER) (uint16_t)(((float)(F_CLOCK) * (float)(MS)) / (1000.0 * (float)(TCE_PRESCALER)) + 0.5) - 1

/**
 * @ingroup tce0
 * @brief Converts from seconds to clock increments for setting the period.
 */
#define TCE0_PER_S_TO_TICKS(S, F_CLOCK, TCE_PRESCALER)  (uint16_t)(((float)(F_CLOCK) * (float)(S)) / (1.0 * (float)(TCE_PRESCALER)) + 0.5) - 1

/**
 * @ingroup tce0
 * @brief Converts from microseconds to clock increments for setting the compare registers.
 */
#define TCE0_CMP_US_TO_TICKS(US, F_CLOCK, TCE_PRESCALER) (uint16_t)(((float)(F_CLOCK) * (float)(US)) / (1000000.0 * (float)(TCE_PRESCALER)) + 0.5)

/**
 * @ingroup tce0
 * @brief Converts from milliseconds to clock increments for setting the compare registers.
 */
#define TCE0_CMP_MS_TO_TICKS(MS, F_CLOCK, TCE_PRESCALER) (uint16_t)(((float)(F_CLOCK) * (float)(MS)) / (1000.0 * (float)(TCE_PRESCALER)) + 0.5)

/**
 * @ingroup tce0
 * @brief Converts from seconds to clock increments for setting the compare registers.
 */
#define TCE0_CMP_S_TO_TICKS(S, F_CLOCK, TCE_PRESCALER)  (uint16_t)(((float)(F_CLOCK) * (float)(S)) / (1.0 * (float)(TCE_PRESCALER)) + 0.5)

/**
 * @ingroup tce0
 * @brief Converts from hertz to clock increments.
 * @note Used in Frequency mode.
 */
#define TCE0_HZ_TO_CLOCKS_FREQUENCYMODE(HZ, F_CLOCK, TCE_PRESCALER)(uint16_t)((float)(F_CLOCK) / (2 * (float)(HZ) * (float)(TCE_PRESCALER)) - 1)



/**
 * @ingroup tce0
 * @brief Lists the possible states of the TCE0 module.
 */
typedef enum
{
    TCE_STATUS_IDLE    = 0,/**< The timer is not running */
    TCE_STATUS_RUNNING = 1,/**< The timer is running */
}
TCE0_status_t;


/**
 * @ingroup tce0
 * @brief Initializes the TCE0 module. 
 * @note This routine must be called before any other TCE0 APIs.
 * @param None.
 * @return None.
 */
void TCE0_Initialize(void);

/**
 * @ingroup tce0
 * @brief Deinitializes the TCE0 module.
 * @param None.
 * @return None.
 */
void TCE0_Deinitialize(void);

/**
 * @ingroup tce0
 * @brief Starts the TCE0 module.
 * @param None.
 * @return None.
 */
void TCE0_Start(void);

/**
 * @ingroup tce0
 * @brief Stops the TCE0 module.
 * @param None.
 * @return None.
 */
void TCE0_Stop(void);

/**
 * @ingroup tce0
 * @brief Returns the status of the TCE0 module.
 * @param None.
 * @return Status of the TCE0 module
 * @retval TCE_STATUS_IDLE The timer is not running
 * @retval TCE_STATUS_RUNNING The timer is running
 */
TCE0_status_t TCE0_StatusGet(void);

/**
 * @ingroup tce0
 * @brief Sets the Waveform Generation mode for the TCE0 module.
 * @param[in] mode Operation mode:
 * - @c TCE_WGMODE_NORMAL_gc - Normal mode
 * - @c TCE_WGMODE_FRQ_gc - Frequency Generation mode
 * - @c TCE_WGMODE_SINGLESLOPE_gc - Single-Slope PWM mode
 * - @c TCE_WGMODE_DSTOP_gc - Dual-Slope PWM, overflow on TOP mode
 * - @c TCE_WGMODE_DSBOTH_gc - Dual-Slope PWM, overflow on TOP and BOTTOM mode
 * - @c TCE_WGMODE_DSBOTTOM_gc - Dual-Slope PWM, overflow on BOTTOM mode
 * @return None.
 */
void TCE0_ModeSet(TCE_WGMODE_t mode);

/**
 * @ingroup tce0
 * @brief Enables the OVF, CMP0, CMP1, CMP2, or CMP3 interrupts of the TCE0 module.
 * @param[in] interrupts Interrupt(s) to be enabled
 * @return None.
 */
void TCE0_Interrupts_Enable(uint8_t interrupts);

/**
 * @ingroup tce0
 * @brief Clears the OVF, CMP0, CMP1, CMP2, or CMP3 interrupt flags of the TCE0 module.
 * @param[in] interrupts Interrupt(s) flags to be cleared
 * @return None.
 */
void TCE0_Interrupts_FlagsClear(uint8_t interrupts);

/**
 * @ingroup tce0
 * @brief Returns the OVF, CMP0, CMP1, CMP2, or CMP3 interrupt flags of the TCE0 module.
 * @param None.
 * @return uint8_t Interrupt flag status:
 * - Bit 0 is set by the the OVF interrupt
 * - Bit 4 is set by the the CMP0 interrupt
 * - Bit 5 is set by the the CMP1 interrupt
 * - Bit 6 is set by the the CMP2 interrupt
 * - Bit 7 is set by the the CMP3 interrupt
 */
uint8_t TCE0_Interrupts_FlagsGet(void);

/**
 * @ingroup tce0
 * @brief Disables the OVF, CMP0, CMP1, CMP2, or CMP3 interrupts of the TCE0 module.
 * @param[in] interrupts Interrupt(s) to be disabled.
 * @return None.
 */
void TCE0_Interrupts_Disable(uint8_t interrupts);

/**
 * @ingroup tce0
 * @brief Enables or disables the waveform outputs for the TCE0 module.
 * @param[in] mode Output mode
 * @return None.
 */
void TCE0_Event_OutputMode(uint8_t mode);

/**
 * @ingroup tce0
 * @brief Configures the input events for the TCE0 module.
 * @param[in] value Input event configuration
 * @return None.
 */
void TCE0_Event_InputConfig(uint8_t value);

/**
 * @ingroup tce0
 * @brief Sends a software command to the TCE0 module.
 * @param[in] command Software command.
 * - @c TCE_CMD_NONE_gc - No Command
 * - @c TCE_CMD_UPDATE_gc - Force Update
 * - @c TCE_CMD_RESTART_gc - Force Restart
 * - @c TCE_CMD_RESET_gc - Force Hard Reset
 * @return None.
 */
void TCE0_SoftwareCommand(TCE_CMD_t command);

/**
 * @ingroup tce0
 * @brief Enables or disables the Run in Standby mode for the TCE0 module.
 * @param[in] state Enable or disable:
 * - @c true - Enables Sleep
 * - @c false - Disables Sleep
 * @return None.
 */
void TCE0_StandBySleep(bool state);

/**
 * @ingroup tce0
 * @brief Enables or disables the Run in Debug mode for the TCE0 module.
 * @param[in] state Enable or disable:
 * - @c true - TCE0 continues running in Break Debug mode when the CPU is halted
 * - @c false - TCE0 is halted in Break Debug mode and ignores events
 * @return None.
 */
void TCE0_DebugRun(bool state);

/**
 * @ingroup tce0
 * @brief Returns the Counter register value for the TCE0.
 * @param None.
 * @return Counter value
 */
uint16_t TCE0_CounterGet(void);

/**
 * @ingroup tce0
 * @brief Sets the Counter register value for the TCE0 module.
 * @param[in] value Counter value
 * @return None.
 */
void TCE0_CounterSet(uint16_t value);

/**
 * @ingroup tce0
 * @brief Sets the clock prescaler for the TCE0 module.
 * @param[in] prescaler Clock prescaler
 * - @c DIV1 - Direct clock source
 * - @c DIV2 - Clock frequency divided by 2
 * - @c DIV4 - Clock frequency divided by 4
 * - @c DIV8 - Clock frequency divided by 8
 * - @c DIV16 - Clock frequency divided by 16
 * - @c DIV64 - Clock frequency divided by 64
 * - @c DIV256 - Clock frequency divided by 256
 * - @c DIV1024 - Clock frequency divided by 1024
 * @return None.
*/
void TCE0_PrescalerSet(TCE_CLKSEL_t prescaler);

/**
 * @ingroup tce0
 * @brief Sets the Compare Channel 0 (CMP0) register value for the TCE0 module.
 * @param[in] value Compare Channel 0 value
 * @return None.
 */
void TCE0_Compare0Set(uint16_t value);

/**
 * @ingroup tce0
 * @brief Sets the Compare Channel 1 (CMP1) register value for the TCE0 module.
 * @param[in] value Compare Channel 1 value
 * @return None.
 */
void TCE0_Compare1Set(uint16_t value);

/**
 * @ingroup tce0
 * @brief Sets the Compare Channel 2 (CMP2) register value for the TCE0 module.
 * @param[in] value Compare Channel 2 value
 * @return None.
 */
void TCE0_Compare2Set(uint16_t value);

/**
 * @ingroup tce0
 * @brief Sets the Compare Channel 3 (CMP3) register value for the TCE0 module.
 * @param[in] value Compare Channel 3 value
 * @return None.
 */
void TCE0_Compare3Set(uint16_t value);

/**
 * @ingroup tce0
 * @brief Sets all the Compare (CMP) registers for the TCE0 module.
 * @param[in] value0 Compare Channel 0 value
 * @param[in] value1 Compare Channel 1 value
 * @param[in] value2 Compare Channel 2 value
 * @param[in] value3 Compare Channel 3 value
 * @return None.
 */
void TCE0_CompareAllChannelsSet(uint16_t value0, uint16_t value1, uint16_t value2, uint16_t value3);

/**
 * @ingroup tce0
 * @brief Sets the Compare Channel 0 (CMP0), Compare Channel 1 (CMP1), and Compare Channel 2 (CMP2) registers for the TCE0 module.
 * @param[in] value0 Compare Channel 0 value
 * @param[in] value1 Compare Channel 1 value
 * @param[in] value2 Compare Channel 2 value
 * @return None.
 */
void TCE0_CompareChannels012Set(uint16_t value0, uint16_t value1, uint16_t value2);

/**
 * @ingroup tce0
 * @brief Sets the Compare Channel 1 (CMP1), Compare Channel 2 (CMP2), and Compare Channel 3 (CMP3) registers for the TCE0 module.
 * @param[in] value1 Compare Channel 1 value
 * @param[in] value2 Compare Channel 2 value
 * @param[in] value3 Compare Channel 3 value
 * @return None.
 */
void TCE0_CompareChannels123Set(uint16_t value1, uint16_t value2, uint16_t value3);

/**
 * @ingroup tce0
 * @brief Sets all the Compare Buffer (CMPBUF) registers for the TCE0 module.
 * @param[in] value0 Compare Buffer Channel 0 value
 * @param[in] value1 Compare Buffer Channel 1 value
 * @param[in] value2 Compare Buffer Channel 2 value
 * @param[in] value3 Compare Buffer Channel 3 value
 * @return None.
 */
void TCE0_CompareAllChannelsBufferedSet(uint16_t value0, uint16_t value1, uint16_t value2, uint16_t value3);

/**
 * @ingroup tce0
 * @brief Sets the Compare Buffer Channel 0 (CMP0BUF), Compare Buffer Channel 1 (CMP1BUF), and Compare Buffer Channel 2 (CMP2BUF) registers for the TCE0 module.
 * @param[in] value0 Compare Buffer Channel 0 value
 * @param[in] value1 Compare Buffer Channel 1 value
 * @param[in] value2 Compare Buffer Channel 2 value
 * @return None.
 */
void TCE0_CompareChannels012BufferedSet(uint16_t value0, uint16_t value1, uint16_t value2);

/**
 * @ingroup tce0
 * @brief Sets the Compare Buffer Channel 1 (CMP1BUF), Compare Buffer Channel 2 (CMP2BUF), and Compare Buffer Channel 3 (CMP3BUF) registers for the TCE0 module.
 * @param[in] value1 Compare Buffer Channel 1 value
 * @param[in] value2 Compare Buffer Channel 2 value
 * @param[in] value3 Compare Buffer Channel 3 value
 * @return None.
 */
void TCE0_CompareChannels123BufferedSet(uint16_t value1, uint16_t value2, uint16_t value3);

/**
 * @ingroup tce0
 * @brief Enable the Waveform Outputs for the TCE0 module.
 * @param[in] value Bitmask value for the channels
 * @return None.
 */
void TCE0_OutputsEnable(uint8_t value);

/**
 * @ingroup tce0
 * @brief Sets the Waveform Outputs for the TCE0 module.
 * @param[in] value Bitmask value for the channels
 * @return None.
 */
void TCE0_OutputsValueSet(uint8_t value);

/**
 * @ingroup tce0
 * @brief Returns the Waveform Outputs value for the TCE0 module.
 * @param None.
 * @return Outputs value:
 * - Bit 0 is set by the the CMP0 output
 * - Bit 1 is set by the the CMP1 output
 * - Bit 2 is set by the the CMP2 output
 * - Bit 3 is set by the the CMP3 output
 */
uint8_t TCE0_OutputsValueGet(void);

/**
 * @ingroup tce0
 * @brief Sets the Waveform Outputs Polarity for the TCE0 module.
 * @param[in] value Bitmask value for the channels
 * @return None.
 */
void TCE0_OutputPolaritySet(uint8_t value);

/**
 * @ingroup tce0
 * @brief Returns the Waveform Outputs Polarity for the TCE0 module.
 * @param None.
 * @return Waveform Outputs Polarity:
 * - Bit 4 determines the polarity of the CMP0 output
 * - Bit 5 determines the polarity of the CMP1 output
 * - Bit 6 determines the polarity of the CMP2 output
 * - Bit 7 determines the polarity of the CMP3 output
 */
uint8_t TCE0_OutputPolarityGet(void);

/**
 * @ingroup tce0
 * @brief Sets the High Resolution mode for the TCE0 module.
 * @param[in] resolution Resolution:
 * - @c TCE_HREN_OFF_gc - High Resolution Disable
 * - @c TCE_HREN_4X_gc - Resolution increased by 4 (two bits)
 * - @c TCE_HREN_8X_gc - Resolution increased by 8 (three bits)
 * @return None.
 */
void TCE0_HighResSet(TCE_HREN_t resolution);

/**
 * @ingroup tce0
 * @brief Sets the Scaling mode used for the TCE0 module.
 * @param[in] mode Scale mode:
 * - @c TCE_SCALEMODE_CENTER_gc - CMPn scaled from CENTER (50% duty cycle)
 * - @c TCE_SCALEMODE_BOTTOM_gc - CMPn scaled from BOTTOM (0% duty cycle)
 * - @c TCE_SCALEMODE_TOP_gc - CMPn scaled from TOP (100% duty cycle)
 * - @c TCE_SCALEMODE_TOPBOTTOM_gc - CMPn scaled from TOP or BOTTOM depending on the CMPn value
 * @return None.
 */
void TCE0_ScaleModeSet(TCE_SCALEMODE_t mode);

/**
 * @ingroup tce0
 * @brief Enables or disables the Scaling for the TCE0 module.
 * @param[in] state Enable or disable:
 * - @c true - Enable Scaling
 * - @c false - Disables Scaling
 * @return None.
 */
void TCE0_ScaleEnable(bool state);

/**
 * @ingroup tce0
 * @brief Enables or disables the Amplitude Control for the TCE0 module.
 * @param[in] state Enable or disable:
 * - @c true - Enable Amplitude Control
 * - @c false - Disable Amplitude Control
 * @return None.
 */
void TCE0_AmplitudeControlEnable(bool state);

/**
 * @ingroup tce0
 * @brief Sets the Amplitude (AMP) register of the TCE0 module.
 * @param[in] value Amplitude value
 * @return None.
 */
void TCE0_AmplitudeSet(uint16_t value);

/**
 * @ingroup tce0
 * @brief Returns the value of the Amplitude (AMP) register of the TCE0 module.
 * @param None.
 * @return Amplitude value
 */
uint16_t TCE0_AmplitudeGet(void);

/**
 * @ingroup tce0
 * @brief Sets the Offset (OFFSET) register for the TCE0 module.
 * @param[in] value Offset value
 * @return None.
 */
void TCE0_OffsetSet(uint16_t value);

/**
 * @ingroup tce0
 * @brief Returns the value of the Offset (OFFSET) register for the TCE0 module.
 * @param None.
 * @return Offset value
 */
uint16_t TCE0_OffsetGet(void);

/**
 * @ingroup tce0
 * @brief Sets the Period (PER) register for the TCE0 module.
 * @param[in] period Period value
 * @return None.
 */
void TCE0_PeriodSet(uint16_t period);

/**
 * @ingroup tce0
 * @brief Returns the value of the Period (PER) register for the TCE0 module.
 * @param None.
 * @return Period value
 */
uint16_t TCE0_PeriodGet(void);

/**
 * @ingroup tce0
 * @brief Sets the counting direction to UP for the TCE0 module.
 * @param None.
 * @return None.
 */
void TCE0_CountDirectionSet(void);

/**
 * @ingroup tce0
 * @brief Sets the counting direction to DOWN for the TCE0 module.
 * @param None.
 * @return None.
 */
void TCE0_CountDirectionClear(void);

/**
 * @ingroup tce0
 * @brief Sets the Lock Update (LUPD) bit for the TCE0 module.
 * @param None.
 * @return None.
 */
void TCE0_LockUpdateSet(void);

/**
 * @ingroup tce0
 * @brief Clears the Lock Update (LUPD) bit for the TCE0 module.
 * @param None.
 * @return None.
 */
void TCE0_LockUpdateClear(void);

/**
 * @ingroup tce0
 * @brief Sets the Auto-Lock Update (ALUPD) bit for the TCE0 module.
 * @param None.
 * @return None.
 */
void TCE0_AutoLockUpdateSet(void);

/**
 * @ingroup tce0
 * @brief Clears the Auto-Lock Update (ALUPD) bit for the TCE0 module.
 * @param None.
 * @return None.
 */
void TCE0_AutoLockUpdateClear(void);

/**
 * @ingroup tce0
 * @brief Sets the Compare Buffer Channel 0 (CMP0BUF) register value in Pulse-Width Modulation (PWM) mode for the TCE0 module.
 * @param[in] value Compare Buffer Channel 0 value
 * @return None.
 *
 */
void TCE0_PWM_BufferedDutyCycle0Set(uint16_t value);

/**
 * @ingroup tce0
 * @brief Sets the Compare Buffer Channel 1 (CMP1BUF) register value in Pulse-Width Modulation (PWM) mode for the TCE0 module.
 * @param[in] value Compare Buffer Channel 1 value
 * @return None.
 */
void TCE0_PWM_BufferedDutyCycle1Set(uint16_t value);

/**
 * @ingroup tce0
 * @brief Sets the Compare Buffer Channel 2 (CMP2BUF) register value in Pulse-Width Modulation (PWM) mode for the TCE0 module.
 * @param[in] value Compare Buffer Channel 2 value
 * @return None.
 */
void TCE0_PWM_BufferedDutyCycle2Set(uint16_t value);

/**
 * @ingroup tce0
 * @brief Sets the Compare Buffer Channel 3 (CMP3BUF) register value in Pulse-Width Modulation (PWM) mode for the TCE0 module.
 * @param[in] value Compare Buffer Channel 3 value
 * @return None.
 */
void TCE0_PWM_BufferedDutyCycle3Set(uint16_t value);

/**
 * @ingroup tce0
 * @brief Sets the Persiod Buffer (PERBUF) register value in Pulse-Width Modulation (PWM) mode for the TCE0 module.
 * @param[in] value Period buffer value
 * @return None.
 */
void TCE0_PeriodBufferSet(uint16_t value);

/**
 * @ingroup tce0
 * @brief Returns the maximum counter value for the TCE0 module.
 * @param None.
 * @return Maximum counter value
 */
uint16_t TCE0_MaxCountGet(void);


#endif // TCE0_H
