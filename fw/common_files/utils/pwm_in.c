#include <util/atomic.h>
#include "pwm_in.h"
#include "mcc_mapping.h"

#define PWM_IN_TIMEOUT        5

static volatile uint8_t  ovfcnt;
static uint32_t period;
static uint32_t duty;


/* private functions */
static void _PWM_Input_Tmr_Handler(void)
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

static void _PWM_Input_Pin_Handler(void)
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



/* PWM_Input API */
void     PWM_Input_Initialize(void)
{
    ovfcnt = 0;
    period = 0;
    duty = 0;
    PWM_IN_PIN_REGISTER(_PWM_Input_Pin_Handler);
    PWM_IN_TMR_REGISTER(_PWM_Input_Tmr_Handler);
}

uint16_t PWM_Input_PeriodGet(void)
{
    return (uint16_t)(period >> 2);
}

uint16_t PWM_Input_DutyGet(void)
{
    return (uint16_t)(duty >> 2);
}

