#ifndef SW_TIMER_H
#define SW_TIMER_H

#include <stdint.h>
#include <stdbool.h>

/* max number 64 */
#define SW_TIMER_INTR_MAX_NO 1
#define SW_TIMER_MAIN_MAX_NO 2

typedef void (*swtimer_cb_t)(void);

typedef struct
{
    uint16_t       time_limit;
    uint16_t       time;
    swtimer_cb_t   pf;
    bool           state;
} swtimer_data_t;

typedef uint8_t swtimer_id_t;


void         SwTimer_Tick(void);  /* called every 1ms on interrupt context */
swtimer_id_t SwTimer_IntrAdd(swtimer_data_t *pData, uint16_t ms, swtimer_cb_t cb);
swtimer_id_t SwTimer_MainAdd(swtimer_data_t *pData, uint16_t ms, swtimer_cb_t cb);
void         SwTimer_Start(swtimer_id_t id);
void         SwTimer_Stop(swtimer_id_t id);
void         SwTimer_Delay(uint32_t ms);

#endif /*  SW_TIMER_H */

