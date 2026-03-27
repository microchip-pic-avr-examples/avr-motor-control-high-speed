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

#include <string.h>              /* for memset() */
#include "conversion_macros.h"
#include "mcc_mapping.h"
#include "analog.h"
#include "config.h"


typedef struct
{
    analog_fault_handler_t handler;
    uint16_t               threshold;
    uint8_t                event;
} analog_emergency_t;


/** private data */
static uint8_t  index,  sequencer_idx;
static analog_emergency_t emergency[ID_MAX];
static split24_t analog_results[ID_MAX];
static uint8_t  pins_list[ID_MAX];
static const analog_id_t  analog_sequencer[] = 
{
    ID_CRT, ID_VBUS, ID_CRT, ID_VBUS,
    ID_CRT, ID_VBUS, ID_CRT, ID_POT, ID_CRT, ID_REF
};
#define ANALOG_SEQUENCER_MAX  (sizeof(analog_sequencer)/sizeof(analog_id_t))

static inline void             AdataClear(analog_id_t id)                       {analog_results[id].W24 = 0;}
static inline void             AdataInit(analog_id_t id, adc_result_t value)    {analog_results[id].H16 = value; analog_results[id].L8 = 0;}
static inline uint16_t         AdataRead (analog_id_t id)                       {return analog_results[id].H16;}
static inline void             AdataFilterWrite(analog_id_t id, adc_result_t data) {uint24_t x = analog_results[id].W24; uint24_t y = x >> 4; analog_results[id].W24 = x - y + ((uint24_t)data << 4);}
static inline void             AdataSimpleWrite(analog_id_t id, adc_result_t data) {analog_results[id].H16 = data;}


void Analog_Handler(void)
{
    static uint8_t next_mux = VBUS_ADC_PIN, p_index = 0, pp_index = 0;
    if(ADC_NO_CONV_PROGRESS())
    {
        uint16_t adc = ADC_RESULT_GET();
        ADC_MUX_SET(next_mux);
        ADC_CONV_START();

        pp_index = p_index;
        p_index = index;
        sequencer_idx++; if(sequencer_idx == ANALOG_SEQUENCER_MAX) sequencer_idx = 0;
        index = analog_sequencer[sequencer_idx];
        next_mux = pins_list[index];

        if(ADC_IIR_FILTER == true)
            AdataFilterWrite(pp_index, adc);
        else
            AdataSimpleWrite(pp_index, adc);
        adc = AdataRead(pp_index);

        if(emergency[pp_index].handler != NULL)
        {
            if(adc > emergency[pp_index].threshold)
                emergency[pp_index].handler(emergency[pp_index].event);
        } 
    }
}

/********************************/
/******* public functions *******/
/********************************/

void Analog_Initialize(void)
{
    memset(analog_results, 0, sizeof(analog_results));
    memset(emergency, 0, sizeof(emergency));
    pins_list[ID_CRT]  = CRT_P_ADC_PIN;
    pins_list[ID_REF]  = CRT_N_ADC_PIN;
    pins_list[ID_VBUS] = VBUS_ADC_PIN;
    pins_list[ID_POT]  = POT_ADC_PIN;
    index = analog_sequencer[0];
    sequencer_idx = 0;
    ADC_MUX_SET(pins_list[index]);
}

uint16_t Analog_Max(void)
{
    return (1UL << ADC_RESOLUTION_GET()) - 1UL;
}

uint16_t Analog_Get(analog_id_t id)
{
	uint16_t retval;
    ATOMIC_COPY(retval, AdataRead(id));
    return retval;
}

void     Analog_EmergencyStop_Register(analog_id_t id, analog_fault_handler_t handler, uint16_t threshold, uint8_t event)
{
    ATOMIC_COPY(emergency[id].event,     event);
    ATOMIC_COPY(emergency[id].threshold, threshold);
    ATOMIC_COPY(emergency[id].handler,   handler);
}

