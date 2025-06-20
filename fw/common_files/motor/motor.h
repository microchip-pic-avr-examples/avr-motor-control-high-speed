#ifndef MOTOR_H
#define MOTOR_H


#include <stdint.h>

/* public data types */

typedef enum
{
    MOTOR_IDLE           = 0 ,
    MOTOR_RUNNING        = (1 << 0),
    MOTOR_EVENT_STALL    = (1 << 1),
    MOTOR_EVENT_FAULT    = (1 << 2),
    MOTOR_EVENT_OV       = (1 << 3),
    MOTOR_EVENT_OC       = (1 << 4),
} motor_status_t;

#define MOTOR_ERROR_FLAGS (MOTOR_EVENT_OC | MOTOR_EVENT_OV | MOTOR_EVENT_FAULT | MOTOR_EVENT_STALL)

typedef enum
{
    MOTOR_NO_FAULT = 0,
    MOTOR_FAULT_OVERCURRENT,
    MOTOR_FAULT_OVERVOLTAGE,
} motor_fault_t;

/*************************************/
/***** public function prototypes ****/
/*************************************/

void           Motor_Initialize(void);
void           Motor_Start(uint16_t vbus_adc);
void           Motor_Stop(void);
void           Motor_Fault(motor_fault_t);
void           Motor_AmplitudeSet(uint16_t amp);
uint16_t       Motor_MaxAmpGet(void);
motor_status_t Motor_StatusGet(void);
uint16_t       Motor_ErpmGet(void);
uint16_t       Motor_AmplitudeGet(void);
void           Motor_TimeTick(void);  /* this function has to be called once every 1 ms, on interrupt context */

#endif /* MOTOR_H */
