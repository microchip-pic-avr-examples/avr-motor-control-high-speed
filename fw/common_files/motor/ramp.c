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

#include "ramp.h"

#define NEGATIVE    true
#define POSITIVE    false

void Ramp_Init(uint16_t begin, uint16_t end, uint16_t steps, ramp_t* pData)
{
    if(pData == NULL) return;
    if(steps < 2)
    {
        pData->end_value = end;
        pData->accumulator.H16 = end;
        pData->accumulator.L16 = 0;
        pData->step_counter = 0;
        pData->step_size = 0;
        pData->step_sign = POSITIVE;
        pData->is_done = true;
        return;
    }

    if(begin < end)
    {
        pData->step_sign = POSITIVE;
        pData->step_size = end - begin;
    }
    else
    {
        pData->step_sign = NEGATIVE;
        pData->step_size = begin - end;
    }
    
    pData->step_counter = steps;
    steps--; 
    pData->step_size = ((pData->step_size)<<16)/steps;  
    pData->end_value = end;    
    pData->accumulator.H16 = begin;
    pData->accumulator.L16 = 0;    
    pData->is_done = false;
}

uint16_t Ramp_Get(ramp_t* pData)
{
    uint16_t ret_val;
    if(pData == NULL) return 0;
    if(pData->step_counter == 0)
    {
        pData->is_done = true;
        return (pData->accumulator.H16);
    }    
    
    ret_val = pData->accumulator.H16;
             
    pData->step_counter--;
    if(pData->step_counter == 0)
    {
        pData->accumulator.H16 = pData->end_value;
        pData->accumulator.L16 = 0;
        pData->is_done = true;
        ret_val = pData->accumulator.H16;
    }
    else
    {
        if(pData->step_sign == POSITIVE)
            pData->accumulator.W32 +=  pData->step_size;        
        else // pData->u16.step_sign == NEGATIVE
            pData->accumulator.W32 -=  pData->step_size;               
    }
    
    return ret_val;
}

