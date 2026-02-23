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

#include <stddef.h>  /* for NULL definition */
#include "sw_timer.h"

static swtimer_data_t  *intr_array[SW_TIMER_INTR_MAX_NO] = {NULL};
static swtimer_data_t  *main_array[SW_TIMER_MAIN_MAX_NO] = {NULL};
static swtimer_id_t     intr_count = 0;
static swtimer_id_t     main_count = 0;
static volatile uint8_t ticks_count = 0;


swtimer_id_t SwTimer_IntrAdd(swtimer_data_t *pData, uint16_t ms, swtimer_cb_t cb)
{
    if(intr_count >= SW_TIMER_INTR_MAX_NO)
        return -1;
    if(pData == NULL)
        return -1;
    
    intr_array[intr_count] = pData;
    pData -> time = 0;
    pData -> time_limit = ms;
    pData -> pf = cb;
    pData -> state = false;

    intr_count++;
    return (intr_count - 1) & 127;
}

swtimer_id_t SwTimer_MainAdd(swtimer_data_t *pData, uint16_t ms, swtimer_cb_t cb)
{
    if(main_count >= SW_TIMER_MAIN_MAX_NO)
        return -1;
    if(pData == NULL)
        return -1;
    
    main_array[main_count] = pData;
    pData -> time = 0;
    pData -> time_limit = ms;
    pData -> pf = cb;
    pData -> state = false;

    main_count++;
    return (main_count - 1) | 128;
}


void         SwTimer_Start(swtimer_id_t id)
{
    if(id == -1)
        return;
    if(id & 128)  /* main type */
    {
        id &= 127;
        if(id >= main_count)
            return;
        swtimer_data_t *pData = main_array[id];
        pData -> state = true;
    }
    else         /* intr type */
    {
        if(id >= intr_count)
            return;
        swtimer_data_t *pData = intr_array[id];
        pData -> state = true;
    }
}


void         SwTimer_Stop(swtimer_id_t id)
{
    if(id == -1)
        return;
    if(id & 128)  /* main type */
    {
        id &= 127;
        if(id >= main_count)
            return;
        swtimer_data_t *pData = main_array[id];
        pData -> state = false;
    }
    else         /* intr type */
    {
        if(id >= intr_count)
            return;
        swtimer_data_t *pData = intr_array[id];
        pData -> state = false;
    }
}

/* called every 1ms on interrupt context */
void SwTimer_Tick(void)
{
    ticks_count++;
    
    uint8_t i;
    for(i = 0; i < intr_count; i++)
    {
        swtimer_data_t *pData = intr_array[i];
        if(pData->state)
        {
            pData->time++;
            if(pData->time == pData->time_limit)
            {
                pData->time = 0;
                swtimer_cb_t pf = pData->pf;
                if(pf != NULL)
                    pf();
            }
        }
    }
}


void         SwTimer_Delay(uint32_t ticks)
{
    while(ticks)
    {
        uint8_t ticks_local;
        while(ticks_count == 0);

        ticks_local = ticks_count;
        ticks_count = 0;

        if(ticks > ticks_local)
            ticks -= ticks_local;
        else
            ticks = 0;
        
        uint8_t i;
        for(i = 0; i < main_count; i++)
        {
            swtimer_data_t *pData = main_array[i];
            if(pData->state)
            {
                pData->time+= ticks_local;
                if(pData->time >= pData->time_limit)
                {
                    pData->time = 0;
                    swtimer_cb_t pf = pData->pf;
                    if(pf != NULL)
                        pf();
                }
            }
        }
    }
}

