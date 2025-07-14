#ifndef PWM_IN_H
#define PWM_IN_H

#include <stdint.h>

/* PWM_Input API */
void     PWM_Input_Initialize(void);
uint16_t PWM_Input_PeriodGet(void);
uint16_t PWM_Input_DutyGet(void);


#endif /* PWM_IN_H */
