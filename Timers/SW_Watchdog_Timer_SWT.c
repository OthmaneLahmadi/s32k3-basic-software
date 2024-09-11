#include "SWT.h"

//--------------------
/*
Control (CR)
Offset
Register Offset
CR 0h
Function
Contains fields for configuring and controlling SWT. The register is read-only if either hard lock or soft lock is enabled (either HLK
or SLK is 1).

*/

void SWTControl_Set(const watchdog_register_t* config) {
    // Write values from the structure to the CR register
    *CR = ((uint32_t)config->MAP0 << 31) |
         ((uint32_t)config->MAP1 << 30) |
         ((uint32_t)config->MAP2 << 29) |
         ((uint32_t)config->MAP3 << 28) |
         ((uint32_t)config->MAP4 << 27) |
         ((uint32_t)config->MAP5 << 26) |
         ((uint32_t)config->MAP6 << 25) |
         ((uint32_t)config->MAP7 << 24) |
         ((uint32_t)config->SMD  << 9)  |
         ((uint32_t)config->RIA  << 8)  |
         ((uint32_t)config->WND  << 7)  |
         ((uint32_t)config->ITR  << 6)  |
         ((uint32_t)config->HLK  << 5)  |
         ((uint32_t)config->SLK  << 4)  |
         ((uint32_t)config->STP  << 2)  |
         ((uint32_t)config->FRZ  << 1)  |
         ((uint32_t)config->WEN);
}


void SWTControl_Get(watchdog_register_t* config) {
    // Read the CR register into the structure
    uint32_t value = *CR;
    config->MAP0 = (value >> 31) & 0x1;
    config->MAP1 = (value >> 30) & 0x1;
    config->MAP2 = (value >> 29) & 0x1;
    config->MAP3 = (value >> 28) & 0x1;
    config->MAP4 = (value >> 27) & 0x1;
    config->MAP5 = (value >> 26) & 0x1;
    config->MAP6 = (value >> 25) & 0x1;
    config->MAP7 = (value >> 24) & 0x1;
    config->SMD  = (value >> 9)  & 0x3;
    config->RIA  = (value >> 8)  & 0x1;
    config->WND  = (value >> 7)  & 0x1;
    config->ITR  = (value >> 6)  & 0x1;
    config->HLK  = (value >> 5)  & 0x1;
    config->SLK  = (value >> 4)  & 0x1;
    config->STP  = (value >> 2)  & 0x1;
    config->FRZ  = (value >> 1)  & 0x1;
    config->WEN  = value & 0x1;
}

//------------------------------------------------------------------

/*
Interrupt (IR)
Offset
Register Offset
IR 4h
Function
The timeout interrupt flag.

*/

void set_Interrupt(uint8_t TIF){
*IR&=~0b1;
*IR|=TIF;
}

uint8_t get_Interrupt(){
    return (uint8_t)(*IR & 0b1);
}

//---------------------------------------

/*
Timeout (TO)
Offset
Register Offset
TO 8h
Function
Contains the 32-bit timeout period. The register is read-only if either hard lock or soft lock is enabled (CR[HLK] or CR[SLK] is 1).
*/

void set_Timeout(uint32_t WTO){
*TO=WTO;
}

uint32_t get_Timeout(){
return *TO;
}

//-----------------------------------------------------------

/*

Window (WN)
Offset
Register Offset
WN Ch
Function
Contains the 32-bit window start value. SWT clears this register on reset. The register is read-only if either hard lock or soft lock
is enabled (CR[HLK] or CR[SLK] is 1).

*/

void set_Window(uint32_t WST){
*WN=WST;
}

uint32_t get_Window(){
return *WN;
}

//---------------------------------------------
/*

Service (SR)
Offset
Register Offset
SR 10h
Function
Initiates the service operation and resets the watchdog timer.


*/

void set_Service(uint16_t WSC){
*SR &=~(0xFFFF);
*SR|=WSC;
}
//---------------------------------------

/*

Counter Output (CO)
Offset
Register Offset
CO 14h
Function
Shows the value of the internal timer when SWT is disabled.
*/

void set_Counter_Output(uint32_t CNT){
*CO=CNT;
}

uint32_t get_Counter_Output(){
return *CO;
}


//-------------------------------------------------

/*

Service Key (SK)
Offset
Register Offset
SK 18h
Function
Holds the previous (or initial) service key value. This register is read-only if either hard lock or soft lock is enabled (CR[HLK] or
CR[SLK] is 1).

*/

void set_Service_Key (uint16_t sk){
*SK&=~(0xFFFF);
*SK=sk;
}

uint16_t get_Service_Key(){
return (uint16_t)(*SK);
}

//--------------------------------------------------------

/*
Event Request (RRR)
Offset
Register Offset
RRR 1Ch
Function
Contains the timeout reset request flag. See the chip-specific information for the specific event associated with this flag.

*/

uint8_t get_Event_Request(){
return (uint8_t)(*RRR & 0b1);
}

void set_Event_Request(uint8_t rrr){
*(RRR)&=~0b1;
*(RRR)=rrr;
}