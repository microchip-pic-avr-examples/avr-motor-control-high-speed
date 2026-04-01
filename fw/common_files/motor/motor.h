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
    MOTOR_EVENT_UV       = (1 << 4),
    MOTOR_EVENT_OC       = (1 << 5),
} motor_status_t;

#define MOTOR_ERROR_FLAGS (MOTOR_EVENT_OC | MOTOR_EVENT_OV | MOTOR_EVENT_FAULT | MOTOR_EVENT_STALL | MOTOR_EVENT_UV)

typedef enum
{
    MOTOR_NO_FAULT = 0,
    MOTOR_FAULT_OVERCURRENT,
    MOTOR_FAULT_OVERVOLTAGE,
} motor_fault_t;

typedef enum
{
    DIR_CW = 0,
    DIR_CCW,
} motor_dir_t;

/*************************************/
/***** public function prototypes ****/
/*************************************/

void           Motor_Initialize(void);
void           Motor_Start(uint16_t vbus_adc, motor_dir_t dir);
void           Motor_Stop(void);
void           Motor_Fault(motor_fault_t);
void           Motor_CommandSet(uint16_t ref);
uint16_t       Motor_MaxAmpGet(void);
motor_status_t Motor_StatusGet(void);
uint32_t       Motor_ErpmGet(void);
uint16_t       Motor_AmplitudeGet(void);
void           Motor_TimeTick(void);  /* this function has to be called once every 1 ms, on interrupt context */

#endif /* MOTOR_H */
