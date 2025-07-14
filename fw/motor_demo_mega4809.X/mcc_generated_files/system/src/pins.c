/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 1.1.0
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

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

#include "../pins.h"

static void (*DRIVE_H0_InterruptHandler)(void);
static void (*DRIVE_H1_InterruptHandler)(void);
static void (*DRIVE_H2_InterruptHandler)(void);
static void (*RX3_InterruptHandler)(void);
static void (*TX3_InterruptHandler)(void);
static void (*BEMF_N_InterruptHandler)(void);
static void (*BEMF_A_InterruptHandler)(void);
static void (*EVSYS_OUT_InterruptHandler)(void);
static void (*CRT_P_InterruptHandler)(void);
static void (*BEMF_B_InterruptHandler)(void);
static void (*BEMF_C_InterruptHandler)(void);
static void (*VBUS_InterruptHandler)(void);
static void (*POT_InterruptHandler)(void);
static void (*FAULT_INPUT_InterruptHandler)(void);
static void (*PWM_IN_InterruptHandler)(void);
static void (*BUTTON_InterruptHandler)(void);
static void (*DRIVE_L0_InterruptHandler)(void);
static void (*DRIVE_L1_InterruptHandler)(void);
static void (*DRIVE_L2_InterruptHandler)(void);
static void (*DBG_0_InterruptHandler)(void);
static void (*DBG_1_InterruptHandler)(void);
static void (*DBG_2_InterruptHandler)(void);
static void (*DBG_3_InterruptHandler)(void);
static void (*LED_InterruptHandler)(void);

void PIN_MANAGER_Initialize()
{

  /* OUT Registers Initialization */
    PORTA.OUT = 0x0;
    PORTB.OUT = 0x1;
    PORTC.OUT = 0x0;
    PORTD.OUT = 0x0;
    PORTE.OUT = 0x0;
    PORTF.OUT = 0x20;

  /* DIR Registers Initialization */
    PORTA.DIR = 0xBF;
    PORTB.DIR = 0x1;
    PORTC.DIR = 0x3C;
    PORTD.DIR = 0x0;
    PORTE.DIR = 0x0;
    PORTF.DIR = 0x20;

  /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x0;
    PORTA.PIN1CTRL = 0x0;
    PORTA.PIN2CTRL = 0x0;
    PORTA.PIN3CTRL = 0x0;
    PORTA.PIN4CTRL = 0x0;
    PORTA.PIN5CTRL = 0x0;
    PORTA.PIN6CTRL = 0x0;
    PORTA.PIN7CTRL = 0x0;
    PORTB.PIN0CTRL = 0x0;
    PORTB.PIN1CTRL = 0x8;
    PORTB.PIN2CTRL = 0x0;
    PORTB.PIN3CTRL = 0x0;
    PORTB.PIN4CTRL = 0x0;
    PORTB.PIN5CTRL = 0x0;
    PORTB.PIN6CTRL = 0x0;
    PORTB.PIN7CTRL = 0x0;
    PORTC.PIN0CTRL = 0x0;
    PORTC.PIN1CTRL = 0x0;
    PORTC.PIN2CTRL = 0x0;
    PORTC.PIN3CTRL = 0x0;
    PORTC.PIN4CTRL = 0x0;
    PORTC.PIN5CTRL = 0x0;
    PORTC.PIN6CTRL = 0x0;
    PORTC.PIN7CTRL = 0x9;
    PORTD.PIN0CTRL = 0x4;
    PORTD.PIN1CTRL = 0x0;
    PORTD.PIN2CTRL = 0x4;
    PORTD.PIN3CTRL = 0x0;
    PORTD.PIN4CTRL = 0x4;
    PORTD.PIN5CTRL = 0x0;
    PORTD.PIN6CTRL = 0x4;
    PORTD.PIN7CTRL = 0x4;
    PORTE.PIN0CTRL = 0x4;
    PORTE.PIN1CTRL = 0x0;
    PORTE.PIN2CTRL = 0x4;
    PORTE.PIN3CTRL = 0x1;
    PORTE.PIN4CTRL = 0x0;
    PORTE.PIN5CTRL = 0x0;
    PORTE.PIN6CTRL = 0x0;
    PORTE.PIN7CTRL = 0x0;
    PORTF.PIN0CTRL = 0x0;
    PORTF.PIN1CTRL = 0x0;
    PORTF.PIN2CTRL = 0x0;
    PORTF.PIN3CTRL = 0x0;
    PORTF.PIN4CTRL = 0x0;
    PORTF.PIN5CTRL = 0x0;
    PORTF.PIN6CTRL = 0x8;
    PORTF.PIN7CTRL = 0x0;

  /* PORTMUX Initialization */
    PORTMUX.CCLROUTEA = 0x0;
    PORTMUX.EVSYSROUTEA = 0x1;
    PORTMUX.TCAROUTEA = 0x0;
    PORTMUX.TCBROUTEA = 0x0;
    PORTMUX.TWISPIROUTEA = 0x0;
    PORTMUX.USARTROUTEA = 0x0;

  // register default ISC callback functions at runtime; use these methods to register a custom function
    DRIVE_H0_SetInterruptHandler(DRIVE_H0_DefaultInterruptHandler);
    DRIVE_H1_SetInterruptHandler(DRIVE_H1_DefaultInterruptHandler);
    DRIVE_H2_SetInterruptHandler(DRIVE_H2_DefaultInterruptHandler);
    RX3_SetInterruptHandler(RX3_DefaultInterruptHandler);
    TX3_SetInterruptHandler(TX3_DefaultInterruptHandler);
    BEMF_N_SetInterruptHandler(BEMF_N_DefaultInterruptHandler);
    BEMF_A_SetInterruptHandler(BEMF_A_DefaultInterruptHandler);
    EVSYS_OUT_SetInterruptHandler(EVSYS_OUT_DefaultInterruptHandler);
    CRT_P_SetInterruptHandler(CRT_P_DefaultInterruptHandler);
    BEMF_B_SetInterruptHandler(BEMF_B_DefaultInterruptHandler);
    BEMF_C_SetInterruptHandler(BEMF_C_DefaultInterruptHandler);
    VBUS_SetInterruptHandler(VBUS_DefaultInterruptHandler);
    POT_SetInterruptHandler(POT_DefaultInterruptHandler);
    FAULT_INPUT_SetInterruptHandler(FAULT_INPUT_DefaultInterruptHandler);
    PWM_IN_SetInterruptHandler(PWM_IN_DefaultInterruptHandler);
    BUTTON_SetInterruptHandler(BUTTON_DefaultInterruptHandler);
    DRIVE_L0_SetInterruptHandler(DRIVE_L0_DefaultInterruptHandler);
    DRIVE_L1_SetInterruptHandler(DRIVE_L1_DefaultInterruptHandler);
    DRIVE_L2_SetInterruptHandler(DRIVE_L2_DefaultInterruptHandler);
    DBG_0_SetInterruptHandler(DBG_0_DefaultInterruptHandler);
    DBG_1_SetInterruptHandler(DBG_1_DefaultInterruptHandler);
    DBG_2_SetInterruptHandler(DBG_2_DefaultInterruptHandler);
    DBG_3_SetInterruptHandler(DBG_3_DefaultInterruptHandler);
    LED_SetInterruptHandler(LED_DefaultInterruptHandler);
}

/**
  Allows selecting an interrupt handler for DRIVE_H0 at application runtime
*/
void DRIVE_H0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DRIVE_H0_InterruptHandler = interruptHandler;
}

void DRIVE_H0_DefaultInterruptHandler(void)
{
    // add your DRIVE_H0 interrupt custom code
    // or set custom function using DRIVE_H0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DRIVE_H1 at application runtime
*/
void DRIVE_H1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DRIVE_H1_InterruptHandler = interruptHandler;
}

void DRIVE_H1_DefaultInterruptHandler(void)
{
    // add your DRIVE_H1 interrupt custom code
    // or set custom function using DRIVE_H1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DRIVE_H2 at application runtime
*/
void DRIVE_H2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DRIVE_H2_InterruptHandler = interruptHandler;
}

void DRIVE_H2_DefaultInterruptHandler(void)
{
    // add your DRIVE_H2 interrupt custom code
    // or set custom function using DRIVE_H2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for RX3 at application runtime
*/
void RX3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    RX3_InterruptHandler = interruptHandler;
}

void RX3_DefaultInterruptHandler(void)
{
    // add your RX3 interrupt custom code
    // or set custom function using RX3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for TX3 at application runtime
*/
void TX3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    TX3_InterruptHandler = interruptHandler;
}

void TX3_DefaultInterruptHandler(void)
{
    // add your TX3 interrupt custom code
    // or set custom function using TX3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for BEMF_N at application runtime
*/
void BEMF_N_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    BEMF_N_InterruptHandler = interruptHandler;
}

void BEMF_N_DefaultInterruptHandler(void)
{
    // add your BEMF_N interrupt custom code
    // or set custom function using BEMF_N_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for BEMF_A at application runtime
*/
void BEMF_A_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    BEMF_A_InterruptHandler = interruptHandler;
}

void BEMF_A_DefaultInterruptHandler(void)
{
    // add your BEMF_A interrupt custom code
    // or set custom function using BEMF_A_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for EVSYS_OUT at application runtime
*/
void EVSYS_OUT_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    EVSYS_OUT_InterruptHandler = interruptHandler;
}

void EVSYS_OUT_DefaultInterruptHandler(void)
{
    // add your EVSYS_OUT interrupt custom code
    // or set custom function using EVSYS_OUT_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for CRT_P at application runtime
*/
void CRT_P_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    CRT_P_InterruptHandler = interruptHandler;
}

void CRT_P_DefaultInterruptHandler(void)
{
    // add your CRT_P interrupt custom code
    // or set custom function using CRT_P_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for BEMF_B at application runtime
*/
void BEMF_B_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    BEMF_B_InterruptHandler = interruptHandler;
}

void BEMF_B_DefaultInterruptHandler(void)
{
    // add your BEMF_B interrupt custom code
    // or set custom function using BEMF_B_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for BEMF_C at application runtime
*/
void BEMF_C_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    BEMF_C_InterruptHandler = interruptHandler;
}

void BEMF_C_DefaultInterruptHandler(void)
{
    // add your BEMF_C interrupt custom code
    // or set custom function using BEMF_C_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for VBUS at application runtime
*/
void VBUS_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    VBUS_InterruptHandler = interruptHandler;
}

void VBUS_DefaultInterruptHandler(void)
{
    // add your VBUS interrupt custom code
    // or set custom function using VBUS_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for POT at application runtime
*/
void POT_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    POT_InterruptHandler = interruptHandler;
}

void POT_DefaultInterruptHandler(void)
{
    // add your POT interrupt custom code
    // or set custom function using POT_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for FAULT_INPUT at application runtime
*/
void FAULT_INPUT_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    FAULT_INPUT_InterruptHandler = interruptHandler;
}

void FAULT_INPUT_DefaultInterruptHandler(void)
{
    // add your FAULT_INPUT interrupt custom code
    // or set custom function using FAULT_INPUT_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PWM_IN at application runtime
*/
void PWM_IN_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PWM_IN_InterruptHandler = interruptHandler;
}

void PWM_IN_DefaultInterruptHandler(void)
{
    // add your PWM_IN interrupt custom code
    // or set custom function using PWM_IN_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for BUTTON at application runtime
*/
void BUTTON_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    BUTTON_InterruptHandler = interruptHandler;
}

void BUTTON_DefaultInterruptHandler(void)
{
    // add your BUTTON interrupt custom code
    // or set custom function using BUTTON_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DRIVE_L0 at application runtime
*/
void DRIVE_L0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DRIVE_L0_InterruptHandler = interruptHandler;
}

void DRIVE_L0_DefaultInterruptHandler(void)
{
    // add your DRIVE_L0 interrupt custom code
    // or set custom function using DRIVE_L0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DRIVE_L1 at application runtime
*/
void DRIVE_L1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DRIVE_L1_InterruptHandler = interruptHandler;
}

void DRIVE_L1_DefaultInterruptHandler(void)
{
    // add your DRIVE_L1 interrupt custom code
    // or set custom function using DRIVE_L1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DRIVE_L2 at application runtime
*/
void DRIVE_L2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DRIVE_L2_InterruptHandler = interruptHandler;
}

void DRIVE_L2_DefaultInterruptHandler(void)
{
    // add your DRIVE_L2 interrupt custom code
    // or set custom function using DRIVE_L2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DBG_0 at application runtime
*/
void DBG_0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DBG_0_InterruptHandler = interruptHandler;
}

void DBG_0_DefaultInterruptHandler(void)
{
    // add your DBG_0 interrupt custom code
    // or set custom function using DBG_0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DBG_1 at application runtime
*/
void DBG_1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DBG_1_InterruptHandler = interruptHandler;
}

void DBG_1_DefaultInterruptHandler(void)
{
    // add your DBG_1 interrupt custom code
    // or set custom function using DBG_1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DBG_2 at application runtime
*/
void DBG_2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DBG_2_InterruptHandler = interruptHandler;
}

void DBG_2_DefaultInterruptHandler(void)
{
    // add your DBG_2 interrupt custom code
    // or set custom function using DBG_2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DBG_3 at application runtime
*/
void DBG_3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DBG_3_InterruptHandler = interruptHandler;
}

void DBG_3_DefaultInterruptHandler(void)
{
    // add your DBG_3 interrupt custom code
    // or set custom function using DBG_3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for LED at application runtime
*/
void LED_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    LED_InterruptHandler = interruptHandler;
}

void LED_DefaultInterruptHandler(void)
{
    // add your LED interrupt custom code
    // or set custom function using LED_SetInterruptHandler()
}
ISR(PORTA_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTA.INTFLAGS & PORT_INT0_bm)
    {
       DRIVE_H0_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT1_bm)
    {
       DRIVE_H1_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT2_bm)
    {
       DRIVE_H2_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT7_bm)
    {
       EVSYS_OUT_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT3_bm)
    {
       DRIVE_L0_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT4_bm)
    {
       DRIVE_L1_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT5_bm)
    {
       DRIVE_L2_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTA.INTFLAGS = 0xff;
}

ISR(PORTB_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTB.INTFLAGS & PORT_INT1_bm)
    {
       RX3_InterruptHandler(); 
    }
    if(VPORTB.INTFLAGS & PORT_INT0_bm)
    {
       TX3_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTB.INTFLAGS = 0xff;
}

ISR(PORTC_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTC.INTFLAGS & PORT_INT7_bm)
    {
       FAULT_INPUT_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT2_bm)
    {
       DBG_0_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT3_bm)
    {
       DBG_1_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT4_bm)
    {
       DBG_2_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT5_bm)
    {
       DBG_3_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTC.INTFLAGS = 0xff;
}

ISR(PORTD_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTD.INTFLAGS & PORT_INT7_bm)
    {
       BEMF_N_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT2_bm)
    {
       BEMF_A_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT0_bm)
    {
       CRT_P_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT4_bm)
    {
       BEMF_B_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT6_bm)
    {
       BEMF_C_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTD.INTFLAGS = 0xff;
}

ISR(PORTE_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTE.INTFLAGS & PORT_INT0_bm)
    {
       VBUS_InterruptHandler(); 
    }
    if(VPORTE.INTFLAGS & PORT_INT2_bm)
    {
       POT_InterruptHandler(); 
    }
    if(VPORTE.INTFLAGS & PORT_INT3_bm)
    {
       PWM_IN_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTE.INTFLAGS = 0xff;
}

ISR(PORTF_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTF.INTFLAGS & PORT_INT6_bm)
    {
       BUTTON_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT5_bm)
    {
       LED_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTF.INTFLAGS = 0xff;
}

/**
 End of File
*/