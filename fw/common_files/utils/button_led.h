/*
� [2024] Microchip Technology Inc. and its subsidiaries.
 
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

#ifndef BUTTON_LED_H
#define BUTTON_LED_H

#define BUTTON_LED_TIME_STEP   (1)     /* milliseconds */
#define BUTTON_DEBOUNCE_TIME   (20)    /* milliseconds */
#define BUTTON_TIME_LONG       (1500)  /* 1.5 s long press timeout */
#define LED_BLINK_DURATION     (200)   /* 0.2 s LED blink duration */
#define LED_BLINKS_NUMBER      (5)     /* number of LED blinks     */

typedef enum
{
    BUTTON_IDLE,
    BUTTON_SHORT_PRESS,
    BUTTON_LONG_PRESS
} button_state_t;

typedef enum
{
    LED_ON,
    LED_OFF,
    LED_BLINK
} led_ctrl_t;


/* this has to be called approximately every 'BUTTON_TIME_STEP' ms */
button_state_t ButtonGet(void);

/* LED on, LED off or LED blink */
void LedControl(led_ctrl_t);

#endif /* BUTTON_LED_H */
