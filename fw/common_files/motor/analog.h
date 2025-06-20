
#ifndef ANALOG_H
#define ANALOG_H

#include <stdint.h>


typedef enum
{
	ID_POT = 0,
	ID_VBUS,
	ID_CRT,
    ID_MAX,
} analog_id_t;

typedef void (*analog_fault_handler_t)(uint8_t);

typedef void (*analog_adapt_pwm_handler_t)(uint16_t);

void     Analog_Initialize(void);
uint16_t Analog_MaxGet(void);
uint16_t Analog_Get(analog_id_t id);
void     Analog_EmergencyStop_Register(analog_id_t id, analog_fault_handler_t handler, uint16_t threshold, uint8_t event);

#endif /* ANALOG_H */

