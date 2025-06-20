#ifndef  LOGGER_H
#define  LOGGER_H

#include <stdint.h>
#include <stdbool.h>



typedef enum
{
    _8_SIGNED,
    _8_UNSIGNED,
    _8_HEX,
    _16_SIGNED,
    _16_UNSIGNED,
    _16_HEX,
} log_format_t;



bool Log_Decimate(uint8_t, uint8_t *);
void Log_Start(bool);
void Log_Stop(void);
void Log_Add8 (uint8_t);
void Log_Add16(uint16_t);
void Log_Show(const char *title, uint8_t sample_size, log_format_t format);

#endif /* LOGGER_H */

