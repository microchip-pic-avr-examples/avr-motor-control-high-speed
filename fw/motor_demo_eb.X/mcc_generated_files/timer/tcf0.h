/**
 *  Timer/Counter F Embedded Driver API Header File
 *
 *  @file tcf0.h
 *
 *  @defgroup tcf0 TCF0
 *
 *  @brief This document contains API prototypes and data types for the Timer Counter F module.
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


#ifndef TCF0_H
#define TCF0_H

#include <avr/io.h>

#include <stdbool.h>
#include <stdint.h>


/**
 * @ingroup tcf0
 * @brief
 * Performs the conversion from us(microseconds) to clock cycles.
 * - The first argument is the output period expressed in microseconds
 * - The second argument is the TCF peripheral clock frequency expressed in Hertz
 * - The third argument is the TCF prescaler value as an integer
 * @note Used in Frequency mode to compute the argument for the @c TCF0_CompareSet function.
 */
#define TCF0_F_US_TO_CLOCKS(US, F_CLOCK, TCF_PRESCALER)    (uint32_t)((((float)(F_CLOCK) * (float)(US)) / (2000000.0 * (float)(TCF_PRESCALER)) + 0.5) - 1)

/**
 * @ingroup tcf0
 * @brief
 * Performs the conversion from ms(milliseconds) to clock cycles.
 * - The first argument is the output period expressed in milliseconds
 * - The second argument is the TCF peripheral clock frequency expressed in Hertz
 * - The third argument is the TCF prescaler value as an integer
 * @note Used in Frequency mode to compute the argument for the @c TCF0_CompareSet function.
 */
#define TCF0_F_MS_TO_CLOCKS(MS, F_CLOCK, TCF_PRESCALER)    (uint32_t)((((float)(F_CLOCK) * (float)(MS)) / (2000.0 * (float)(TCF_PRESCALER)) + 0.5) - 1)

/**
 * @ingroup tcf0
 * @brief
 * Performs the conversion from seconds to clock cycles.
 * - The first argument is the output period expressed in seconds
 * - The second argument is the TCF peripheral clock frequency expressed in Hertz
 * - The third argument is the TCF prescaler value as an integer
 * @note Used in Frequency mode to compute the argument for the @c TCF0_CompareSet function.
 */
#define TCF0_F_S_TO_CLOCKS(S, F_CLOCK, TCF_PRESCALER)    (uint32_t)((((float)(F_CLOCK) * (float)(S)) / (2.0 * (float)(TCF_PRESCALER)) + 0.5) - 1)

/**
 * @ingroup tcf0
 * @brief
 * Performs the conversion from Hz to clock cycles.
 * - The first argument is the output frequency expressed in Hertz
 * - The second argument is the TCF peripheral clock frequency expressed in Hertz
 * - The third argument is the TCF prescaler value as an integer
 * @note Used in Frequency mode to compute the argument for the @c TCF0_CompareSet function.
 */
#define TCF0_F_HZ_TO_CLOCKS(HZ, F_CLOCK, TCF_PRESCALER)    (uint32_t)((float)(F_CLOCK) / (2.0 * (HZ) * (TCF_PRESCALER)) - 1)

/**
 * @ingroup tcf0
 * @brief
 * Performs the conversion from Hz to Numeric Controlled Oscillator (NCO) increment.
 * - The first argument is the NCO frequency expressed in Hertz
 * - The second argument is the TCF peripheral clock frequency expressed in Hertz
 * - The third argument is the TCF prescaler value as an integer
 * @note Used in NCO Pulse Length mode to compute the argument for the @c TCF0_CompareSet function.
 */
#define TCF0_NCOPL_HZ_TO_INCREMENT(HZ, F_CLOCK)    (uint32_t)(((float)(HZ) * 16777216.0) / (float)(F_CLOCK) + 0.5)

/**
 * @ingroup tcf0
 * @brief
 * Performs the conversion from Hz to NCO increment.
 * - The first argument is the NCO frequency expressed in Hertz
 * - The second argument is the TCF peripheral clock frequency expressed in Hertz
 * - The third argument is the TCF prescaler value as an integer
 * @note Used in NCO Fixed Duty Cycle mode to compute the argument for the @c TCF0_CompareSet function.
 */
#define TCF0_NCOFD_HZ_TO_INCREMENT(HZ, F_CLOCK, TCF_PRESCALER)    (uint32_t)(((float)(HZ) * 33554432.0 * (TCF_PRESCALER)) / ((float)(F_CLOCK)) + 0.5)

/**
 * @ingroup tcf0
 * @brief
 * Performs the conversion from Hz to clock cycles.
 * - The first argument is the Pulse-Width Modulation (PWM) frequency expressed in Hertz
 * - The second argument is the TCF peripheral clock frequency expressed in Hertz
 * - The third argument is the TCF prescaler value as an integer
 * @note Used in PWM mode to compute the argument for the @c TCF0_PWM_PeriodSet function.
 */
#define TCF0_PWM_PER_HZ_TO_CLOCKS(HZ, F_CLOCK, TCF_PRESCALER)    (uint8_t)((float)(F_CLOCK) / ((float)(TCF_PRESCALER) * (HZ)) - 1)

/**
 * @ingroup tcf0
 * @brief
 * Performs the conversion from ms(microseconds) to clock cycles.
 * - The first argument is the PWM period expressed in microseconds
 * - The second argument is the TCF peripheral clock frequency expressed in Hertz
 * - The third argument is the TCF prescaler value as an integer
 * @note Used in PWM mode to compute the argument for the @c TCF0_PWM_PeriodSet function.
 */
#define TCF0_PWM_PER_US_TO_CLOCKS(US, F_CLOCK, TCF_PRESCALER)    (uint8_t)(((float)(F_CLOCK) * (float)(US)) / (1000000.0 * (float)(TCF_PRESCALER)) + 0.5) - 1

/**
 * @ingroup tcf0
 * @brief
 * Performs the conversion from duty cycle to clock cycles.
 * - The first argument is the duty cycle expressed as a real value between 0.0 and 1.0
 * - The second argument is an integer expressing the period in clock cycles
 * @note Used in PWM mode to compute arguments for the @c TCF0_PWM_DutyCycle0Set and @c TCF0_PWM_DutyCycle1Set functions.
 */
#define TCF0_PWM_DCY_TO_CLOCKS(DCY, PER)    (uint8_t)(float)((DCY) * (PER))


/**
 * @ingroup tcf0
 * @brief Pointer to a function to be used as a callback handler when an overflow or compare interrupt event occurs.
 */
typedef void (* TCF0_cb_t)(void);


/**
 * @ingroup tce0
 * @brief Lists the possible states of the TCF0.
 */
typedef enum
{
    TCF_STATUS_IDLE    = 0, /**< The timer is not running */
    TCF_STATUS_RUNNING = 1, /**< The timer is running */
}
TCF0_status_t;


/**
 * @ingroup tcf0
 * @brief Setter function for TCF0 overflow callback.
 * @pre None.
 * @param callback Pointer to custom callback function.
 * @return None.
 */
void TCF0_OverflowCallbackRegister(TCF0_cb_t callback);


/**
 * @ingroup tcf0
 * @brief Initializes the TCF0 module and is the first routine called.
 * @pre None.
 * @param None.
 * @return None.
 */
void TCF0_Initialize(void);


/**
 * @ingroup tcf0
 * @brief Resets the TCF0 module to the Default state.
 * @pre None.
 * @param None.
 * @return None.
 */
void TCF0_Deinitialize(void);


/**
 * @ingroup tcf0
 * @brief Returns the status of the TCF0 module.
 * @pre None.
 * @param None.
 * @return TCF_status_t
 * @retval TCF_STATUS_IDLE The timer is not running
 * @retval TCF_STATUS_RUNNING The timer is running
 */
TCF0_status_t TCF0_StatusGet(void);


/**
 * @ingroup tcf0
 * @brief Starts TCF0.
 * @pre TCF0_Initialize() is already called.
 * @param None.
 * @return None.
 */
void TCF0_Start(void);


/**
 * @ingroup tcf0
 * @brief Stops TCF0.
 * @pre TCF0_Initialize() is already called.
 * @param None.
 * @return None.
 */
void TCF0_Stop(void);


/**
 * @ingroup tcf0
 * @brief Selects the prescaler for TCF0.
 * @pre None.
 * @param TCF_PRESC_t
 * - @c TCF_PRESC_DIV1_gc - Direct clock source
 * - @c TCF_PRESC_DIV2_gc - Clock divided by 2
 * - @c TCF_PRESC_DIV4_gc - Clock divided by 4
 * - @c TCF_PRESC_DIV8_gc - Clock divided by 8
 * - @c TCF_PRESC_DIV16_gc - Clock divided by 16
 * - @c TCF_PRESC_DIV32_gc - Clock divided by 32
 * - @c TCF_PRESC_DIV64_gc - Clock divided by 64
 * - @c TCF_PRESC_DIV128_gc - Clock divided by 128
 * @return None.
 */
void TCF0_PrescalerSet(TCF_PRESC_t config);


/**
 * @ingroup tcf0
 * @brief Enables or disables the Run-in-Standby mode for TCF0.
 * @pre TCF0_Initialize() is already called.
 * @param state
 * - @c True - Enables Sleep.
 * - @c False - Disables Sleep.
 * @return None.
 */
void TCF0_StandBySleep(bool state);


/**
 * @ingroup tcf0
 * @brief Sets the Waveform Generation mode for TCF0.
 * @pre None.
 * @param mode
 * - @c TCF_WGMODE_FRQ_gc - Frequency
 * - @c TCF_WGMODE_NCOPF_gc - NCO Pulse-Frequency
 * - @c TCF_WGMODE_NCOFDC_gc - NCO Fixed Duty Cycle
 * - @c TCF_WGMODE_PWM8_gc - 8-bit PWM
 * @return None.
 */
void TCF0_ModeSet(TCF_WGMODE_t mode);


/**
 * @ingroup tcf0
 * @brief Sets the clock source for TCF0.
 * @pre None.
 * @param config
 * - @c TCF_CLKSEL_CLKPER_gc - Peripheral Clock
 * - @c TCF_CLKSEL_EVENT_gc - Event as clock source
 * - @c TCF_CLKSEL_OSCHF_gc - Internal High Frequency Oscillator
 * - @c TCF_CLKSEL_OSC32K_gc - Internal 32.768 kHz Oscillator
 * - @c TCF_CLKSEL_PLL_gc - Phase-Locked Loop
 * - @c TCF_CLKSEL_OSCBOOT_gc - Boot Oscillator
 * @return None.
 */
void TCF0_ClockSet(TCF_CLKSEL_t config);


/**
 * @ingroup tcf0
 * @brief Controls the Event Output mode for TCF0.
 * @pre TCF0_Initialize() is already called.
 * @param value
 * Where only bits 6-7 are used:
 * - Bit 6 represents event output 0
 * - Bit 7 represents event output 1
 * @return None.
 */
void TCF0_Event_OutputMode(uint8_t value);


/**
 * @ingroup tcf0
 * @brief Controls the Waveform outputs for TCF0.
 * @pre None.
 * @param value
 * Where only bits 0-3 are used:
 * - Bit 0 enables channel 0
 * - Bit 1 enables channel 1
 * - Bit 2 reverses the polarity on channel 0
 * - Bit 3 reverses the polarity on channel 1
 * @return None.
 */
void TCF0_OutputsSet(uint8_t value);


/**
 * @ingroup tcf0
 * @brief Issues the software commands of Update, Restart or Reset over the TCF0.
 * @pre TCF0_Initialize() is already called.
 * @param command
 * - @c TCF_CMD_NONE_gc - No command
 * - @c TCF_CMD_UPDATE_gc - Force update
 * - @c TCF_CMD_RESTART_gc - Force restart
 * @return None.
 */
void TCF0_SoftwareCommand(TCF_CMD_t command);


/**
 * @ingroup tcf0
 * @brief Configures the input event for TCF0.
 * @pre TCF0_Initialize() is already called.
 * @param config
 * Where only bits 0-3 are used:
 * - Bit 0 enables the event input
 * - Bits 1 and 2 select the action event (0 for Restart, 1 for Blank)
 * - Bit 3 enables the filter
 * @return None.
 */
void TCF0_Event_InputConfig(uint8_t config);


/**
 * @ingroup tcf0
 * @brief Enables the TCF0 Overflow, CMP0 or CMP1 interrupts.
 * @pre TCF0_Initialize() is already called.
 * @param mask
 * Where only bits 0-2 are used:
 * - Bit 0 enables the OVF interrupt
 * - Bit 1 enables the CMP0 interrupt
 * - Bit 2 enables the CMP1 interrupt
 * @return None.
 */
void TCF0_Interrupts_Enable(uint8_t mask);


/**
 * @ingroup tcf0
 * @brief Disables the TCF0 Overflow, CMP0 or CMP1 interrupts.
 * @pre TCF0_Initialize() is already called.
 * @param mask
 * Where only bits 0-2 are used:
 * - Bit 0 disables the OVF interrupt
 * - Bit 1 disables the CMP0 interrupt
 * - Bit 2 disables the CMP1 interrupt
 * @return None.
 */
void TCF0_Interrupts_Disable(uint8_t mask);


/**
 * @ingroup tcf0
 * @brief Retrieves the interrupt flags.
 * @pre TCF0_Initialize() is already called.
 * @param None.
 * @return uint8_t From the returned 8-bit word, only bits TCF_OVF_bm, TCF_CMP0_bm and TCF_CMP1_bm are used.
 */
uint8_t TCF0_Interrupts_FlagsGet(void);


/**
 * @ingroup tcf0
 * @brief Clears the interrupt flags.
 * @pre TCF0_Initialize() is already called.
 * @param mask
 * Where only bits 0-2 are used:
 * - Bit 0 clears the OVF flag
 * - Bit 1 clears the CMP0 flag
 * - Bit 2 clears the the CMP1 flag
 * @return None.
 */
void TCF0_Interrupts_FlagsClear(uint8_t mask);


/**
 * @ingroup tcf0
 * @brief Gets the CNT register value.
 * @pre TCF0_Initialize() is already called.
 * @param None.
 * @return uint32_t 24-bit Counter value.
 */
uint32_t TCF0_CounterGet(void);


/**
 * @ingroup tcf0
 * @brief Sets the CNT register value.
 * @pre None.
 * @param uint32_t 24-bit Counter value.
 * @return None.
 */
void TCF0_CounterSet(uint32_t value);


/**
 * @ingroup tcf0
 * @brief Sets the CMP register value for TCF0.
 * @pre None.
 * @param uint32_t 24-bit Compare value.
 * @return None.
 */
void TCF0_CompareSet(uint32_t value);


/**
 * @ingroup tcf0
 * @brief Sets the pulse length of the generated waveform for TCF0.
 * @pre None.
 * @param config
 * - @c TCF_WGPULSE_CLK1_gc - High pulse is 1 clock period
 * - @c TCF_WGPULSE_CLK2_gc - High pulse is 2 clock periods
 * - @c TCF_WGPULSE_CLK4_gc - High pulse is 4 clock periods
 * - @c TCF_WGPULSE_CLK8_gc - High pulse is 8 clock periods
 * - @c TCF_WGPULSE_CLK16_gc - High pulse is 16 clock periods
 * - @c TCF_WGPULSE_CLK32_gc - High pulse is 32 clock periods
 * - @c TCF_WGPULSE_CLK64_gc - High pulse is 64 clock periods
 * - @c TCF_WGPULSE_CLK128_gc - High pulse is 128 clock periods
 * @return None.
 */
void TCF0_NCO_PulseLengthSet(TCF_WGPULSE_t config);


/**
 * @ingroup tcf0
 * @brief Sets the CMP0 register value for TCF0.
 * @pre None.
 * @param value Duty Cycle.
 * @return None.
 */
void TCF0_PWM_DutyCycle0Set(uint8_t value);


/**
 * @ingroup tcf0
 * @brief Sets the CMP1 register value for TCF0.
 * @pre None.
 * @param value Duty Cycle.
 * @return None.
 */
void TCF0_PWM_DutyCycle1Set(uint8_t value);


/**
 * @ingroup tcf0
 * @brief Sets the CNT1 register value for TCF0 in PWM mode.
 * @pre None.
 * @param value Period.
 * @return None.
 */
void TCF0_PWM_PeriodSet(uint8_t value);

#endif /* TCF0_H */
