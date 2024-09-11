#include "PIT.h"
#include <stdint.h>

//-------------------------

/*

PIT Module Control (MCR)
Offset
Register Offset
MCR 0h
Function
Enables the PIT timer clocks and specifies the behavior of the timers when PIT enters Debug mode

*/

PIT_MCR_t get_PIT_MCR(void) {
    PIT_MCR_t mcr;
    uint32_t reg_value = *PIT_MCR; // Read the PIT_MCR register
    
    mcr.FRZ = (reg_value & 0x01); // Extract bit 0
    mcr.MDIS = (reg_value >> 1) & 0x01; // Extract bit 1
    mcr.MDIS_RTI = (reg_value >> 2) & 0x01; // Extract bit 2
    
    return mcr;
}


void set_PIT_MCR(PIT_MCR_t mcr) {
    uint32_t reg_value = 0;
    
    reg_value |= (mcr.FRZ & 0x01); // Set bit 0
    reg_value |= ((mcr.MDIS & 0x01) << 1); // Set bit 1
    reg_value |= ((mcr.MDIS_RTI & 0x01) << 2); // Set bit 2
    
    *PIT_MCR = reg_value; // Write the value to PIT_MCR
}

//------------------

/*
PIT Upper Lifetimer (LTMR64H)
Offset
Register Offset
LTMR64H E0h


Function
Combined with LTMR64L, provides a 64-bit lifetimer constructed from the values in two chained PIT timers.
For more information
*/


uint32_t set_PIT_Upper_Lifetimer(){
return (*PIT_LTMR64H);
}

uint32_t set_PIT_Lower_Lifetimer(){
return (*PIT_LTMR64L);
}

//------------------------------

/*
RTI Timer Load Value Sync Status (RTI_LDVAL_STAT)
Offset
Register Offset
RTI_LDVAL_STAT ECh

Function
Indicates whether the RTI timer start value has been loaded (RTI_LDVAL). This status is necessary because it takes several
cycles for the RTI start value to synchronize into the RTI clock domain.
*/

uint8_t get_RTI_Timer_Load_Value_Sync_Status(){
return (uint8_t)((*PIT_RTI_LDVAL_STAT & 0b1));
}

void set_RTI_Timer_Load_Value_Sync_Status(uint8_t RT_STAT){
*PIT_RTI_LDVAL_STAT &=~ 0b1;
*PIT_RTI_LDVAL_STAT|=RT_STAT;
}
//-------------------------------------
/*

RTI Timer Load Value (RTI_LDVAL)
Offset
Register Offset
RTI_LDVAL F0h
Function
Specifies the length of the RTI timeout period in clock cycles.
It takes several cycles for this value to synchronize into the RTI clock domain.

*/

uint32_t get_RTI_Timer_Load_Value(){
    return *PIT_RTI_LDVAL;
}

void set_RTI_Timer_Load_Value(uint32_t TSV){
*PIT_RTI_LDVAL=TSV;
}

//--------------------------------------

/*
Current RTI Timer Value (RTI_CVAL)
Offset
Register Offset
RTI_CVAL F4h
Function
Indicates the current RTI timer value. Because this timer might be driven from a different clock domain from the other timers,
the value may be several cycles old

*/


uint32_t get_Current_RTI_Timer_Value(){
return *PIT_RTI_CVAL;
}

//-----------------------------------------------

/*

RTI Timer Control (RTI_TCTRL)
Offset
Register Offset
RTI_TCTRL F8h
Function
Controls RTI timer behavior.
The RTI may take several RTI clock cycles to enable or update. Therefore, you must wait for at least three RTI clock cycles after
RTI configuration before relying on the RTI timer.
*/

RTI_control get_RTI_Timer_Control(){
    RTI_control cfg;
    cfg.TIE=(uint8_t)((*PIT_RTI_TCTRL >>1) & 0b1);
    cfg.TEN=(uint8_t)(*PIT_RTI_TCTRL & 0b1);
    return cfg;
}

void set_RTI_Timer_Control(RTI_control cfg){
        uint32_t reg_value = 0;

    reg_value |= (cfg.TEN & 0x01);        
    reg_value |= ((cfg.TIE & 0x01) << 1); 

    *PIT_RTI_TCTRL = reg_value; // Write the value to RTI_CTRL
}
//-------------------------

/*
RTI Timer Interrupt Flag (RTI_TFLG)
Offset
Register Offset
RTI_TFLG FCh
Function
Indicates the RTI timer has expired
*/

uint8_t get_RTI_Timer_Interrupt_Flag(){
return (uint8_t)(*PIT_RTI_TFLG & 0b1) ;
}

void clear_RTI_Timer_Interrupt_Flag(uint8_t TIF){
*PIT_RTI_TFLG&=0b1;
*PIT_RTI_TFLG|=TIF;
}

//---------------------------------------------

/*
Timer Load Value (LDVAL0 - LDVAL3)
Offset
Register Offset
LDVAL0 100h
LDVAL1 110h
LDVAL2 120h
LDVAL3 130h
Function
Specifies the length of the timeout period in clock cycles.
The value change is visible immediately. The synchronization mechanism allows 0 wait states in this case
*/
uint32_t get_Timer_Load_Value(uint8_t n){
return (*PIT_LDVAL(n));
}

void set_Timer_Load_Value(uint32_t tsv,uint8_t n){
(*PIT_LDVAL(n))=tsv;
}

//-------------------------------------------------

/*

Current Timer Value (CVAL0 - CVAL3)
Offset
Register Offset
CVAL0 104h
CVAL1 114h
CVAL2 124h
CVAL3 134h
Function
Indicates the current timer value

*/

uint32_t get_Current_Timer_Value(uint8_t n){
return *PIT_CVAL(n);
}

//---------------------------

/*

Timer Control (TCTRL0 - TCTRL3)


 * Timer Control Registers
 * -------------------------
 * Offset     | Register Offset | Function
 * -------------------------------------------
 * TCTRL0     | 0x108           | Controls timer behavior.
 * TCTRL1     | 0x118           | Controls timer behavior.
 * TCTRL2     | 0x128           | Controls timer behavior.
 * TCTRL3     | 0x138           | Controls timer behavior.
 */


Control_timer get_Control_timer(uint8_t n) {
    Control_timer ctrl;
    uint32_t reg_value = *PIT_TCTRL(n); 

    ctrl.TEN = reg_value & 0x01;          // Extract Timer Enable (bit 0)
    ctrl.TIE = (reg_value >> 1) & 0x01;   // Extract Timer Interrupt Enable (bit 1)
    ctrl.CHN = (reg_value >> 2) & 0x01;   // Extract Chain Mode (bit 2)

    return ctrl;
}

void set_Control_timer(Control_timer ctrl) {
    uint32_t reg_value = 0;

    reg_value |= (ctrl.TEN & 0x01);        // Set Timer Enable (bit 0)
    reg_value |= ((ctrl.TIE & 0x01) << 1); // Set Timer Interrupt Enable (bit 1)
    reg_value |= ((ctrl.CHN & 0x01) << 2); // Set Chain Mode (bit 2)

    *PIT_TCTRL(n) = reg_value; // Write the value to PIT_TCTRL
}

//-------------------------------

/* Timer Flag Registers */

/*
 * Register Offset    | Function
 * ------------------ | --------------------------------------------
 * TFLG0              | Indicates the PIT timer has expired.
 * Offset: 0x10C
 *
 * TFLG1              | Indicates the PIT timer has expired.
 * Offset: 0x11C
 *
 * TFLG2              | Indicates the PIT timer has expired.
 * Offset: 0x12C
 *
 * TFLG3              | Indicates the PIT timer has expired.
 * Offset: 0x13C
 */


uint8_t get_Timer_Flag(uint8_t n){
return (uint8_t)(*PIT_TFLG(n) & 0b1);
}

void clear_Timer_Flag (uint8_t TIF,uint8_t n){
(*PIT_TFLG(n))&=~0b1;
(*PIT_TFLG(n))|=TIF;
}