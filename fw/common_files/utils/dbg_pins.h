/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DBG_PINS_H
#define	DBG_PINS_H

#include "mcc_mapping.h"

#define DBG0_SET          DBG_0_SetHigh
#define DBG1_SET          DBG_1_SetHigh
#define DBG2_SET          DBG_2_SetHigh
#define DBG3_SET          DBG_3_SetHigh
#define DBG0_CLR          DBG_0_SetLow
#define DBG1_CLR          DBG_1_SetLow
#define DBG2_CLR          DBG_2_SetLow
#define DBG3_CLR          DBG_3_SetLow
#define DBG0_TGL          DBG_0_Toggle
#define DBG1_TGL          DBG_1_Toggle
#define DBG2_TGL          DBG_2_Toggle
#define DBG3_TGL          DBG_3_Toggle

#define DBG0_SETVAL(b)           do{if(b) DBG0_SET();else DBG0_CLR();}while(0)
#define DBG1_SETVAL(b)           do{if(b) DBG1_SET();else DBG1_CLR();}while(0)
#define DBG2_SETVAL(b)           do{if(b) DBG2_SET();else DBG2_CLR();}while(0)
#define DBG3_SETVAL(b)           do{if(b) DBG3_SET();else DBG3_CLR();}while(0)

#endif	/* DBG_PINS_H */

