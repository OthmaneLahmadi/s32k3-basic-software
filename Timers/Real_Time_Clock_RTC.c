#include "RTC.h"
#include <stdint.h>

//------------
/*

RTC Supervisor control register (RTCSUPV)
Offset
Register Offset
RTCSUPV 0h

*/

uint8_t get_RTC_Supervisor_Control_Register(){
    return (uint8_t)((*RTCSUPV >>31)& 0b1 ) ;
}

void set_RTC_Supervisor_Control_Register(uint8_t SUPV){
*RTCSUPV &=~(0b1<<31);
*RTCSUPV|=SUPV<<31;
}

//----------------------------

/*

RTC Control register (RTCC)
Offset
Register Offset
RTCC 4h
*/

RTC_CONTROL get_RTCC(void) {
    RTC_CONTROL rtcControl;
    uint8_t regValue = *RTCC;  // Read the value from the RTCC register

    // Extract fields from the register value
    rtcControl.TRIG_EN  = (regValue >> 0) & 0x01;
    rtcControl.DIV32EN  = (regValue >> 10) & 0x01;
    rtcControl.DIV512EN = (regValue >> 11) & 0x01;
    rtcControl.CLKSEL   = (regValue >> 12) & 0x03;
    rtcControl.APIIE    = (regValue >> 14) & 0x01;
    rtcControl.APIEN    = (regValue >> 15) & 0x01;
    rtcControl.ROVREN   = (regValue >> 28) & 0x01;
    rtcControl.FRZEN    = (regValue >> 29) & 0x01;
    rtcControl.RTCIE    = (regValue >> 30) & 0x01;
    rtcControl.CNTEN    = (regValue >> 31) & 0x01;

    return rtcControl;
}


void set_RTCC(const RTC_CONTROL *rtcControl) {
    uint32_t regValue = 0;

    regValue |= (rtcControl->TRIG_EN       << 0);
    regValue |= (rtcControl->DIV32EN       << 10);
    regValue |= (rtcControl->DIV512EN      << 11);
    regValue |= (rtcControl->CLKSEL        << 12);
    regValue |= (rtcControl->APIIE         << 14);
    regValue |= (rtcControl->APIEN         << 15);
    regValue |= (rtcControl->ROVREN        << 28);
    regValue |= (rtcControl->FRZEN         << 29);
    regValue |= (rtcControl->RTCIE         << 30);
    regValue |= (rtcControl->CNTEN         << 31);

    // Write the value to the RTCC register
    *RTCC = regValue;
}

//----------------------

/*

RTC Status register (RTCS)
Offset
Register Offset
RTCS 8h

*/

RTC_STATUS get_RTC_STATUS(void) {
    RTC_STATUS RTC_STATUS;
    uint32_t regValue = *RTCS;  // Read the value from the RTCC register

    // Extract fields from the register value
    RTC_STATUS.RTCF    = (regValue >> 29) & 0x01;
    RTC_STATUS.INV_RTC = (regValue >> 18) & 0x01;
    RTC_STATUS.INV_API = (regValue >> 17) & 0x01;
    RTC_STATUS.APIF    = (regValue >> 13) & 0x01;
    RTC_STATUS.ROVRF   = (regValue >> 10) & 0x01;

    return RTC_STATUS;
}


void set_RTC_STATUS(const RTC_STATUS *RTC_STATUS) {
    uint32_t regValue = 0;

    // Combine fields into a single register value
    regValue |= (RTC_STATUS->RTCF    << 29);
    regValue |= (RTC_STATUS->INV_RTC << 18);
    regValue |= (RTC_STATUS->INV_API << 17);
    regValue |= (RTC_STATUS->APIF    << 13);
    regValue |= (RTC_STATUS->ROVRF   << 10);

    // Write the value to the RTCC register
    *RTCS = regValue;
}
//-----------------------------------------------

/*
RTC Counter register (RTCCNT)
Offset
Register Offset
RTCCNT Ch
*/

uint32_t get_RTC_Counter_Register(){
    return *RTCCNT;
}

//--------------------------------------

/*
API Compare value register (APIVAL)
Offset
Register Offset
APIVAL 10h
Function
The APIVAL offset bits are compared to the RTC counter bits and if a match occurs, an interrupt/wakeup request is asserted.
*/

uint32_t get_API_Compare_Value(){
return *APIVAL;
}

void set_API_Compare_Value(uint32_t apival){
*APIVAL=apival;
}

//---------------------------------------
/*
RTC Compare value register (RTCVAL)
Offset
Register Offset
RTCVAL 14h
Function
The RTCVAL bits are compared to the RTC counter bits and if a match occurs, RTCF is set. The minimum value of RTCVAL should
be 4
*/

uint32_t get_RTC_Compare_Value_Register(){
return *RTCVAL;
}

void set_RTC_Compare_Value_Register(uint32_t rtcval){
*RTCVAL=rtcval;
}
