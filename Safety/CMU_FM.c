#include "CMU_FM.h"

//---------------------------------------
/*

Global Configuration Register (GCR)
Offset
Register Offset
GCR 0h
Function
Controls module level configurations such as enabling frequency metering.
*/

uint8_t get_Global_Configuration_Register(){
return (uint8_t)(*CMU_GCR & 0b1); 
}

void set_Global_Configuration_Register(uint8_t FME){
*CMU_GCR&=~0b1;
*CMU_GCR|=FME;
}

//------------------------------------------

/*
Reference Count Configuration Register (RCCR)
Offset
Register Offset
RCCR 4h
Function
Programs reference count duration of the frequency meter window.
Write to RCCR only when GCR[FME] = 0. A bus transfer error results if software writes RCCR when GCR[FME] = 1.

*/


uint16_t get_Reference_Count_Configuration_Register(){
return (uint16_t)(*CMU_RCCR & 0xFFFF);
}

void set_Reference_Count_Configuration_Register(uint16_t REF_CNT){
*CMU_RCCR&=~0xFFFF;
*CMU_RCCR|=REF_CNT;
}

//-------------------------------------------------

/*
Status Register (SR)
Offset
Register Offset
SR 8h
Function
Provides the internal status of the module and metered clock count.

*/

CMF_FM_STATUS get_CMF_FM_Status_Register(){
CMF_FM_STATUS status;
status.MET_CNT=(uint32_t)((*CMU_SR >>8) & 0xFFFFFF);
status.FMTO=(uint8_t)((*CMU_SR >>1) & 0b1);
status.FMC=(uint8_t)(*CMU_SR & 0b1);
return status;
}


void Clear_CMF_FM_Status_Register(uint8_t clc){
*CMU_SR&=~0b11;
*CMU_SR|=clc;
}

//-------------------------------------------

/*
Interrupt Enable Register (IER)
Offset
Register Offset
IER Ch
Function
Enables CMU_FM interrupts.
Write IER only when GCR[FME] = 0. A bus transfer error results if software writes IER when GCR[FME] = 1.
*/

uint8_t get_Interrupt_Enable_Register(){
    return (uint8_t)(*CMU_IER & 0b1);
}

void set_Interrupt_Enable_Register(uint8_t FMCIE){
*CMU_IER&=~0b1;
*CMU_IER|=FMCIE;
}