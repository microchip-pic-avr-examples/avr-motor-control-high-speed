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

#include <util/atomic.h>
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "dbg_logger.h"
#include "conversion_macros.h"

static uint8_t   log_buff[DEBUG_BUFF_SIZE];
static uint16_t  log_index;
static bool      log_enabled = false, log_overflow = false;
static log_buf_t log_loop;

static void _Debug_PrintRow(uint16_t index, uint16_t id, uint8_t sample_size, log_format_t format)
{
    uint16_t  data;
    uint8_t   i;
    int8_t    t8;

    printf("%u\t", id);
    for(i = 0; i < sample_size; i++)
    {
        if(format < _16_SIGNED)
        {
            void   *ptr = (void*)(log_buff + sample_size * index + i);
            data = *(uint8_t*)ptr;
        }
        else
        {
            void   *ptr = (void*)(log_buff + 2 * (sample_size * index + i));
            data = *(uint16_t*)ptr;
        }
        switch(format)
        {
            case _8_SIGNED:     t8 = (int8_t)data; printf("%03d\t", t8); break;
            case _8_UNSIGNED:   printf("%03u\t", data); break;
            case _8_HEX:        printf("%02X\t", data); break;
            case _16_SIGNED:    printf("%05d\t", data); break;
            case _16_UNSIGNED:  printf("%05u\t", data); break;
            case _16_HEX:       printf("%04X\t", data); break;
        }
    }
    printf("\n\r");
}


bool Log_Decimate(uint8_t level, uint8_t *pCounter)
{
    (*pCounter)++;
    if(*pCounter == level)
    {
        *pCounter = 0;
        return true;
    }
    else
        return false;
}

void Log_Start(log_buf_t loop)
{
    memset((void*)log_buff, 0, sizeof(log_buff));
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        log_index = 0;
        log_loop = loop;
        log_enabled = true;
        log_overflow = false;
    }
}

void Log_Stop(void)
{
    log_enabled = false;
}

void Log_Add8(uint8_t data)
{
    if(log_enabled == false) return;
    if(log_index < DEBUG_BUFF_SIZE)
    {
        log_buff[log_index] = data;
        log_index++;
    }
    else if(log_loop == LOG_LOOP)
    {
        log_index = 0;
        log_buff[log_index] = data;
        log_index++;
        log_overflow = true;
    }
}

void Log_Add16(uint16_t data)
{
    split16_t split_data;
    split_data.W16 = data;
    if(log_enabled == false) return;
    if((log_index + 1) < DEBUG_BUFF_SIZE)
    {
        log_buff[log_index++] = split_data.L8;
        log_buff[log_index++] = split_data.H8;
    }
    else if(log_loop == LOG_LOOP)
    {
        log_index = 0;
        log_buff[log_index++] = split_data.L8;
        log_buff[log_index++] = split_data.H8;
        log_overflow = true;
    }
}


void Log_Show(const char *title, uint8_t sample_size, log_format_t format)
{
    uint16_t i, j = 0, m, n;

    if(format < _16_SIGNED)
    {
        m = log_index       / sample_size;
        n = DEBUG_BUFF_SIZE / sample_size;
    }
    else
    {
        m = log_index       / (sample_size * 2);
        n = DEBUG_BUFF_SIZE / (sample_size * 2);
    }
    
    if((log_loop == LOG_LOOP) && (log_overflow == true))
    {
        printf("\n\rEnd of buffer:\n\r%s\n\r", title);
        for(i = m; i < n; i++)
            _Debug_PrintRow(i, j++, sample_size, format);
    }
    else
    {
        printf("\n\rStart of buffer:\n\r%s\n\r", title);
    }
    for(i = 0; i < m; i++)
    {
        _Debug_PrintRow(i, j++, sample_size, format);
    }
}

