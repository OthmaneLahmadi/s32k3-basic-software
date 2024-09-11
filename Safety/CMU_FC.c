#include "CMU_FC.h"
#include <stdint.h>

//-------------------------------------
/*
Global Configuration Register (GCR)
Offset
Register Offset
GCR 0h
Function
Controls module level configurations such as enabling frequency check.
*/

uint8_t get_Global_Configuration_Register(){
return (uint8_t)(*CMU_GCR & 0b1);
}

void set_Global_Configuration_Register(uint8_t FCE){
*CMU_GCR&=~0b1;
*CMU_GCR|=FCE;
}

//-----------------------------------------------

/*

Reference Count Configuration Register (RCCR)
Offset
Register Offset
RCCR 4h
Function
Programs reference count duration of the frequency check window.
Write to RCCR only when GCR[FCE] = 0. A bus transfer error results if software writes RCCR when GCR[FCE] = 1.
*/

uint16_t get_Reference_Count_Configuration_Register(){
return (uint16_t)(*CMU_RCCR & 0xFFFF);
}

void set_Reference_Count_Configuration_Register(uint16_t REF_CNT){
*CMU_RCCR&=~0xFFFF;
*CMU_RCCR|=REF_CNT;
}

//----------------------------------------------------

/*
High Threshold Configuration Register (HTCR)
Offset
Register Offset
HTCR 8h
Function
Determines the high threshold limit of the monitored clock counter.
Write HTCR only when GCR[FCE] = 0. A bus transfer error results if software writes HTCR when GCR[FCE] = 1*/


uint32_t get_High_Threshold_Configuration_Register(){
    return (uint32_t)(*CMU_HTCR & 0xFFFFFF)
}

void set_High_Threshold_Configuration_Register(uint32_t HFREF){
*CMU_HTCR&=~(0xFFFFFF);
*CMU_HTCR|=HFREF;
}

//------------------------------------------------

/*
Low Threshold Configuration Register (LTCR)
Offset
Register Offset
LTCR Ch
Function
Determines the low threshold limit of the monitored clock counter.
Write LTCR only when GCR[FCE] = 0. A bus transfer error results if software writes LTCR when GCR[FCE] = 1.

*/

uint32_t get_Low_Threshold_Configuration_Register(){
    return (uint32_t)(*CMU_LTCR & 0xFFFFFF);
}

void set_Low_Threshold_Configuration_Register(uint32_t LFREF){
*CMU_LTCR &=~(0xFFFFFF);
*CMU_LTCR|=LFREF;
}

//-------------------------------------------------------

/*
Status Register (SR)
Offset
Register Offset
SR 10h
Function
Provides the internal status of the module.

*/


CMU_status_register get_CMU_Status_Register(){
CMU_status_register stat; 
uint32_t reg=*CMU_SR;
stat.RS=(uint8_t)((reg >> 4) & 0b1);
stat.FHH=(uint8_t)((reg >> 1) & 0b1);
stat.FLL=(uint8_t)((reg >> 0) & 0b1);
return stat;
}

void clear_CMU_Status_Register(uint8_t clc){
uint32_t reg=0;
reg=(uint32_t)clc;
*CMU_SR=reg;
}

//------------------------------------------------------

/*

Interrupt Enable Register (IER)
Offset
Register Offset
IER 14h
Function
Enables CMU_FC interrupts.
Write IER only when GCR[FCE] = 0. A bus transfer error results if software writes IER when GCR[FCE] = 1.
NOTE
Enable only either asynchronous FHH event interrupt or synchronous FHH event interrupt at a time.
For example:
• If IER[FHHIE] is set to 1 then set IER[FHHAIE] to 0.
• If IER[FHHAIE] is set to 1 then set IER[FHHIE] to 0.
Enable only either asynchronous FLL event interrupt or synchronous FLL event interrupt at a time.
 */

 