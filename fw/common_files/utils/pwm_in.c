/*
© [2026] Microchip Technology Inc. and its subsidiaries.
 
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

#include "config.h"
#include "pwm_in.h"
#include "conversion_macros.h"
#include "mcc_mapping.h"

#define PWM_IN_TIMEOUT        5

static volatile uint8_t  ovfcnt;
static uint32_t period;
static uint32_t duty;
static uint16_t min, max;



/* private functions */
static void _Tmr_Handler(void)
{
    ovfcnt++;
    if(ovfcnt > PWM_IN_TIMEOUT)
    {
        PWM_IN_TMR_CLEAR();
        ovfcnt = 0;
        period = 0;
        duty = 0;
    }
}

static void _Pin_Handler(void)
{
    uint16_t tmp16 = PWM_IN_TMR_READ();
    uint8_t tmp8 = ovfcnt;
    if(PWM_IN_PIN_READ())
    {
        PWM_IN_TMR_CLEAR();
        ovfcnt = 0;
        period = ((uint32_t)tmp8 << 16) | (uint32_t)tmp16;
    }
    else
    {
        duty = ((uint32_t)tmp8 << 16) | (uint32_t)tmp16;
    }
}

static inline uint16_t _PeriodGet(void)
{
    return (uint16_t)(period >> 2);
}

static inline uint16_t _DutyGet(void)
{
    return (uint16_t)(duty >> 2);
}



/* PWM Input API */
void IPWM_Initialize(void)
{
    min = 0;
    max = 0;
    ovfcnt = 0;
    period = 0;
    duty = 0;
    PWM_IN_PIN_REGISTER(_Pin_Handler);
    PWM_IN_TMR_REGISTER(_Tmr_Handler);
}

uint16_t IPWM_Min(void)
{
    return min;
}

uint16_t IPWM_Max(void)
{
    return max;
}

uint16_t IPWM_Read(void)
{
    uint16_t dcy;
    uint16_t per = _PeriodGet();
    if(per != 0)
    {
        dcy = _DutyGet();
        min = (PWM_IN_MIN_DCY * per / PWM_IN_PERIOD);
        max = (PWM_IN_MAX_DCY * per / PWM_IN_PERIOD);
        dcy = SATURATE(dcy, min, max);
    }
    else
    {
        dcy = 0;
        min = 0;
        max = 0;
    }
    return dcy;
}

