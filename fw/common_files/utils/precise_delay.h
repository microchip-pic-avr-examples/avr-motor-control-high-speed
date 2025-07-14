#ifndef PRECISE_DELAY_H
#define PRECISE_DELAY_H

#include "sw_timer.h"

#define PRECISE_DELAY_MS(X)    SwTimer_Delay((uint32_t)((X) * 1000.0 / SW_TIMER_PERIOD + 0.5))
        

#endif /* PRECISE_DELAY_H */
