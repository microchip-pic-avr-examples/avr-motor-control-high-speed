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
static analog_id_t  analog_sequencer[] = 
{
    ID_CRT, ID_VBUS, ID_CRT, ID_VBUS,
    ID_CRT, ID_VBUS, ID_CRT, ID_POT
};
#define ANALOG_SEQUENCER_MAX  (sizeof(analog_sequencer)/sizeof(analog_id_t))

static inline void             AdataClear(analog_id_t id)                       {analog_results[id].W = 0;}
static inline void             AdataInit(analog_id_t id, adc_result_t value)    {analog_results[id].H = value; analog_results[id].L = 0;}
static inline uint16_t         AdataRead (analog_id_t id)                       {return analog_results[id].H;}
static inline void             AdataFilterWrite(analog_id_t id, adc_result_t data) {split24_t x = analog_results[id]; uint32_t y = x.W;  uint16_t z = x.H; analog_results[id].W = y - z + (uint16_t)data;}
static inline void             AdataSimpleWrite(analog_id_t id, adc_result_t data) {analog_results[id].H = data;}


static void _Analog_Handler(void)
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
    pins_list[ID_VBUS] = VBUS_ADC_PIN;
    pins_list[ID_POT]  = POT_ADC_PIN;
    index = analog_sequencer[0];
    sequencer_idx = 0;
    ADC_CB_REGISTER(_Analog_Handler);
    ADC_MUX_SET(pins_list[index]);
}

uint16_t Analog_MaxGet(void)
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

