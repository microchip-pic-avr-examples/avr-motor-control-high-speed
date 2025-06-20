/*
© [2024] Microchip Technology Inc. and its subsidiaries.
 
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

#include <stdint.h>
#include <stdbool.h>

#include "button_led.h"
#include "mcc_mapping.h"


/* this is called every BUTTON_TIME_STEP ms */
button_state_t ButtonGet(void)
{
    button_state_t retVal = BUTTON_IDLE;
    static uint8_t db_counter = 0;
    static uint16_t len_counter = 0;
    static bool debounced_state = false;
    static bool long_detected = false;

    bool actual_state = (BUTTON_GetValue() == BUTTON_ACTIVE)?  true : false; /* true=pressed , false=notpressed */
    
    if(debounced_state == true)
    {
        len_counter++;
        if(len_counter == (BUTTON_TIME_LONG/BUTTON_LED_TIME_STEP))
        {
            retVal = BUTTON_LONG_PRESS;
            long_detected = true;
        }
    }

    if(actual_state != debounced_state)
    {
        db_counter++;
        if(db_counter == (BUTTON_DEBOUNCE_TIME/BUTTON_LED_TIME_STEP))
        {
            debounced_state = actual_state;
            len_counter = 0;
            if(debounced_state == false) /* button release */
            {
                if(long_detected == false)
                    retVal = BUTTON_SHORT_PRESS;
                long_detected = false;
            }
        }
    }
    else
        db_counter = 0;
    return retVal;
}

/* pass LED_ON, LED_OFF or LED_BLINK */
void LedControl(led_ctrl_t state)
{
    static uint16_t counter;
    static uint8_t  blinks_counter;
    static bool     blinking_flag = false;

    /* starts blinking */
    if((state == LED_BLINK)  && (blinking_flag == false))
    {
        blinking_flag = true;
        blinks_counter = 2 * LED_BLINKS_NUMBER;
        counter = 0;
    }

    if(blinking_flag == true)
    {
        counter++;
        if(counter == (LED_BLINK_DURATION/BUTTON_LED_TIME_STEP))
        {
            counter = 0;
            if(blinks_counter > 1)
                LED_Toggle();
            blinks_counter--;
            if(blinks_counter == 0)
                blinking_flag = false;
        }
    }
    else
    {
        if(state == LED_ON)    LED_SetLow();
        if(state == LED_OFF)   LED_SetHigh();
    }
}
