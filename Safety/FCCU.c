#include "FCCU.h"
#include <stdint.h>

//--------------------------------

/*

Control (CTRL)
Offset
Register Offset
CTRL 0h
Function
Initiates and indicates the status of operations—and enables the Debug mode.
*/

void set_CTRL(CTRL_t config) {
    uint32_t value = 0;
    value |= (uint32_t)(config.OPR & 0x1F);
    value |= (uint32_t)((config.OPS & 0x3) << 6);
    value |= (uint32_t)((config.DEBUG & 0x1) << 9);
    *CTRL_FCCU = value;
}


CTRL_t get_CTRL(void) {
    CTRL_t config;
    uint32_t value = *CTRL_FCCU;
    config.OPR = (uint8_t)(value & 0x1F);
    config.OPS = (uint8_t)((value >> 6) & 0x3);
    config.DEBUG = (uint8_t)((value >> 9) & 0x1);
    
    return config;
}

//-------------------------------------
/*
Control Key (CTRLK)
Offset
Register Offset
CTRLK 4h
*/

void  Set_Control_Key_State(uint32_t* ctrlk){
*CTRLK=ctrlk;
}

//----------------------------------
/*
Configuration (CFG)
Offset
Register Offset
CFG 8h
Function
Writable only when FCCU is in the CONFIG state. Changed by FCCU to another value when the chip resets FCCU, a
Configuration-state timeout occurs, or you run an OP31 operation.

if you specify a new value for any of the fields in this register that affect the EOUT signals while the fault-output
(EOUT) timer is running (FCCU is indicating a fault on the EOUT signals), FCCU does not use the new settings you
specified until after the fault-output (EOUT) timer expires (FCCU stops indicating a fault on the EOUT signals).
*/


void set_CFG(CFG_t config) {
    uint32_t value = 0;
    value |= (uint32_t)((config.FOM & 0x7) << 6);
    
    // Set PS (bit 9)
    value |= (uint32_t)((config.PS & 0x1) << 9);
    
    // Set CM (bit 11)
    value |= (uint32_t)((config.CM & 0x1) << 11);
    
    // Set FCCU_SET_CLEAR (bits 23-22)
    value |= (uint32_t)((config.FCCU_SET_CLEAR & 0x3) << 22);
    
    // Set FCCU_SET_AFTER_RESET (bit 24)
    value |= (uint32_t)((config.FCCU_SET_AFTER_RESET & 0x1) << 24);
    
    // Write the value to the CFG register
    *CFG = value;
}

CFG_t get_CFG(void) {
    CFG_t config;
    uint32_t value = *CFG;
    
    // Extract FOM (bits 8-6)
    config.FOM = (uint8_t)((value >> 6) & 0x7);
    
    // Extract PS (bit 9)
    config.PS = (uint8_t)((value >> 9) & 0x1);
    
    // Extract CM (bit 11)
    config.CM = (uint8_t)((value >> 11) & 0x1);
    
    // Extract FCCU_SET_CLEAR (bits 23-22)
    config.FCCU_SET_CLEAR = (uint8_t)((value >> 22) & 0x3);
    
    // Extract FCCU_SET_AFTER_RESET (bit 24)
    config.FCCU_SET_AFTER_RESET = (uint8_t)((value >> 24) & 0x1);
    
    return config;
}

//-----------------------------------------

/*

Non-critical Fault Configuration (NCF_CFG0)
Offset
Register Offset
NCF_CFG0 1Ch


Non-critical Fault Configuration n
Writable only when FCCU is in the CONFIG state. Changed by FCCU to its reset value when a
Configuration-state timeout occurs. Controls the recovery type (HW or SW) of the associated non-critical
fault channel (n). For information on how to configure the non-critical fault channels

*/

uint8_t get_Non_Critical_Fault_Configuration(uint8_t n){
    return (uint8_t)((*NCF_CFG0 >> (n*2)) & 0b11);
}

void set_Non_Critical_Fault_Configuration(uint8_t ncfscn,uint8_t n){
    *NCF_CFG0&=~(0b11<<(n*2));
    *NCF_CFG0|=ncfscn<<(n*2);
}

//------------------------------------------

/*
Non-critical Fault Status (NCF_S0)
Offset
Register Offset
NCF_S0 80h
*/


uint8_t get_Non_Critical_Fault_Status(uint8_t n){
    return (uint8_t)((*NCF_S0 >>n)& 0b1);
}

void Clear_Non_Critical_Fault_Status(uint8_t ncfsn,uint8_t n){
    *NCF_S0&=~(0b1<<(n));
    *NCF_S0|=ncfsn<<(n);
}

//----------------------------------

/*

Non-critical Fault Key (NCFK)
Offset
Register Offset
NCFK 90h

*/

void set_Non_Critical_Fault_Key(){
    return *NCFK;
}

//-----------------------------

/*
Non-critical Fault Enable (NCF_E0)
Offset
Register Offset
NCF_E0 94h

*/

uint8_t get_Non_Critical_Fault_Enable(uint8_t n){
    return (uint8_t)((*NCF_E0 >>n)& 0b1);
}

void Clear_Non_Critical_Fault_Status(uint8_t ncfen,uint8_t n){
    *NCF_E0&=~(0b1<<(n));
    *NCF_E0|=ncfen<<(n);
}
//-----------------------------------------

/*
Non-critical-Fault Alarm-State Timeout Enable (NCF_TOE0)
Offset
Register Offset
NCF_TOE0 A4h
*/
uint8_t get_Non_critical_Fault_Alarm_State_Timeout_Enable(uint8_t n){
    return (uint8_t)((*NCF_TOE0 >>n) & 0b1);
}

void set_Non_critical_Fault_Alarm_State_Timeout_Enable(uint8_t ncftoen,uint8_t n){
    *NCF_TOE0&=~(0b1<<(n));
    *NCF_TOE0|=ncftoen<<(n);
}

//---------------------------------------
/*

Non-critical-Fault Alarm-State Timeout Interval (NCF_TO)
Offset
Register Offset
NCF_TO B4h
*/

uint32_t get_Non_critical_Fault_Alarm_State_Timeout_Interval(){
    return *NCF_TO;
}

void set_Non_critical_Fault_Alarm_State_Timeout_Interval(uint32_t to){
    *NCF_TO=to;
}
//---------------------------------------------
/*
Configuration-State Timeout Interval (CFG_TO)
Offset
Register Offset
CFG_TO B8h
*/

uint8_t get_Configuration_State_Timeout_Interval(){
    return (uint8_t)(*CFG_TO & 0b111);
}

void set_Configuration_State_Timeout_Interval(uint8_t to){
    *CFG_TO&=~(0b111);
    *CFG_TO|=to;
}

//-------------------------------------

/*
IO Control (EINOUT)
Offset
Register Offset
EINOUT BCh
*/

/**
 * The EINOUT register allows the following operations typically in the NORMAL state:
 * - Control the EOUT[1] output level when the FCCU is configured in "Test1" or "Test0" fault output mode (CFG[FOM])
 * - Control the EOUT[0] output level when the FCCU is configured in "Test1" or "Test2" fault output mode (CFG[FOM])
 * - Observe the state of signals at EIN[1:0] pins
 *
 * Bi-Stable encoding based on Mode (CFG[FOM]):
 * 
 * | Mode  | EOUT[0] | EOUT[1] |
 * |-------|---------|---------|
 * | Test1 |  output |  output |
 * | Test2 |  output |  input  |
 * | Test0 |  input  |  output |
 */

void set_EINOUT(EINOUT_t config) {
    uint32_t value = 0;
    value |= (uint32_t)(config.EOUT0 & 0x1);
    value |= (uint32_t)((config.EOUT1 & 0x1) << 1);
    value |= (uint32_t)((config.EIN0 & 0x1) << 4);
    value |= (uint32_t)((config.EIN1 & 0x1) << 5);
    *EINOUT = value;
}

EINOUT_t get_EINOUT(void) {
    EINOUT_t config;
    uint32_t value = *EINOUT;
    config.EOUT0 = (uint8_t)(value & 0x1);
    config.EOUT1 = (uint8_t)((value >> 1) & 0x1);
    config.EIN0 = (uint8_t)((value >> 4) & 0x1);
    config.EIN1 = (uint8_t)((value >> 5) & 0x1);    
    return config;
}

//-----------------------------------------

/*
Status (STAT)
Offset
Register Offset
STAT C0h
Function
This register indicates the following:
• States that FCCU is driving on the EOUT signals
• Whether FCCU is in a faulty condition
• Current state of FCCU
*/

void set_STAT(STAT_t config) {
    uint32_t value = 0;
    value |= (uint32_t)(config.STATUS & 0x7);
    value |= (uint32_t)((config.ESTAT & 0x1) << 3);
    value |= (uint32_t)((config.PhysicErrorPin & 0x3) << 4);
    *STAT = value;
}

STAT_t get_STAT(void) {
    STAT_t config;
    uint32_t value = *STAT;
    config.STATUS = (uint8_t)(value & 0x7);
    config.ESTAT = (uint8_t)((value >> 3) & 0x1);
    config.PhysicErrorPin = (uint8_t)((value >> 4) & 0x3);
    return config;
}

//-----------------------------------------
/*
Normal-to-Alarm Freeze Status (N2AF_STATUS)
Offset
Register Offset
N2AF_STATUS C4h
*/

uint8_t get_Normal_to_Alarm_Freeze_Status(){
return (uint8_t)(*N2AF_STATUS & 0xFF);
}

//----------------------------------------

/*
Alarm-to-Fault Freeze Status (A2FF_STATUS)
Offset
Register Offset
A2FF_STATUS C8h
Function
Used only for testing and debugging. Indicates whether FCCU left the ALARM state and entered the FAULT state since the last
time this register was cleared and, if so, which type of fault caused FCCU to do so.
*/

void set_A2FF_STATUS(A2FF_STATUS_t config) {
    uint32_t value = 0;

    // Set AFFS (bits 7-0)
    value |= (uint32_t)(config.AFFS & 0xFF);

    // Set AF_SRC (bits 9-8)
    value |= (uint32_t)((config.AF_SRC & 0x3) << 8);

    // Write the value to the A2FF_STATUS register
    *A2FF_STATUS = value;
}

A2FF_STATUS_t get_A2FF_STATUS(void) {
    A2FF_STATUS_t config;
    uint32_t value = *A2FF_STATUS;

    // Extract AFFS (bits 7-0)
    config.AFFS = (uint8_t)(value & 0xFF);

    // Extract AF_SRC (bits 9-8)
    config.AF_SRC = (uint8_t)((value >> 8) & 0x3);
    return config;
}

//-----------------------------------------------
/*
Normal-to-Fault Freeze Status (N2FF_STATUS)
Offset
Register Offset
N2FF_STATUS CCh
Function
Used only for testing and debugging. Indicates whether FCCU left the NORMAL state and entered the FAULT state since the last
time this register was cleared and, if so, which type of fault caused FCCU to do so.
 */

void set_N2FF_STATUS(N2FF_STATUS_t config) {
    uint32_t value = 0;
    value |= (uint32_t)(config.NFFS & 0xFF);
    value |= (uint32_t)((config.NF_SRC & 0x3) << 8);
    *N2FF_STATUS = value;
}

N2FF_STATUS_t get_N2FF_STATUS(void) {
    N2FF_STATUS_t config;
    uint32_t value = *N2FF_STATUS;

    // Extract NFFS (bits 7-0)
    config.NFFS = (uint8_t)(value & 0xFF);

    // Extract NF_SRC (bits 9-8)
    config.NF_SRC = (uint8_t)((value >> 8) & 0x3);

    return config;
}

//--------------------------------------
/*
Fault-to-Alarm Freeze Status (F2AF_STATUS)
Offset
Register Offset
F2AF_STATUS D0h
*/

uint16_t get_Fault_to_Alarm_Freeze_Status(){
    return (uint16_t)(*F2AF_STATUS & 0x1FF);
}

//--------------------------------------------------------
/*

Non-critical Fault Fake (NCFF)
Offset
Register Offset
NCFF DCh
Function
This register contains a unique code to set a non-critical fault in mutually exclusive mode by the external FAULT interface (signal
setting). It allows the SW emulation of the non-critical faults, by injecting the fault directly in the FAULT root, to verify the entire
path and reaction. The reaction following a fake non-critical fault cannot be masked.
This is a write-only register with a set of codes corresponding to each non-critical fault injection
*/

void set_Non_Critical_Fault_Fake(uint8_t fncfc){
/*
00h: Fake non-critical fault injection at non-critical fault source 0
01h: Fake non-critical fault injection at non-critical fault source 1
02h: Fake non-critical fault injection at non-critical fault source 2
...
7Fh: Fake non-critical fault injection at non-critical fault source 127
*/
*NCFF&=~(0x7F);
*NCFF|=fncfc;
}

//---------------------------------------------------

/*
IRQ Status (IRQ_STAT)
Offset
Register Offset
IRQ_STAT E0h
Function
This register provides the FCCU interrupt status related to the following events:
• Configuration-state timeout error
• Alarm interrupt
• NMI interrupt
The configuration-state timeout interrupt is asserted if both IRQ_STAT[CFG_TO_STAT] and IRQ_EN[CFG_TO_IEN] bits are
asserted. It is cleared when a 1 is written to the IRQ_STAT[CFG_TO_STAT] bit.
The NMI and ALARM interrupts are asserted and cleared according to the FCCU state. The status bits of the IRQ_STAT trace the
status of the related interrupt lines
*/

void Clear_IRQ_STAT(IRQ_STAT_t config) {
    uint32_t value = 0;
    value |= (uint32_t)(config.CFG_TO_STAT & 0x1);
    *IRQ_STAT = value;
}

IRQ_STAT_t get_IRQ_STAT(void) {
    IRQ_STAT_t config;
    uint32_t value = IRQ_STAT;
    config.CFG_TO_STAT = (uint8_t)(value & 0x1);
    config.ALRM_STAT = (uint8_t)((value >> 1) & 0x1);
    config.NMI_STAT = (uint8_t)((value >> 2) & 0x1);
    return config;
}

//------------------------------------
/*
IRQ Enable (IRQ_EN)
Offset
Register Offset
IRQ_EN E4h
Function
This register is used to configure enabling of interrupt related to the "Configuration-state timeout error".
The configuration-state timeout interrupt is asserted if both the IRQ_STAT[CFG_TO_STAT] and IRQ_EN[CFG_TO_IEN] fields are
set to 1.
*/

uint8_t get_IRQ_Enable(){
    return (uint8_t)(*IRQ_EN &0b1);
}

void set_IRQ_Enable(uint8_t irq){
*IRQ_EN&=~(0b1);
*IRQ_EN|=(irq);
}

//-------------------------------------------

/*
Transient Configuration Lock (TRANS_LOCK)
Offset
Register Offset
TRANS_LOCK F0h*/

void acquire_Transient_Configuration_Lock(uint16_t TRANSKEY){
    *TRANS_LOCK&=~(0x1FF);
    *TRANS_LOCK|=TRANSKEY;
}
//--------------------------------
/*

Permanent Configuration Lock (PERMNT_LOCK)
Offset
Register Offset
PERMNT_LOCK F4h


*/

void set_Permanent_Configuration_Lock(uint16_t PERMNTKEY){
    *PERMNT_LOCK&=~(0x1FF);
    *PERMNT_LOCK|=TRANSKEY;
}
//-------------------------------------
/*

Delta T (DELTA_T)
Offset
Register Offset
DELTA_T F8h
Function
The DELTA_T register is used for programming the value of delta_T constant in microseconds.

Minimum Fault-Output (EOUT) Timer Interval
Applies only to Bi-Stable and Fault-Toggle fault-output modes (CFG[FOM]). Controls the minimum amount
of time (
Tmin) that the fault-output (EOUT) timer runs according to this equation:
Tmin = (250+ DELTA_T) μs * (48000/CLKSAFE freq KHz )

*/
uint16_t get_Delta_T(){
    return (uint16_t)(*DELTA_T & 0x3FF);
}

//--------------------------------------------

/*
Non-critical Alarm-State Interrupt-Request Enable (IRQ_ALARM_EN0)
Offset
Register Offset
IRQ_ALARM_EN0 FCh

Non-critical Alarm-State Interrupt-Request Enable n
Writable only when FCCU is in the CONFIG state. Changed by FCCU to its reset value when a
Configuration-state timeout occurs. Controls whether the interrupt request is enabled as the Alarm-state
reaction for the associated non-critical fault channel (n). When the ALARM state and the Alarm-state
interrupt request are enabled for an enabled non-critical fault channel, a fault on that channel causes FCCU
to assert the irq_alarm signal when FCCU enters the ALARM state; irq_alarm remains asserted until FCCU
*/


uint8_t get_Non_critical_Alarm_State_Interrupt_Request_Enable(uint8_t n){
    return (uint8_t)((*IRQ_ALARM_EN0 >>n) & 0b1);
}

void set_Non_critical_Alarm_State_Interrupt_Request_Enable(uint8_t irqenn,uint8_t n){
    *IRQ_ALARM_EN0&=~(0b1<<(n));
    *IRQ_ALARM_EN0|=irqenn<<(n);
}

//---------------------------------

/*
Non-critical Fault-State Non-maskable-Interrupt-Request Enable n
Writable only when FCCU is in the CONFIG state. Changed by FCCU to its reset value when a
Configuration-state timeout occurs. Controls whether the non-maskable interrupt request is enabled as
a Fault-state reaction for the associated non-critical fault channel (n). When the non-maskable interrupt
request is enabled for an enabled non-critical fault channel, a fault on that channel causes FCCU to assert the NMIOUT signal when FCCU enters the FAULT state; NMIOUT remains asserted until FCCU
exits FAULT state. 
*/

uint8_t get_Non_critical_Alarm_State_Interrupt_Request_Enable(uint8_t n){
    return (uint8_t)((*NMI_EN0 >>n) & 0b1);
}

void set_Non_critical_Alarm_State_Interrupt_Request_Enable(uint8_t nmienn,uint8_t n){
    *NMI_EN0&=~(0b1<<(n));
    *NMI_EN0|=nmienn<<(n);
}
//-------------------------------------
/*
Non-critical Fault-State EOUT Signaling Enable n
Writable only when FCCU is in the CONFIG state. Changed by FCCU to its reset value
when a Configuration-state timeout occurs. Applies only when the EOUT signals are active
(CFG[FCCU_SET_AFTER_RESET]). When FCCU is configured for Bi-Stable fault-output mode
0b - In Bi-Stable fault-output mode, both EOUT signaling and FIF assertion are disabled; in other
fault-output modes, EOUT signaling is enabled and FIF assertion is disabled.
1b - Both EOUT signaling and FIF assertion are enabled in all fault-output modes
*/
uint8_t get_Non_critical_Alarm_State_Interrupt_Request_Enable(uint8_t n){
    return (uint8_t)((*EOUT_SIG_EN0 >>n) & 0b1);
}

void set_Non_critical_Alarm_State_Interrupt_Request_Enable(uint8_t eouten,uint8_t n){
    *EOUT_SIG_EN0&=~(0b1<<(n));
    *EOUT_SIG_EN0|=eouten<<(n);
}
//---------------------------------------
/**
 * Alarm-State Timer (TMR_ALARM)
 * 
 * Offset: 0x12C
 * 
 * TMR_ALARM reset values based on FCCU state:
 * 
 * | FCCU state | Timer state | Timer value            |
 * |------------|-------------|------------------------|
 * | CONFIG     | Idle        | 0000_0000h             |
 * | NORMAL     | Idle        | Initial value: NCF_TO[TO] |
 * | ALARM      | Running     | Value when read        |
 * | FAULT      | Idle        | End of count           |
 */

uint32_t get_Alarm_State_Timer_Value(){
    return *TMR_ALARM;
}

void set_Alarm_State_Timer_Value(uint32_t count){
    *TMR_ALARM=count;
}
//------------------------------------------------------

/**
 * Configuration-State Timer (TMR_CFG)
 * 
 * Offset: 0x134
 * 
 * Function:
 * See TMR_CFG[COUNT].
 * 
 * Configuration-State Timer's state and value based on FCCU state:
 * 
 * | FCCU state | Timer state | Timer value  |
 * |------------|-------------|--------------|
 * | CONFIG     | Running     | Value when read |
 * | NORMAL     | Idle        | 000F_FFFFh   |
 * | ALARM      | Idle        | 000F_FFFFh   |
 * | FAULT      | Idle        | 000F_FFFFh   |
 */

uint32_t get_Configuration_State_Timer_Value(){
    return *TMR_CFG;
}

void set_Configuration_State_Timer_Value(uint32_t count){
    *TMR_CFG=count;
}

/**
 * Fault-Output Timer
 * 
 * This table shows how the fault-output timer's state and value vary by FCCU state and fault-output mode:
 * 
 * | FCCU state | Fault-Output Mode | Timer state            | Timer value                                                        |
 * |------------|-------------------|------------------------|--------------------------------------------------------------------|
 * | CONFIG     | Not Fault-Toggle  | Idle                   | 0000_0000h                                                         |
 * |            | Fault-Toggle      | Running or Idle         | Value when read or 0000_0000h                                      |
 * | NORMAL     | Not Fault-Toggle  | Idle                   | 0000_0000h                                                         |
 * |            | Fault-Toggle      | Running or Idle         | Value when read or 0000_0000h                                      |
 * | ALARM      | Not Fault-Toggle  | Idle                   | 0000_0000h                                                         |
 * |            | Fault-Toggle      | Running or Idle         | Value when read or 0000_0000h                                      |
 * | FAULT      | Not Fault-Toggle  | Running                 | Value when read; it is an up-counter that rolls back to zero after reaching maximum value and begins counting again. |
 * |            | Fault-Toggle      | Running or Idle         | Value when read or 0000_0000h                                      |
 */

uint32_t get_Fault_Output_Timer_Value(){
    return *TMR_ETMR;
}

void set_Fault_Output_Timer_Value(uint32_t count){
*TMR_ETMR=count;
}