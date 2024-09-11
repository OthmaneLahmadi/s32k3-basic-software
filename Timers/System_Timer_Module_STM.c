#include "STM.h"
#include <stdio.h>

//---------------------------------------
/*
Control (CR)
Offset
Register Offset
CR 0h
Function
Contains fields for the prescale value, freeze control, and timer enable
*/


void CR_SWT_Set(const STM_Control* config) {
    uint32_t value = 0;

    // Set the individual fields from the structure
    value |= ((uint32_t)config->TEN) << 0;
    value |= ((uint32_t)config->FRZ) << 1;
    value |= ((uint32_t)config->CPS) << 8;

    // Write the value to the CR_SWT register
    *CR_SWT = value;
}

void CR_SWT_Get(STM_Control* config) {
    // Read the value from the CR_SWT register
    uint32_t value = CR_SWT;

    // Populate the structure with the register fields
    config->TEN = (value >> 0) & 0x1;
    config->FRZ = (value >> 1) & 0x1;
    config->CPS = (value >> 8) & 0xFF;
}

//--------------------------------------------------------

/*
Count (CNT)
Offset
Register Offset
CNT 4h
Function
Holds the timer count value.

*/

uint32_t get_Count(){
return *CNT;
}

void set_Count(uint32_t cnt){
*CNT=cnt;
}
//---------------------------------------------------------


/*

Channel Control (CCR0 - CCR3)
Offset
Register Offset
CCR0 10h
CCR1 20h
CCR2 30h
CCR3 40h
Function
Enables channel n of the timer.

*/

uint8_t get_Channel_Control(uint8_t chanel){
return (uint8_t)((*CCR(n) & 0b1));
}

void set_Channel_Control(uint8_t chanel,uint8_t CEN){
(*CCR(chanel))&=~0b1;
*CCR(chanel)|=CEN;
}
//---------------------------------------------

/*
Channel Interrupt (CIR0 - CIR3)
Offset
Register Offset
CIR0 14h
CIR1 24h
CIR2 34h
CIR3 44h
Function
Indicates and clears the interrupt flag for channel n of the timer.

*/

void set_Channel_Interrupt(uint8_t CIF,uint8_t chanel){
(*CIR(chanel))&=~0b1;
*CIR(chanel)|=CIF;
}

uint8_t get_Channel_Interrupt(uint8_t chanel){
return (uint8_t)(*CIR(chanel) & 0b1);
}

//------------------------------------------------------
/*

Channel Compare (CMP0 - CMP3)
Offset
Register Offset
CMP0 18h
CMP1 28h
CMP2 38h
CMP3 48h
Function
The compare value for channel n.

 */

void set_Channel_Compare(uint32_t cmp,uint8_t chanel){
(*CMP(chanel))=cmp;
}

uint32_t get_Channel_Compare(uint8_t chanel){
return *(CMP(chanel));
}