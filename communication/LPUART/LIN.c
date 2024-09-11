#include "LIN.c"
#include <stdint.h>


//----------------------------------------------------

/*

Version ID (VERID)

indicates the version integrated for this instance on the chip and also specifies the inclusion and exclusion of several optional
features

*/


void set_VersionRegister(const VersionRegister *reg) {
    uint32_t regValue = (reg->major << 24) | (reg->minor << 16) | reg->feature;
    *VERID = regValue;
}


VersionRegister get_VersionRegister() {
    VersionRegister reg;
    uint32_t regValue = *VERID;
    reg.feature = regValue & 0xFFFF;
    reg.minor = (regValue >> 16) & 0xFF;
    reg.major = (regValue >> 24) & 0xFF;
    return reg;
}

//----------------------------------------------------------


parameter get_parameter(){
parameter pr;
pr.RXFIFO=((uint8_t)(*PARAM>>8 & 0xFF) );
pr.TXFIFO=((uint8_t)(*PARAM) & 0xFF);
return pr;
}

void set_parameter(parameter* pr){
(*PARAM)&=~(0xFFFF);//mask 
(*PARAM)|=(pr->RXFIFO<<8)|(pr->TXFIFO);
}


//-----------------------------------------------

//global 

/*

Performs global functions.

*/

uint8_t get_Global(){
return (uint8_t)(*GLOBAL & 0b10);
}

void set_Global(uint8_t gb){
*GLOBAL=(gb<<1);
}

//---------------------------------
//Pin Configuration
/*

    Enables the selection of input pins.


00b - Input trigger disabled
01b - Input trigger used instead of the RXD pin input
10b - Input trigger used instead of the CTS_B pin input
11b - Input trigger used to modulate the TXD pin output, which (after TXINV configuration) is
internally ANDed with the input trigger

*/

uint8_t get_Pin_Configuration(){
return (uint8_t)(*PINCFG & 0b11); 
}

void set_Pin_Configuration(uint8_t cfg){
*PINCFG &=~(0b11);
(*PINCFG)|=cfg;
}

//------------------------------
/*
Baud Rate (BAUD)
Configures the baud rate.
*/


BaudeConfig get_Baud_Rate_config() {
    BaudeConfig reg;
    uint32_t regValue = *PARAM; 
    reg.SBR       = regValue & 0x1FFF;             // Extract SBR (bits 12-0)
    reg.SBNS      = (regValue >> 13) & 0x1;        // Extract SBNS (bit 13)
    reg.RXEDGIE   = (regValue >> 14) & 0x1;        // Extract RXEDGIE (bit 14)
    reg.LBKDIE    = (regValue >> 15) & 0x1;        // Extract LBKDIE (bit 15)
    reg.RESYNCDIS = (regValue >> 16) & 0x1;        // Extract RESYNCDIS (bit 16)
    reg.BOTHEDGE  = (regValue >> 17) & 0x1;        // Extract BOTHEDGE (bit 17)
    reg.MATCFG    = (regValue >> 18) & 0x3;        // Extract MATCFG (bits 18-19)
    reg.RDMAE     = (regValue >> 21) & 0x1;        // Extract RDMAE (bit 21)
    reg.TDMAE     = (regValue >> 23) & 0x1;        // Extract TDMAE (bit 23)
    reg.OSR       = (regValue >> 24) & 0x1F;       // Extract OSR (bits 24-28)
    reg.M10       = (regValue >> 29) & 0x1;        // Extract M10 (bit 29)
    reg.MAEN2     = (regValue >> 30) & 0x1;        // Extract MAEN2 (bit 30)
    reg.MAEN1     = (regValue >> 31) & 0x1;        // Extract MAEN1 (bit 31)
    return reg;
}

void set_register_config(const BaudeConfig* reg) {
    uint32_t regValue = 0;
    regValue |= reg->SBR;                     // Set SBR (bits 12-0)
    regValue |= (reg->SBNS << 13);            // Set SBNS (bit 13)
    regValue |= (reg->RXEDGIE << 14);         // Set RXEDGIE (bit 14)
    regValue |= (reg->LBKDIE << 15);          // Set LBKDIE (bit 15)
    regValue |= (reg->RESYNCDIS << 16);       // Set RESYNCDIS (bit 16)
    regValue |= (reg->BOTHEDGE << 17);        // Set BOTHEDGE (bit 17)
    regValue |= (reg->MATCFG << 18);          // Set MATCFG (bits 18-19)
    regValue |= (reg->RDMAE << 21);           // Set RDMAE (bit 21)
    regValue |= (reg->TDMAE << 23);           // Set TDMAE (bit 23)
    regValue |= (reg->OSR << 24);             // Set OSR (bits 24-28)
    regValue |= (reg->M10 << 29);             // Set M10 (bit 29)
    regValue |= (reg->MAEN2 << 30);           // Set MAEN2 (bit 30)
    regValue |= (reg->MAEN1 << 31);           // Set MAEN1 (bit 31)
    *PARAM = regValue; // Write to the register
}

//-----------------------------------------------------------------

/*

Status (STAT)

Register Offset
STAT 14h

Function
Provides the module status.

*/

StatusRegister get_status_register(void) {
    StatusRegister sr;
    uint32_t reg_value = *STAT; // Read the STAT register value

    sr.LBKDIF   = (reg_value >> 31) & 0x1;
    sr.RXEDGIF  = (reg_value >> 30) & 0x1;
    sr.MSBF     = (reg_value >> 29) & 0x1;
    sr.RXINV    = (reg_value >> 28) & 0x1;
    sr.RWUID    = (reg_value >> 27) & 0x1;
    sr.BRK13    = (reg_value >> 26) & 0x1;
    sr.LBKDE    = (reg_value >> 25) & 0x1;
    sr.RAF      = (reg_value >> 24) & 0x1;
    sr.TDRE     = (reg_value >> 23) & 0x1;
    sr.TC       = (reg_value >> 22) & 0x1;
    sr.RDRF     = (reg_value >> 21) & 0x1;
    sr.IDLE     = (reg_value >> 20) & 0x1;
    sr.OR       = (reg_value >> 19) & 0x1;
    sr.NF       = (reg_value >> 18) & 0x1;
    sr.FE       = (reg_value >> 17) & 0x1;
    sr.PF       = (reg_value >> 16) & 0x1;
    sr.MA1F     = (reg_value >> 15) & 0x1;
    sr.MA2F     = (reg_value >> 14) & 0x1;
    sr.Reserved = (reg_value >> 9) & 0x1F; // Reserved bits (5 bits)
    sr.TSF      = (reg_value >> 9) & 0x1;
    sr.MSF      = (reg_value >> 8) & 0x1;
    sr.AME      = (reg_value >> 1) & 0x1;
    sr.LBKFE    = (reg_value >> 0) & 0x1;

    return sr;
}

void set_status_register(const StatusRegister* sr) {
    uint32_t reg_value = 0;

    reg_value |= (sr->LBKDIF   << 31);
    reg_value |= (sr->RXEDGIF  << 30);
    reg_value |= (sr->MSBF     << 29);
    reg_value |= (sr->RXINV    << 28);
    reg_value |= (sr->RWUID    << 27);
    reg_value |= (sr->BRK13    << 26);
    reg_value |= (sr->LBKDE    << 25);
    reg_value |= (sr->RAF      << 24);
    reg_value |= (sr->TDRE     << 23);
    reg_value |= (sr->TC       << 22);
    reg_value |= (sr->RDRF     << 21);
    reg_value |= (sr->IDLE     << 20);
    reg_value |= (sr->OR       << 19);
    reg_value |= (sr->NF       << 18);
    reg_value |= (sr->FE       << 17);
    reg_value |= (sr->PF       << 16);
    reg_value |= (sr->MA1F     << 15);
    reg_value |= (sr->MA2F     << 14);
    reg_value |= (sr->Reserved << 9);  // Reserved bits (5 bits)
    reg_value |= (sr->TSF      << 9);
    reg_value |= (sr->MSF      << 8);
    reg_value |= (sr->AME      << 1);
    reg_value |= (sr->LBKFE    << 0);

    *STAT = reg_value; // Write the value to the STAT register
}

//------------------------------------------------------

/*

Controls various optional features of the LPUART system.
You must write to the fields of this register only when both the transmitter and receiver are disabled.
*/


ControlConfig get_ControlConfig() {
    ControlConfig cfg;
    uint32_t regValue = *CTRL; // Read the entire register value

    // Extract fields using bit masks and shifts
    cfg.R8T9      = (regValue >> 31) & 0x01;
    cfg.R9T8      = (regValue >> 30) & 0x01;
    cfg.TXDIR     = (regValue >> 29) & 0x01;
    cfg.TXINV     = (regValue >> 28) & 0x01;
    cfg.ORIE      = (regValue >> 27) & 0x01;
    cfg.NEIE      = (regValue >> 26) & 0x01;
    cfg.FEIE      = (regValue >> 25) & 0x01;
    cfg.PEIE      = (regValue >> 24) & 0x01;
    cfg.TIE       = (regValue >> 23) & 0x01;
    cfg.TCIE      = (regValue >> 22) & 0x01;
    cfg.RIE       = (regValue >> 21) & 0x01;
    cfg.ILIE      = (regValue >> 20) & 0x01;
    cfg.TE        = (regValue >> 19) & 0x01;
    cfg.RE        = (regValue >> 18) & 0x01;
    cfg.RWU       = (regValue >> 17) & 0x01;
    cfg.SBK       = (regValue >> 16) & 0x01;
    cfg.MA1IE     = (regValue >> 15) & 0x01;
    cfg.MA2IE     = (regValue >> 14) & 0x01;
    cfg.Reserved1 = (regValue >> 9)  & 0x07;
    cfg.M7        = (regValue >> 11) & 0x01;
    cfg.IDLECFG   = (regValue >> 8)  & 0x07;
    cfg.LOOPS     = (regValue >> 7)  & 0x01;
    cfg.DOZEEN    = (regValue >> 6)  & 0x01;
    cfg.RSRC      = (regValue >> 5)  & 0x01;
    cfg.M         = (regValue >> 4)  & 0x01;
    cfg.WAKE      = (regValue >> 3)  & 0x01;
    cfg.ILT       = (regValue >> 2)  & 0x01;
    cfg.PE        = (regValue >> 1)  & 0x01;
    cfg.PT        = (regValue >> 0)  & 0x01;

    return cfg;
}


void set_ControlConfig(const ControlConfig* cfg) {
    uint32_t regValue = 0;

    // Set fields using bit masks and shifts
    regValue |= (cfg->R8T9      << 31);
    regValue |= (cfg->R9T8      << 30);
    regValue |= (cfg->TXDIR     << 29);
    regValue |= (cfg->TXINV     << 28);
    regValue |= (cfg->ORIE      << 27);
    regValue |= (cfg->NEIE      << 26);
    regValue |= (cfg->FEIE      << 25);
    regValue |= (cfg->PEIE      << 24);
    regValue |= (cfg->TIE       << 23);
    regValue |= (cfg->TCIE      << 22);
    regValue |= (cfg->RIE       << 21);
    regValue |= (cfg->ILIE      << 20);
    regValue |= (cfg->TE        << 19);
    regValue |= (cfg->RE        << 18);
    regValue |= (cfg->RWU       << 17);
    regValue |= (cfg->SBK       << 16);
    regValue |= (cfg->MA1IE     << 15);
    regValue |= (cfg->MA2IE     << 14);
    regValue |= (cfg->Reserved1 << 9);  // Reserved bits (set as needed)
    regValue |= (cfg->M7        << 11);
    regValue |= (cfg->IDLECFG   << 8);
    regValue |= (cfg->LOOPS     << 7);
    regValue |= (cfg->DOZEEN    << 6);
    regValue |= (cfg->RSRC      << 5);
    regValue |= (cfg->M         << 4);
    regValue |= (cfg->WAKE      << 3);
    regValue |= (cfg->ILT       << 2);
    regValue |= (cfg->PE        << 1);
    regValue |= (cfg->PT        << 0);

    *CTRL = regValue; // Write the updated value to the register
}



//----------------------------------------------------


/*

Data (DATA)
Register Offset
DATA 1Ch
Function
Supports 8-bit, 16-bit, or 32-bit writes, each type of write performing a separate function. An 8-bit write to DATA[7:0] pushes
{CTRL[R8T9], CTRL[R9T8], DATA[7:0]} the transmit FIFO with TSC clear. A 16-bit or 32-bit write pushes the data written into the
FIFO and does not update the value of CTRL[R8T9] or CTRL[R9T8].
Reads and writes of this register are also involved in the automatic flag clearing mechanisms for some of the LPUART status fields.

*/

DATA_cfg get_StatusRegister() {
    DATA_cfg status;
    uint32_t regValue = *DATA; // Read the entire register value

    status.NOISY    = (regValue >> 15) & 0x01;
    status.PARITYE  = (regValue >> 14) & 0x01;
    status.FRETSC   = (regValue >> 13) & 0x01;
    status.RXEMPT   = (regValue >> 12) & 0x01;
    status.IDLINE   = (regValue >> 11) & 0x01;
    status.LINBRK   = (regValue >> 10) & 0x01;
    status.R9T9     = (regValue >> 9)  & 0x01;
    status.R8T8     = (regValue >> 8)  & 0x01;
    status.R7T7     = (regValue >> 7)  & 0x01;
    status.R6T6     = (regValue >> 6)  & 0x01;
    status.R5T5     = (regValue >> 5)  & 0x01;
    status.R4T4     = (regValue >> 4)  & 0x01;
    status.R3T3     = (regValue >> 3)  & 0x01;
    status.R2T2     = (regValue >> 2)  & 0x01;
    status.R1T1     = (regValue >> 1)  & 0x01;
    status.R0T0     = (regValue >> 0)  & 0x01;

    return status;
}

void set_StatusRegister(const DATA_cfg* status) {
    uint16_t regValue = 0;

    regValue |= (status->NOISY    << 15);
    regValue |= (status->PARITYE  << 14);
    regValue |= (status->FRETSC   << 13);
    regValue |= (status->RXEMPT   << 12);
    regValue |= (status->IDLINE   << 11);
    regValue |= (status->LINBRK   << 10);
    regValue |= (status->R9T9     << 9);
    regValue |= (status->R8T8     << 8);
    regValue |= (status->R7T7     << 7);
    regValue |= (status->R6T6     << 6);
    regValue |= (status->R5T5     << 5);
    regValue |= (status->R4T4     << 4);
    regValue |= (status->R3T3     << 3);
    regValue |= (status->R2T2     << 2);
    regValue |= (status->R1T1     << 1);
    regValue |= (status->R0T0     << 0);

    *DATA = regValue; // Write the updated value to the register
}

//----------------------------------------------------

/*


Match Address (MATCH)
Register Offset
MATCH 20h
Function
Provides addresses for address matching during the receiver operation.

*/

MatchAddressRegister getMatchAddressRegister() {
    MatchAddressRegister reg;
    reg.MA1 = MATCH->MA1;
    reg.MA2 = MATCH->MA2;
    return reg;
}

void setMatchAddressRegister(MatchAddressRegister* reg) {
    (*MATCH) &=~0x3FF ;
    (*MATCH) &=~0x3FF<<16;

    (*MATCH) |= (reg->MA1 & 0x3FF) | ((reg->MA2 & 0x3FF) << 16);

    }

    //----------------------------

    /*
    
    MODEM IrDA (MODIR)
Offset
Register Offset
MODIR 24h
Function
Controls options for setting the MODEM configuration.
    
    */



Setting_MODEM get_Setting_MODEM() {
    Setting_MODEM reg;
    uint32_t regValue = *MODIR; 
    reg.TXCTSE   = (regValue >> 0) & 0x01; // Extract bit 0
    reg.TXRTSE   = (regValue >> 1) & 0x01; // Extract bit 1
    reg.TXRTSPOL = (regValue >> 2) & 0x01; // Extract bit 2
    reg.RXRTSE   = (regValue >> 3) & 0x01; // Extract bit 3
    reg.TXCTSC   = (regValue >> 4) & 0x01; // Extract bit 4
    reg.TXCTSSRC = (regValue >> 5) & 0x01; // Extract bit 5
    reg.Reserved = (regValue >> 6) & 0x03; // Extract bits 7-6
    reg.RTSWATER = (regValue >> 8) & 0x0F; // Extract bits 11-8
    reg.TNP      = (regValue >> 16) & 0x03; // Extract bits 17-16
    reg.IREN     = (regValue >> 18) & 0x01; // Extract bit 18

    return reg;
}


void set_Setting_MODEM(Setting_MODEM* reg) {
    uint32_t regValue = 0;

    regValue |= (reg->TXCTSE   & 0x01) << 0;   // Set bit 0
    regValue |= (reg->TXRTSE   & 0x01) << 1;   // Set bit 1
    regValue |= (reg->TXRTSPOL & 0x01) << 2;   // Set bit 2
    regValue |= (reg->RXRTSE   & 0x01) << 3;   // Set bit 3
    regValue |= (reg->TXCTSC   & 0x01) << 4;   // Set bit 4
    regValue |= (reg->TXCTSSRC & 0x01) << 5;   // Set bit 5
    regValue |= (reg->Reserved & 0x03) << 6;   // Set bits 7-6
    regValue |= (reg->RTSWATER & 0x0F) << 8;   // Set bits 11-8
    regValue |= (reg->TNP      & 0x03) << 16;  // Set bits 17-16
    regValue |= (reg->IREN     & 0x01) << 18;  // Set bit 18

    *MODIR = regValue; 
}


//----------------------------------------------------------


/*
FIFO (FIFO)
Offset
Register Offset
FIFO 28h
Function
Provides you the ability to turn on and turn off the FIFO functionality.
This register also provides you the size of the FIFO that has been implemented. You can read this register at any time and must
write to it only when CTRL[RE] and CTRL[TE] are 0 and the FIFO is empty.

*/


FIFORegister getFIFORegister() {
    FIFORegister reg;
    uint32_t regValue = *FIFO; 

    reg.RXFIFOSIZE = (regValue >> 0) & 0x07; // Extract bits 2-0
    reg.RXFE       = (regValue >> 3) & 0x01; // Extract bit 3
    reg.TXFIFOSIZE = (regValue >> 4) & 0x07; // Extract bits 6-4
    reg.TXFE       = (regValue >> 7) & 0x01; // Extract bit 7
    reg.RXUFE      = (regValue >> 8) & 0x01; // Extract bit 8
    reg.TXOFE      = (regValue >> 9) & 0x01; // Extract bit 9
    reg.RXIDEN     = (regValue >> 10) & 0x07; // Extract bits 12-10
    reg.RXFLUSH    = (regValue >> 14) & 0x01; // Extract bit 14
    reg.TXFLUSH    = (regValue >> 15) & 0x01; // Extract bit 15
    reg.RXUF       = (regValue >> 16) & 0x01; // Extract bit 16
    reg.TXOF       = (regValue >> 17) & 0x01; // Extract bit 17
    reg.RXEMPT     = (regValue >> 22) & 0x01; // Extract bit 22
    reg.TXEMPT     = (regValue >> 23) & 0x01; // Extract bit 23

    return reg;
}

FIFORegister getFIFORegister() {
    FIFORegister reg;
    uint32_t regValue = *FIFO;

    reg.RXFIFOSIZE = (regValue >> 0) & 0x07; // Extract bits 2-0
    reg.RXFE       = (regValue >> 3) & 0x01; // Extract bit 3
    reg.TXFIFOSIZE = (regValue >> 4) & 0x07; // Extract bits 6-4
    reg.TXFE       = (regValue >> 7) & 0x01; // Extract bit 7
    reg.RXUFE      = (regValue >> 8) & 0x01; // Extract bit 8
    reg.TXOFE      = (regValue >> 9) & 0x01; // Extract bit 9
    reg.RXIDEN     = (regValue >> 10) & 0x07; // Extract bits 12-10
    reg.RXFLUSH    = (regValue >> 14) & 0x01; // Extract bit 14
    reg.TXFLUSH    = (regValue >> 15) & 0x01; // Extract bit 15
    reg.RXUF       = (regValue >> 16) & 0x01; // Extract bit 16
    reg.TXOF       = (regValue >> 17) & 0x01; // Extract bit 17
    reg.RXEMPT     = (regValue >> 22) & 0x01; // Extract bit 22
    reg.TXEMPT     = (regValue >> 23) & 0x01; // Extract bit 23

    return reg;
}


//---------------------------------------------

/*

Watermark (WATER)
Offset
Register Offset
WATER 2Ch

Function
Provides the ability to set a programmable threshold for notification, or sets the programmable thresholds to indicate that transmit
data can be written or receive data can be read.
You may read this register at any time but must write to it only when CTRL[TE] is 0.

*/

WatermarkCounterRegister getWatermarkCounterRegister() {
    WatermarkCounterRegister reg;
    uint32_t regValue = *WATER; 

    reg.TXWATER = (regValue >> 0) & 0x0F;   // Extract bits 3-0
    reg.TXCOUNT = (regValue >> 8) & 0x1F;   // Extract bits 12-8
    reg.RXWATER = (regValue >> 16) & 0x0F;  // Extract bits 19-16
    reg.RXCOUNT = (regValue >> 24) & 0x0F;  // Extract bits 28-24

    return reg;
}

void setWatermarkCounterRegister(WatermarkCounterRegister* reg) {
    uint32_t regValue = 0;

    regValue |= (reg->TXWATER & 0x0F) << 0;   // Set bits 3-0
    regValue |= (reg->TXCOUNT & 0x1F) << 8;   // Set bits 12-8
    regValue |= (reg->RXWATER & 0x0F) << 16;  // Set bits 19-16
    regValue |= (reg->RXCOUNT & 0x0F) << 24;  // Set bits 28-24

    *WATER = regValue;
}

//----------------------------------------------

/*
Data Read-Only (DATARO)
Offset
Register Offset
DATARO 30h
Function
Indicates the first entry in the receive FIFO, but does not pull data from the FIFO.
*/

uint16_t get_Data_Read_Only(){
    return (uint16_t)(*DATARO);
}

//--------------------------------------------

/*

MODEM Control (MCR)
Offset
Register Offset
MCR 40h
Function
Controls the operation of the MODEM pins.


*/

MODEM_Control get_MODEM_Control() {
    MODEM_Control reg;
    uint32_t regValue = *MCR;
    reg.CTS = (regValue >> 0) & 0x01;  // Extract bit 0
    reg.DSR = (regValue >> 1) & 0x01;  // Extract bit 1
    reg.RIN = (regValue >> 2) & 0x01;  // Extract bit 2
    reg.DCD = (regValue >> 3) & 0x01;  // Extract bit 3
    reg.DTR = (regValue >> 8) & 0x01;  // Extract bit 8
    reg.RTS = (regValue >> 9) & 0x01;  // Extract bit 9

    return reg;
}

void set_MODEM_Control(MODEM_Control* reg){
    uint32_t regValue = 0;

    regValue |= (reg->CTS & 0x01) << 0;  // Set bit 0
    regValue |= (reg->DSR & 0x01) << 1;  // Set bit 1
    regValue |= (reg->RIN & 0x01) << 2;  // Set bit 2
    regValue |= (reg->DCD & 0x01) << 3;  // Set bit 3
    regValue |= (reg->DTR & 0x01) << 8;  // Set bit 8
    regValue |= (reg->RTS & 0x01) << 9;  // Set bit 9

    *MCR = regValue; 
}


//-------------------------------------------------

/*

MODEM Status (MSR)
Offset
Register Offset
MSR 44h

indicates the status of the MODEM pins.
*/


MODEM_Status get_MODEM_Status() {
    MODEM_Status reg;
    uint32_t regValue = *MSR; 

    reg.DCTS = (regValue >> 0) & 0x01;  // Extract bit 0
    reg.DDSR = (regValue >> 1) & 0x01;  // Extract bit 1
    reg.DRI  = (regValue >> 2) & 0x01;  // Extract bit 2
    reg.DDCD = (regValue >> 3) & 0x01;  // Extract bit 3
    reg.CTS  = (regValue >> 4) & 0x01;  // Extract bit 4
    reg.DSR  = (regValue >> 5) & 0x01;  // Extract bit 5
    reg.RIN  = (regValue >> 6) & 0x01;  // Extract bit 6
    reg.DCD  = (regValue >> 7) & 0x01;  // Extract bit 7

    return reg;
}

void set_MODEM_Status(MODEM_Status* reg) {
    uint32_t regValue = 0;

    regValue |= (reg->DCTS & 0x01) << 0;  // Set bit 0
    regValue |= (reg->DDSR & 0x01) << 1;  // Set bit 1
    regValue |= (reg->DRI  & 0x01) << 2;  // Set bit 2
    regValue |= (reg->DDCD & 0x01) << 3;  // Set bit 3
    regValue |= (reg->CTS  & 0x01) << 4;  // Set bit 4
    regValue |= (reg->DSR  & 0x01) << 5;  // Set bit 5
    regValue |= (reg->RIN  & 0x01) << 6;  // Set bit 6
    regValue |= (reg->DCD  & 0x01) << 7;  // Set bit 7

    *MSR = regValue; 
}

//-----------------------------------------
/*

Receiver Extended Idle (REIR)
Offset
Register Offset
REIR 48h
Function
Configures the receiver extended idle functionality. You must not change this value when the receiver is enabled.

*/

uint16_t get_Receiver_Extended_Idle(){
return (uint16_t)(*REIR & 0x3FFF);
}

void set_Receiver_Extended_Idle(uint16_t IDTIME){
(*REIR)&=~(0x3FFF);
*REIR|=IDTIME;
}

//------------------------------------------------------

/*

Transmitter Extended Idle (TEIR)
Offset
Register Offset
TEIR 4Ch
Function
Configures the transmitter extended idle functionality. You must not change this value when the transmitter is enabled


*/

uint16_t get_Transmitter_Extended_Idle(){
return (uint16_t)(*TEIR & 0x3FFF);
}

void set_Transmitter_Extended_Idle(uint16_t IDTIME){
(*TEIR)&=~(0x3FFF);
*TEIR|=IDTIME;
}

//-------------------------------------------------
/*

Half Duplex Control (HDCR)
Offset
Register Offset
HDCR 50h
Function
Provides control for half-duplex-related operations.
You can use this register instead of CTRL[LOOPS], CTRL[RSRC], and CTRL[TXDIR] functions, although you can use
CTRL[LOOPS] to loop-back the transmitter outputs to the receiver.
*/


Half_Duplex_Control get_Half_Duplex_Control() {
    Half_Duplex_Control reg;
    uint32_t regValue = *HDCR;

    reg.TXSTALL   = (regValue >> 0) & 0x01;  // Extract bit 0
    reg.RXSEL     = (regValue >> 1) & 0x01;  // Extract bit 1
    reg.RXWRMSK   = (regValue >> 2) & 0x01;  // Extract bit 2
    reg.RXMSK     = (regValue >> 3) & 0x01;  // Extract bit 3
    reg.RTSEXT    = (regValue >> 8) & 0xFF;  // Extract bits 15-8

    return reg;
}

void set_Half_Duplex_Control(Half_Duplex_Control* reg) {
    uint32_t regValue = 0;

    regValue |= (reg->TXSTALL   & 0x01) << 0;  // Set bit 0
    regValue |= (reg->RXSEL     & 0x01) << 1;  // Set bit 1
    regValue |= (reg->RXWRMSK   & 0x01) << 2;  // Set bit 2
    regValue |= (reg->RXMSK     & 0x01) << 3;  // Set bit 3
    regValue |= (reg->RTSEXT    & 0xFF) << 8;  // Set bits 15-8

    *HDCR = regValue; 
}

//---------------------------------------

/*
Timeout Control (TOCR)
Offset
Register Offset
TOCR 58h
Function
Configures the behavior of the timeout logic. Timeouts 0 and 1 are used to monitor the receiver and timeouts 2 and 3 are used to
monitor the transmitter.
*/

TimeoutControl getTimeoutControl() {
    TimeoutControl reg;
    uint32_t regValue = *TOCR; 

    reg.TOEN = (regValue >> 0) & 0x0F;  // Extract bits 3-0
    reg.TOIE = (regValue >> 8) & 0x0F;  // Extract bits 11-8

    return reg;
}

void setTimeoutControl(const TimeoutControl* reg) {
    uint32_t regValue = 0;

    regValue |= (reg->TOEN & 0x0F) << 0;  // Set bits 3-0
    regValue |= (reg->TOIE & 0x0F) << 8;  // Set bits 11-8

    *TOCR = regValue;
}


//----------------------------------------

/*
imeout Status (TOSR)
Offset
Register Offset
TOSR 5Ch
Function
Indicates the status of the timeout logic. Timeouts 0 and 1 are used to monitor the receiver and timeouts 2 and 3 are used to
monitor the transmitter.

*/


TimeoutStatus getTimeoutStatus() {
    TimeoutStatus reg;
    uint32_t regValue = *TOSR; 

    reg.TOZ = (regValue >> 0) & 0x0F;  // Extract bits 3-0
    reg.TOF = (regValue >> 8) & 0x0F;  // Extract bits 11-8

    return reg;
}

void setTimeoutStatus(const TimeoutStatus* reg) {
    uint32_t regValue = 0;

    // Construct the register value
    regValue |= (reg->TOZ & 0x0F) << 0;  // Set bits 3-0
    regValue |= (reg->TOF & 0x0F) << 8;  // Set bits 11-8

    *TOSR = regValue;
}

//-------------------------------------------

/*
 * Timeout Registers (TIMEOUT0 - TIMEOUT3)
 * ----------------------------------------
 * Offset Register:
 * - TIMEOUT0: 60h
 * - TIMEOUT1: 64h
 * - TIMEOUT2: 68h
 * - TIMEOUT3: 6Ch
 *
 * Function:
 * - Configures the corresponding timeout counter and status field.
 * - TIMEOUT0 and TIMEOUT1 are used to monitor the receiver.
 * - TIMEOUT2 and TIMEOUT3 are used to monitor the transmitter.
 *
 * Note:
 * - You must write to these registers only when the corresponding timeout is disabled or when the value of the corresponding
 *   timeout field is 1.
 */

Timeout getTimeout0() {
    Timeout reg;
    uint32_t regValue = *TIMEOUT0; 

    reg.TIMEOUT = (regValue >> 0) & 0x3FFF;  // Extract bits 13-0
    reg.CFG = (regValue >> 30) & 0x03;       // Extract bits 31-30

    return reg;
}

void setTimeout0(const Timeout* reg) {
    uint32_t regValue = 0;

    // Construct the register value
    regValue |= (reg->TIMEOUT & 0x3FFF) << 0;  // Set bits 13-0
    regValue |= (reg->CFG & 0x03) << 30;       // Set bits 31-30

    *TIMEOUT0 = regValue; 
}
 //--------------------

Timeout getTimeout1() {
    Timeout reg;
    uint32_t regValue = *TIMEOUT1; 

    reg.TIMEOUT = (regValue >> 0) & 0x3FFF;  // Extract bits 13-0
    reg.CFG = (regValue >> 30) & 0x03;       // Extract bits 31-30

    return reg;
}

void setTimeout1(const Timeout* reg) {
    uint32_t regValue = 0;

    // Construct the register value
    regValue |= (reg->TIMEOUT & 0x3FFF) << 0;  // Set bits 13-0
    regValue |= (reg->CFG & 0x03) << 30;       // Set bits 31-30

    *TIMEOUT1 = regValue; 
}

//--------------------------


Timeout getTimeout2() {
    Timeout reg;
    uint32_t regValue = *TIMEOUT2; 

    reg.TIMEOUT = (regValue >> 0) & 0x3FFF;  // Extract bits 13-0
    reg.CFG = (regValue >> 30) & 0x03;       // Extract bits 31-30

    return reg;
}

void setTimeout2(const Timeout* reg) {
    uint32_t regValue = 0;

    // Construct the register value
    regValue |= (reg->TIMEOUT & 0x3FFF) << 0;  // Set bits 13-0
    regValue |= (reg->CFG & 0x03) << 30;       // Set bits 31-30

    *TIMEOUT2 = regValue; 
}

//-------------------------------------

Timeout getTimeout3() {
    Timeout reg;
    uint32_t regValue = *TIMEOUT3; 

    reg.TIMEOUT = (regValue >> 0) & 0x3FFF;  // Extract bits 13-0
    reg.CFG = (regValue >> 30) & 0x03;       // Extract bits 31-30

    return reg;
}

void setTimeout3(const Timeout* reg) {
    uint32_t regValue = 0;

    // Construct the register value
    regValue |= (reg->TIMEOUT & 0x3FFF) << 0;  // Set bits 13-0
    regValue |= (reg->CFG & 0x03) << 30;       // Set bits 31-30

    *TIMEOUT3 = regValue; 
}


//-------------------------------------------------

/*
ransmit Command Burst (TCBR0 - TCBR127)
Offset
For a = 0 to 127:
Register Offset
TCBRa 200h + (a × 4h)
Function
Acts as an alias of Data (DATA), designed to support incrementing burst transfers to the transmit FIFO by a DMA controller, using
aligned 8-bit, 16-bit, or 32-bit writes. The size of this register is 512 bytes:
• An aligned 32-bit write in this region pushes one entry into the transmit FIFO.
• An aligned 16-bit write in this region to TCBR
x[15:0] pushes one entry into the transmit FIFO.
• An 8-bit write in this region to TCBR
x[7:0] updates DATA[7:0], but does not push the data into the transmit FIFO.
• An 8-bit write in this region to TCBR
x[15:8] pushes the data written to DATA[15:8] plus the previously written DATA[7:0] into
the transmit FIFO.
• An 8-bit or 16-bit write in this region to TXBR
x[31:16] is ignored
*/

void set_Transmit_Command_Burst(uint8_t n,uint16_t data){
(*(TCBR(n)))&=~(0xFFFF);
(*(TCBR(n)))|=data;
}

//------------------------------
/*

Transmit Data Burst (TDBR0 - TDBR255)
Offset
For a = 0 to 255:
Register Offset
TDBRa 400h + (a × 4h)
Function
Acts as an alias of Data (DATA), designed to support incrementing burst transfers to the transmit FIFO by a DMA controller using
8-bit, 16-bit, or 32-bit writes. The size of this register is 1024 bytes:
• An aligned 32-bit write in this region pushes four DATA byte entries into the transmit FIFO (DATA0 byte first). The register
access is extended by three wait states.
• An aligned 16-bit write in this region to either half of a 32-bit word pushes two DATA byte entries into the transmit FIFO (DATA0
or DATA2 first). The register access is extended by one wait state.
• An 8-bit write in this region pushes one DATA byte entry into the transmit FIFO.
Byte writes to Data (DATA) use the contents of CTRL[R9T8] for the ninth data bit, CTRL[R8T9] for the tenth data bit, and zero
extend DATA[FRETSC].*/


void set_transmit_Data_Burs(uint8_t n,data_burs* reg){
    uint32_t regValue = 0;

    // Construct the register value
    regValue |= (reg->DATA3 & 0xFF) << 24; // Set bits 31-24
    regValue |= (reg->DATA2 & 0xFF) << 16; // Set bits 23-16
    regValue |= (reg->DATA1 & 0xFF) << 8;  // Set bits 15-8
    regValue |= (reg->DATA0 & 0xFF) << 0;  // Set bits 7-0

    *(TDBR(n)) = regValue; 
}
