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

