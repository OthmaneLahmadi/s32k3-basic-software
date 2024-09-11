#include "CAN.h"
#include <stdint.h>


CAN_config get_Module_Configuration() {
    uint32_t regValue = *MCR; // Read the value from the MCR register
    CAN_config  config;
    config.MDIS       = (regValue >> 31) & 0x01;
    config.FRZ        = (regValue >> 30) & 0x01;
    config.RFEN       = (regValue >> 29) & 0x01;
    config.HALT       = (regValue >> 28) & 0x01;
    config.NOTRDY     = (regValue >> 27) & 0x01;
    config.SOFTRST    = (regValue >> 25) & 0x01;
    config.FRZACK     = (regValue >> 24) & 0x01;
    config.SUPV       = (regValue >> 23) & 0x01;
    config.WRNEN      = (regValue >> 21) & 0x01;
    config.LPMACK     = (regValue >> 20) & 0x01;
    config.SRXDIS     = (regValue >> 17) & 0x01;
    config.IRMQ       = (regValue >> 16) & 0x01;
    config.DMA        = (regValue >> 15) & 0x01;
    config.LPRIOEN    = (regValue >> 13) & 0x01;
    config.AEN        = (regValue >> 12) & 0x01;
    config.FDEN       = (regValue >> 11) & 0x01;
    config.IDAM       = (regValue >> 8) & 0x03;
    config.MAXMB      = (regValue >> 0) & 0x7F;
    return config;
}


void set_Module_Configuration(const CAN_config* config) {
    uint32_t regValue = 0;

    regValue |= (config->MDIS       & 0x01) << 31;
    regValue |= (config->FRZ        & 0x01) << 30;
    regValue |= (config->RFEN       & 0x01) << 29;
    regValue |= (config->HALT       & 0x01) << 28;
    regValue |= (config->NOTRDY     & 0x01) << 27;
    regValue |= (config->SOFTRST    & 0x01) << 25;
    regValue |= (config->FRZACK     & 0x01) << 24;
    regValue |= (config->SUPV       & 0x01) << 23;
    regValue |= (config->WRNEN      & 0x01) << 21;
    regValue |= (config->LPMACK     & 0x01) << 20;
    regValue |= (config->SRXDIS     & 0x01) << 17;
    regValue |= (config->IRMQ       & 0x01) << 16;
    regValue |= (config->DMA        & 0x01) << 15;
    regValue |= (config->LPRIOEN    & 0x01) << 13;
    regValue |= (config->AEN        & 0x01) << 12;
    regValue |= (config->FDEN       & 0x01) << 11;
    regValue |= (config->IDAM       & 0x03) << 8;
    regValue |= (config->MAXMB      & 0x7F) << 0;

    *MCR = regValue; // Write the value to the MCR register
}

//-----------------------------------------------------------------------------

/*Contains specific FlexCAN control features related to the CAN bus. These features include bit rate, programmable sampling point
within an RX bit, Loopback mode, Listen-Only mode, Bus Off recovery behavior, and interrupt enabling (Bus-Off, Error, Warning).
It also determines the division factor for the clock prescaler.
The CAN bit timing variables (CTRL1[PRESDIV], CTRL1[PROPSEG], CTRL1[PSEG1], CTRL1[PSEG2], and CTRL1[RJW]) can
also be configured in CAN Bit Timing (CBT), which extends the range of all these variables. If CBT[BTF] = 1, CTRL1[PRESDIV],
CTRL1[PROPSEG], CTRL1[PSEG1], CTRL1[PSEG2], and CTRL1[RJW] become read-only.
If CTRL2[BTE] = 1, CTRL1[PRESDIV], CTRL1[PROPSEG], CTRL1[PSEG1], CTRL1[PSEG2], and CTRL1[RJW] are not used by
the module. Instead, these fields are read as zero, and a write operation to them has no effect.*/


CAN_Control get_CAN_Control() {
    uint32_t reg_value = *CTRL1;
    CAN_Control control;
    control.PRESDIV = (reg_value >> 24) & 0xFF;   // Extract 31-24 bits
    control.RJW = (reg_value >> 22) & 0x03;       // Extract 23-22 bits
    control.PSEG1 = (reg_value >> 19) & 0x07;     // Extract 21-19 bits
    control.PSEG2 = (reg_value >> 16) & 0x07;     // Extract 18-16 bits
    control.BOFFMSK = (reg_value >> 15) & 0x01;   // Extract 15 bit
    control.ERRMSK = (reg_value >> 14) & 0x01;    // Extract 14 bit
    control.LPB = (reg_value >> 12) & 0x01;       // Extract 12 bit
    control.TWRNMSK = (reg_value >> 11) & 0x01;   // Extract 11 bit
    control.RWRNMSK = (reg_value >> 10) & 0x01;   // Extract 10 bit
    control.SMP = (reg_value >> 7) & 0x01;        // Extract 7 bit
    control.BOFFREC = (reg_value >> 6) & 0x01;    // Extract 6 bit
    control.TSYN = (reg_value >> 5) & 0x01;       // Extract 5 bit
    control.LBUF = (reg_value >> 4) & 0x01;       // Extract 4 bit
    control.LOM = (reg_value >> 3) & 0x01;        // Extract 3 bit
    control.PROPSEG = reg_value & 0x07;           // Extract 2-0 bits
    return control;
}

void set_CAN_Control(const CAN_Control *control) {
    uint32_t reg_value = 0;

    reg_value |= (control->PRESDIV & 0xFF) << 24; // Set 31-24 bits
    reg_value |= (control->RJW & 0x03) << 22;     // Set 23-22 bits
    reg_value |= (control->PSEG1 & 0x07) << 19;   // Set 21-19 bits
    reg_value |= (control->PSEG2 & 0x07) << 16;   // Set 18-16 bits
    reg_value |= (control->BOFFMSK & 0x01) << 15; // Set 15 bit
    reg_value |= (control->ERRMSK & 0x01) << 14;  // Set 14 bit
    reg_value |= (control->LPB & 0x01) << 12;     // Set 12 bit
    reg_value |= (control->TWRNMSK & 0x01) << 11; // Set 11 bit
    reg_value |= (control->RWRNMSK & 0x01) << 10; // Set 10 bit
    reg_value |= (control->SMP & 0x01) << 7;      // Set 7 bit
    reg_value |= (control->BOFFREC & 0x01) << 6;  // Set 6 bit
    reg_value |= (control->TSYN & 0x01) << 5;     // Set 5 bit
    reg_value |= (control->LBUF & 0x01) << 4;     // Set 4 bit
    reg_value |= (control->LOM & 0x01) << 3;      // Set 3 bit
    reg_value |= (control->PROPSEG & 0x07);       // Set 2-0 bits

    *CTRL1 = reg_value;
}

//-------------------------------------------------------------------------

/*Represents a 16-bit free-running counter that the CPU can read and write. The timer starts from 0h after reset, counts linearly to
FFFFh, and wraps around.
When CTRL2[TIMER_SRC] = 1, an external time tick continuously increments the timer. The time tick must be synchronous to
the peripheral clock, with a minimum pulse width of one clock cycle.
When CTRL2[TIMER_SRC] = 0, the CAN bit clock increments the timer, which defines the baud rate on the CAN bus. During a
message transmission or reception, it increments by one for each bit that is received or transmitted. When there is no message
on the bus, it counts using the previously programmed baud rate. The timer is not incremented during Disable and Freeze modes.
The timer value is captured when the second bit of the identifier field of any frame is on the CAN bus. This captured value is written
into the timestamp entry in a message buffer after a successful reception or transmission of a message.
If CTRL1[TSYN] = 1, the timer is reset whenever a message is received in the first available message buffer, according
to CTRL2[RFFN].
The CPU can write to this register anytime. However, if the write occurs simultaneously with the timer being reset by a reception
in the first message buffer, the write value is discarded.*/

uint16_t get_Free_Running_Timer(){
return (uint16_t)(*TIMER & 0xFFFF);
}

void set_Free_Running_Timer(uint16_t time){
(*TIMER)&=~(0xFFFF);
(*TIMER)|=time;
}


//-------------------------------------------------------------------------------------

/*
Masks the filter bits of all RX message buffers, excluding MB14 and MB15, which have individual mask registers.
This register is located in RAM.
RXMGMASK is provided for legacy application support.
• When MCR[IRMQ] is 0, RXMGMASK is always in effect. The bits in RXMGMASK[MG] mask the MB filter bits.
• When MCR[IRMQ] is 1, RXMGMASK has no effect. The bits in RXMGMASK[MG] do not mask the MB filter bits.
This register can only be written in Freeze mode; the module blocks it in other modes.*/



uint32_t get_RX_Message_Buffers_Global_Mask(){
return *RXMGMASK;
}

void set_RX_Message_Buffers_Global_Mask(uint32_t MG){
*RXMGMASK=MG;
}


//----------------------------------------------------------------------------------------------------

/*Masks the filter fields of MB14.
This register is located in RAM.
RX14MASK is provided for legacy application support. When MCR[IRMQ] = 1, RX14MASK has no effect.
This register can only be programmed when the module is in Freeze mode; the module blocks it in other modes*/

uint32_t get_Receive_14_Mask(){
return *RX14MASK;
}

void set_Receive_14_Mask(uint32_t RX14){
*RX14MASK=RX14;
}

//------------------------------------------------------------------------------------------

/*

Masks the filter fields of MB15.
This register is located in RAM.
RX15MASK is provided for legacy application support. When MCR[IRMQ] = 1, RX15MASK has no effect.
This register can be programmed only when the module is in Freeze mode; the module blocks it in other modes.

*/

uint32_t get_Receive_15_Mask(){
return *RX15MASK;
}

void set_Receive_15_Mask(uint32_t RX15){
*RX15MASK=RX15;
}


//--------------------------------------------------------

/*Error Counter
Contains error counters for received and transmitted messages.
TXERRCNT and RXERRCNT consider all errors in both CAN FD and non-FD message formats. TXERRCNT_FAST and
RXERRCNT_FAST count only the errors that occur in the data phase of CAN FD frames that have BRS = 1.
The Fault Confinement state (ESR1[FLTCONF]) is updated based on TXERRCNT and RXERRCNT counters only. The rules for
increasing and decreasing these counters are described in the CAN protocol and are entirely implemented in FlexCAN.

*/

void set_CAN_Error_Counters(const CAN_Error_Counters *counters) {
    uint16_t reg_value = 0;
    reg_value |= (counters->RXERRCNT & 0xFF) << 8;       // Set 15-8 bits
    reg_value |= counters->TXERRCNT & 0xFF;               // Set 7-0 bits

    *ECR = reg_value; // Write to the register
}


CAN_Error_Counters get_CAN_Error_Counters() {
    uint32_t reg_value = *ECR; // Read the register value
    CAN_Error_Counters counters;
    counters.RXERRCNT_FAST = (reg_value >> 24) & 0xFF; // Extract 31-24 bits
    counters.TXERRCNT_FAST = (reg_value >> 16) & 0xFF; // Extract 23-16 bits
    counters.RXERRCNT = (reg_value >> 8) & 0xFF;       // Extract 15-8 bits
    counters.TXERRCNT = reg_value & 0xFF;               // Extract 7-0 bits
}


#include "can.h"


CAN_Error_Status getErrorAndStatus1(void) {
    CAN_Error_Status status;

    // Read the value from the ESR1 register
    uint32_t reg_value = *ESR1;

    status.BIT1ERR_FAST = (reg_value >> 31) & 0x01;
    status.BIT0ERR_FAST = (reg_value >> 30) & 0x01;
    status.CRCERR_FAST = (reg_value >> 28) & 0x01;
    status.FRMERR_FAST = (reg_value >> 27) & 0x01;
    status.STFERR_FAST = (reg_value >> 26) & 0x01;
    status.reserved1 = (reg_value >> 25) & 0x1F; // Reserved bits
    status.ERROVR = (reg_value >> 21) & 0x01;
    status.ERRINT_FAST = (reg_value >> 20) & 0x01;
    status.BOFFDONEINT = (reg_value >> 19) & 0x01;
    status.SYNCH = (reg_value >> 18) & 0x01;
    status.TWRNINT = (reg_value >> 17) & 0x01;
    status.RWRNINT = (reg_value >> 16) & 0x01;
    status.BIT1ERR = (reg_value >> 15) & 0x01;
    status.BIT0ERR = (reg_value >> 14) & 0x01;
    status.ACKERR = (reg_value >> 13) & 0x01;
    status.CRCERR = (reg_value >> 12) & 0x01;
    status.FRMERR = (reg_value >> 11) & 0x01;
    status.STFERR = (reg_value >> 10) & 0x01;
    status.TXWRN = (reg_value >> 9) & 0x01;
    status.RXWRN = (reg_value >> 8) & 0x01;
    status.IDLE = (reg_value >> 7) & 0x01;
    status.TX = (reg_value >> 6) & 0x01;
    status.FLTCONF = (reg_value >> 4) & 0x03;
    status.RX = (reg_value >> 3) & 0x01;
    status.BOFFINT = (reg_value >> 2) & 0x01;
    status.ERRINT = (reg_value >> 1) & 0x01;
    status.reserved2 = reg_value & 0x01; // Reserved bit

    return status;
}


//--------------------------------------------------------------------------------


/*

Masks interrupt flags. This register allows any of the 32 message buffer interrupts to be enabled or disabled for MB63–MB32. It
contains one interrupt mask bit per buffer. This configuration allows the CPU to determine which buffer generates an interrupt after
a successful transmission or reception when the corresponding Interrupt Flags 2 (IFLAG2) flag is set

*/

uint32_t get_Interrupt_Masks_2(){
    return *IMASK2;
} 

void set_Interrupt_Masks_2(uint32_t BUF63TO32M){
*IMASK2=BUF63TO32M;
}

//-------------------------------------------------------



/*
Masks interrupt flags. This register allows any of the 32 message buffer interrupts to be enabled or disabled for MB31–MB0. It
contains one interrupt mask bit per buffer. This configuration allows the CPU to determine which buffer generates an interrupt after
a successful transmission or reception when the corresponding Interrupt Flags 1 (IFLAG1) flag is set.
*/


uint32_t get_Interrupt_Masks_1(){
    return *IMASK1;
} 

void set_Interrupt_Masks_1(uint32_t BUF31TO0M){
*IMASK1=BUF31TO0M;
}


//----------------------------------------------------------------------------


/*

Contains the flags for the 32 message buffer interrupts for MB63–MB32. It contains one interrupt flag bit per buffer. Each
successful transmission or reception sets the respective flag in this register. If the corresponding Interrupt Masks 2 (IMASK2) bit
is set, an interrupt is generated.
Before updating MCR[MAXMB], the CPU must service the IFLAG2 flags whose MB value is greater than the MAXMB to be
updated. Otherwise, those flags remain set and are inconsistent with the number of message buffers available

*/

uint32_t get_Interrupt_Flags_2(){
return *IFLAG2;
}
//------------------------------------------------------------------------------

/*

Contains the flags for the 32 message buffer interrupts for MB31–MB0. It contains one interrupt flag bit per buffer. Each successful
transmission or reception sets the corresponding IFLAG1 bit. If the corresponding Interrupt Masks 1 (IMASK1) bit is set, an
interrupt is generated. There is an exception when DMA for Legacy RX FIFO is enabled, as described below.
*/



CAN_Buffer_Interrupt getBufferInterrupt(void) {
    CAN_Buffer_Interrupt bufferInterrupt;

    // Read the value from the BUFINT register
    uint32_t reg_value = *IFLAG1;

    // Populate the CAN_Buffer_Interrupt structure
    bufferInterrupt.BUF31TO8I = (reg_value >> 16) & 0xFFFFFF; // 24 bits
    bufferInterrupt.BUF7I = (reg_value >> 7) & 0x01;
    bufferInterrupt.BUF6I = (reg_value >> 6) & 0x01;
    bufferInterrupt.BUF5I = (reg_value >> 5) & 0x01;
    bufferInterrupt.BUF4TO1I = (reg_value >> 1) & 0x0F; // 4 bits
    bufferInterrupt.BUF0I = reg_value & 0x01;

    return bufferInterrupt;
}


//---------------------------------------------------------------


/*

Complements Control 1 (CTRL1), providing control bits for memory write-access in Freeze mode. This register extends Legacy
FIFO filter quantity, and adjusts the operation of internal FlexCAN processes such as matching and arbitration.
Soft reset does not affect the contents of this register.
*/


CAN_Control2 getCANControl2(void) {
    uint32_t regValue = *CTRL2;
    CAN_Control2 ctrl2;

    ctrl2.ERRMSK_FAST = (regValue >> 31) & 0x01;
    ctrl2.BOFFDONEMSK = (regValue >> 30) & 0x01;
    ctrl2.ECRWRE = (regValue >> 29) & 0x01;
    ctrl2.WRMFRZ = (regValue >> 28) & 0x01;
    ctrl2.RFFN = (regValue >> 24) & 0x0F;
    ctrl2.TASD = (regValue >> 19) & 0x1F;
    ctrl2.MRP = (regValue >> 18) & 0x01;
    ctrl2.RRS = (regValue >> 17) & 0x01;
    ctrl2.EACEN = (regValue >> 16) & 0x01;
    ctrl2.TIMER_SRC = (regValue >> 15) & 0x01;
    ctrl2.PREXCEN = (regValue >> 14) & 0x01;
    ctrl2.BTE = (regValue >> 13) & 0x01;
    ctrl2.ISOCANFDEN = (regValue >> 12) & 0x01;
    ctrl2.EDFLTDIS = (regValue >> 11) & 0x01;
    ctrl2.MBTSBASE = (regValue >> 8) & 0x03;
    ctrl2.TSTAMPCAP = (regValue >> 6) & 0x03;

    return ctrl2;
}

void setCANControl2(CAN_Control2 ctrl2) {
    uint32_t regValue = 0;

    regValue |= (ctrl2.ERRMSK_FAST & 0x01) << 31;
    regValue |= (ctrl2.BOFFDONEMSK & 0x01) << 30;
    regValue |= (ctrl2.ECRWRE & 0x01) << 29;
    regValue |= (ctrl2.WRMFRZ & 0x01) << 28;
    regValue |= (ctrl2.RFFN & 0x0F) << 24;
    regValue |= (ctrl2.TASD & 0x1F) << 19;
    regValue |= (ctrl2.MRP & 0x01) << 18;
    regValue |= (ctrl2.RRS & 0x01) << 17;
    regValue |= (ctrl2.EACEN & 0x01) << 16;
    regValue |= (ctrl2.TIMER_SRC & 0x01) << 15;
    regValue |= (ctrl2.PREXCEN & 0x01) << 14;
    regValue |= (ctrl2.BTE & 0x01) << 13;
    regValue |= (ctrl2.ISOCANFDEN & 0x01) << 12;
    regValue |= (ctrl2.EDFLTDIS & 0x01) << 11;
    regValue |= (ctrl2.MBTSBASE & 0x03) << 8;
    regValue |= (ctrl2.TSTAMPCAP & 0x03) << 6;

    *CTRL2 = regValue;
}

//---------------------------------------------------------------------------------------------



//Reports general status information.

CAN_Status getErrorStatus2(void) {
    uint32_t regValue = *ESR2; // Read the value from the register
    
    CAN_Status status;
    
    // Extract and populate the fields in CAN_Status
    status.LPTM = (regValue >> 16) & 0x7F;   // Extract bits 22-16
    status.VPS  = (regValue >> 14) & 0x01;   // Extract bit 14
    status.IMB  = (regValue >> 13) & 0x01;   // Extract bit 13
    
    return status;
}

//-----------------------------------------------------

/*

Provides information about the CRC of transmitted messages for non-FD messages. This register only reports the 15 low-order
bits of CRC calculations for messages in CAN FD format that require either 17 or 21 bits. For CAN FD format frames, you must
use the CAN FD CRC (FDCRC). This register is updated at the same time that the TX interrupt flag is set.

*/

CRC_check get_Cyclic_Redundancy_Check(){
CRC_check crc_;
crc_.MBCRC=(uint8_t)((*CRCR>>16)&0x7F);
crc_.TXCRC=(uint16_t)(CRCR & 0x7FFF);
return crc_;
}

//------------------------------------------------

/*

Masks the Legacy RX FIFO ID filter table elements that do not have a corresponding RXIMR according to CTRL2[RFFN], when
Legacy RX FIFO is enabled.
This register is located in RAM.
You can only write to this register in Freeze mode; the module blocks it in other modes.

*/

void set_Legacy_RX_FIFO_Global_Mask(uint32_t fgm){
*RXFGMASK=fgm;
}

uint32_t get_Legacy_RX_FIFO_Global_Mask(){
return *RXFGMASK;
}


//--------------------------------------------------------------

/*
Provides information about Legacy RX FIFO.
This register is the port through which the CPU accesses the output of the Legacy RXFIR FIFO located in RAM. FlexCAN writes
to the Legacy RXFIR FIFO when a new message is moved into the Legacy RX FIFO. Also, its output is updated whenever the
output of the Legacy RX FIFO is updated with the next message. See Legacy RX FIFO for instructions on reading this register.

*/


uint16_t get_Legacy_RX_FIFO_Information(){
    return (uint16_t)(*RXFIR) ;
}

//-----------------------------------------------


/*
Provides an alternative way to store the CAN bit timing variables described in Control 1 (CTRL1). EPRESDIV,
EPROPSEG, EPSEG1, EPSEG2, and ERJW are extended versions of CTRL1[PRESDIV], CTRL1[PROPSEG], CTRL1[PSEG1],
CTRL1[PSEG2], and CTRL1[RJW] respectively.

*/




Extended_CAN_Config get_CBT(void) {
    uint32_t reg_value = *CBT; // Read the CBT register value

    Extended_CAN_Config config;
    config.BTF = (reg_value >> 31) & 0x01; // Extract BTF
    config.EPRESDIV = (reg_value >> 21) & 0x03FF; // Extract EPRESDIV
    config.ERJW = (reg_value >> 16) & 0x1F; // Extract ERJW
    config.EPROPSEG = (reg_value >> 10) & 0x3F; // Extract EPROPSEG
    config.EPSEG1 = (reg_value >> 5) & 0x1F; // Extract EPSEG1
    config.EPSEG2 = reg_value & 0x1F; // Extract EPSEG2

    return config;
}

// Function to write values to the CBT register from the Extended_CAN_Config structure
void set_CBT(const Extended_CAN_Config* config) {
    uint32_t reg_value = 0;
    
    reg_value |= (config->BTF & 0x01) << 31; // Set BTF
    reg_value |= (config->EPRESDIV & 0x03FF) << 21; // Set EPRESDIV
    reg_value |= (config->ERJW & 0x1F) << 16; // Set ERJW
    reg_value |= (config->EPROPSEG & 0x3F) << 10; // Set EPROPSEG
    reg_value |= (config->EPSEG1 & 0x1F) << 5; // Set EPSEG1
    reg_value |= (config->EPSEG2 & 0x1F); // Set EPSEG2

    *CBT = reg_value; // Write the value back to the CBT register
}

//-----------------------------------------------------------------



/*

Enables or disables any number of the 32 message buffer interrupts for MB95–MB64. It contains one interrupt mask bit per buffer.
This configuration allows the CPU to determine which buffer generates an interrupt after a successful transmission or reception
when the corresponding IFLAG3 flag is set.

*/


void set_Interrupt_Masks_3(uint32_t BUF95TO64M){
*IMASK3=BUF95TO64M;
}

uint32_t get_Interrupt_Masks_3(){
return *IMASK3;
}

//----------------------------------------------------


void set_Interrupt_Flags_3(uint32_t BUF95TO64){
*IFLAG3=BUF95TO64;
}

uint32_t get_Interrupt_Flags_3(){
return *IFLAG3;
}

//----------------------------------------------------

/*

Stores the acceptance masks for ID filtering in RX message buffers and the Legacy RX FIFO.
When the Legacy RX FIFO is disabled (MCR[RFEN] = 0), an individual mask is provided for each available RX message buffer
on a one-to-one correspondence. When the Legacy RX FIFO is enabled (MCR[RFEN] = 1), an individual mask is provided for
each Legacy RX FIFO ID filter table element on a one-to-one correspondence. This correspondence depends on the setting of
CTRL2[RFFN] (see Legacy RX FIFO).

*/


uint32_t get_Receive_Individual_Mask(uint8_t n){
return *RXIMR(n);
}

uint32_t set_Receive_Individual_Mask(uint8_t n,uint32_t MI){
*RXIMR(n)=MI;
}

//-----------------------------------------------------------------

/*

Contains control bits for memory error detection and correction (ECC).
When CTRL2[ECRWRE] = 0, writes to this register are blocked, except for MECR[ECRWRDIS].

*/


CAN_ErrorControl get_CAN_ErrorControl(void) {
    uint32_t regValue = *MECR;  // Read the MECR register
    
    CAN_ErrorControl status;
    status.ECRWRDIS = (regValue >> 31) & 0x01;
    status.HANCEI_MSK = (regValue >> 19) & 0x01;
    status.FANCEI_MSK = (regValue >> 18) & 0x01;
    status.CEI_MSK = (regValue >> 16) & 0x01;
    status.HAERRIE = (regValue >> 15) & 0x01;
    status.FAERRIE = (regValue >> 14) & 0x01;
    status.EXTERRIE = (regValue >> 13) & 0x01;
    status.RERRDIS = (regValue >> 9) & 0x01;
    status.ECCDIS = (regValue >> 8) & 0x01;
    status.NCEFAFRZ = (regValue >> 7) & 0x01;
    
    return status;
}

void set_CAN_ErrorControl(CAN_ErrorControl control) {
    uint32_t regValue = *MECR;  // Read the current value of the MECR register

    regValue &= ~(1 << 31);  // Clear the ECRWRDIS bit
    regValue |= (control.ECRWRDIS & 0x01) << 31;

    regValue &= ~(1 << 19);  // Clear the HANCEI_MSK bit
    regValue |= (control.HANCEI_MSK & 0x01) << 19;

    regValue &= ~(1 << 18);  // Clear the FANCEI_MSK bit
    regValue |= (control.FANCEI_MSK & 0x01) << 18;

    regValue &= ~(1 << 16);  // Clear the CEI_MSK bit
    regValue |= (control.CEI_MSK & 0x01) << 16;

    regValue &= ~(1 << 15);  // Clear the HAERRIE bit
    regValue |= (control.HAERRIE & 0x01) << 15;

    regValue &= ~(1 << 14);  // Clear the FAERRIE bit
    regValue |= (control.FAERRIE & 0x01) << 14;

    regValue &= ~(1 << 13);  // Clear the EXTERRIE bit
    regValue |= (control.EXTERRIE & 0x01) << 13;

    regValue &= ~(1 << 9);   // Clear the RERRDIS bit
    regValue |= (control.RERRDIS & 0x01) << 9;

    regValue &= ~(1 << 8);   // Clear the ECCDIS bit
    regValue |= (control.ECCDIS & 0x01) << 8;

    regValue &= ~(1 << 7);   // Clear the NCEFAFRZ bit
    regValue |= (control.NCEFAFRZ & 0x01) << 7;

    *MECR = regValue;  // Write the updated value back to the MECR register
}

//--------------------------------------------------------

/*

Contains the address where error is to be injected.

 * Error Injection Address for Classical CAN Format
 * ------------------------------------------------
 * This table helps in converting from the memory map address to the 
 * location in the physical FlexCAN RAM. Where pairs of values are provided, 
 * the first is the address for MCR[FDEN] = 0, the second is for MCR[FDEN] = 1.
 *
 * +-------------------------+------------------+------------------+
 * | RAM Contents            | Injection Address | Memory Map       |
 * +-------------------------+------------------+------------------+
 * | FlexCAN registers       | Not mapped        | —                |
 * | Message buffers         | 0000h             | 0080h            |
 * | RXIMRs                  | 600h              | 0880h            |
 * | RXFIR_0                 | 780h              | 0A80h            |
 * | RXFIR_1                 | 784h              | 0A84h            |
 * | RXFIR_2                 | 788h              | 0A88h            |
 * | RXFIR_3                 | 78Ch              | 0A8Ch            |
 * | RXFIR_4                 | 790h              | 0A90h            |
 * | RXFIR_5                 | 794h              | 0A94h            |
 * | Reserved                | —                 | 0A98h            |
 * | RXMGMASK                | 7A0h              | 0AA0h            |
 * | RXFGMASK                | 7A4h              | 0AA4h            |
 * | RX14MASK                | 7A8h              | 0AA8h            |
 * | RX15MASK                | 7ACh              | 0AACh            |
 * | Tx_SMB                  | 7B0h              | 0AB0h / 0F28h    |
 * | Rx_SMB0                 | 7C0h / 7F8h       | 0AC0h / 0F70h    |
 * | Rx_SMB1                 | 7D0h / 840h       | 0AD0h / 0FB8h    |
 * | Rx_SMB0_TIME_STAMP      | 888h              | 0C20h            |
 * | Rx_SMB1_TIME_STAMP      | 88Ch              | 0C24h            |
 * | HR_TIME_STAMP           | 890h              | 0C30h            |
 * | Enhanced RX FIFO        | A10h              | 2000h            |
 * | ERFFEL                  | 1050h             | 3000h            |
 * +-------------------------+------------------+------------------+


For RXFIR, Enhanced RX FIFO, and HR_TIME_STAMP addresses, you must inject ECC errors in host
access only.

 */


Error_injection get_Error_injection(void) {
    uint32_t regValue = *ERRIAR;  // Read the ERRIAR register
    
    Error_injection injectionStatus;
    injectionStatus.INJADDR_H = (regValue >> 2) & 0x0FFF;  // Extract bits 13-2
    injectionStatus.INJADDR_L = regValue & 0x03;           // Extract bits 1-0
    
    return injectionStatus;
}

void set_Error_injection(Error_injection injectionControl) {
    uint32_t regValue = *ERRIAR;  // Read the current value of the ERRIAR register

    regValue &= ~0x3FFF;  // Clear bits 13-0 (13-2 for INJADDR_H and 1-0 for INJADDR_L)
    regValue |= (injectionControl.INJADDR_H & 0x0FFF) << 2;  // Set bits 13-2 for INJADDR_H
    regValue |= injectionControl.INJADDR_L & 0x03;           // Set bits 1-0 for INJADDR_L

    *ERRIAR = regValue;  // Write the updated value back to the ERRIAR register
}

//---------------------------------------------------------

/*

Contains the error pattern to be injected in the data word read from memory.
*/

uint32_t get_Error_Injection_Data_Pattern(){
return (*ERRIDPR);
}

void set_Error_Injection_Data_Pattern(uint32_t DFLIP){
*ERRIDPR=DFLIP;
}

//-------------------------------------------------------

/*

Error Injection Parity Pattern

Contains the error pattern to be injected in parity bits read from memory with the data word. Bits set to 1 in the flip pattern
cause the corresponding parity bit in the word read from memory to invert.

*/

ParityFlipPattern getErrorInjectionParityPattern() {
    ParityFlipPattern pattern;
    uint32_t value = *ERRIPPR;

    // Extract the relevant bits from the register value
    pattern.PFLIP3 = (value >> 24) & 0x1F; // Bits 28-24
    pattern.PFLIP2 = (value >> 16) & 0x1F; // Bits 20-16
    pattern.PFLIP1 = (value >> 8)  & 0x1F; // Bits 12-8
    pattern.PFLIP0 = (value >> 0)  & 0x1F; // Bits 4-0

    return pattern;
}

void setErrorInjectionParityPattern(ParityFlipPattern pattern) {
    uint32_t value = 0;

    // Set the bits in the register value based on the pattern
    value |= ((uint32_t)(pattern.PFLIP3 & 0x1F) << 24); // Bits 28-24
    value |= ((uint32_t)(pattern.PFLIP2 & 0x1F) << 16); // Bits 20-16
    value |= ((uint32_t)(pattern.PFLIP1 & 0x1F) << 8);  // Bits 12-8
    value |= ((uint32_t)(pattern.PFLIP0 & 0x1F) << 0);  // Bits 4-0

    *ERRIPPR = value;
}

//---------------------------------------------
/*
 * Error Address Reporting and Source Identification
 * -------------------------------------------------
 * This section describes how the FlexCAN module reports the address and source
 * of an access operation where an error (correctable or non-correctable) was detected.
 *
 * Address Alignment:
 * - The address is always reported using a 32-bit alignment.
 * - Non-aligned accesses (ERRADDR[1:0] nonzero) are reported with the address aligned, 
 *   and the data is reported in Error Report Data (RERRDR) shifted accordingly.
 * - For errors detected in accesses larger than 32-bit (as performed by FlexCAN internal processes), 
 *   the address of the 32-bit word where the error was detected is reported.
 * - If errors are detected in more than one 32-bit word, only the least significant address is reported.
 *
 * Source of Memory Access (SAID[2:0]):
 * +-----+--------------------------------+
 * | SAID| Error during...                |
 * +-----+--------------------------------+
 * |  0  | Move-out FlexCAN access        |
 * |  1  | Move-in                        |
 * |  2  | TX arbitration                 |
 * |  3  | RX matching                    |
 * |  4  | Move-out host access           |
 * | 5–7 | Reserved                       |
 * +-----+--------------------------------+
 */


ErrorStatus getErrorStatus(void) {
    uint32_t register_value = *RERRAR;
    ErrorStatus status;

    status.NCE = (register_value >> 24) & 0x01;
    status.SAID = (register_value >> 16) & 0x07;
    status.ERRADDR = register_value & 0x3FFF;

    return status;
}

void setErrorStatus(ErrorStatus status) {
    uint32_t register_value = 0;

    register_value |= ((uint32_t)(status.NCE & 0x01) << 24);
    register_value |= ((uint32_t)(status.SAID & 0x07) << 16);
    register_value |= (status.ERRADDR & 0x3FFF);

    *RERRAR = register_value;
}

//----------------------------------------------------------

/*


Reports the raw data (unmodified by the correction performed by ECC logic) read from memory with error. 
The value reported does not represent the transient values of the BUSY bit when reading a message buffer.
*/
uint32_t get_Error_Report_Data(){
return *RERRDR;
}



//------------------------------------------------------



/*
Error Report Syndrome (RERRSYNR)

Contains the syndrome detected in a memory read with error. It also reports the bytes which were read in this 32-bit
read transaction.
Each SYNDn field indicates the type of error and which bit in byte (n) the error affects. SYND3 corresponds to the most significant 
byte in the data word read from memory; SYND0 corresponds to the least significant


Each BEn field indicates which byte in the 32-bit word reported was effectively read. The syndrome bits are calculated for all
bytes, including the non-read ones. Errors detected in non-read bytes are indicated


 * Syndrome Definition (SYND)
 * --------------------------
 * The following table defines the meaning of the syndrome values 
 * reported by the system during error detection.
 *
 * +--------+-------------------------------+---------------------+
 * | SYND n | Type                           | Bit Affected        |
 * |  (hex) |                               |                     |
 * +--------+-------------------------------+---------------------+
 * |   00   | —                             | None (no error)      |
 * |   01   | Code                          | 0                   |
 * |   02   | Code                          | 1                   |
 * |   04   | Code                          | 2                   |
 * |   07   | Data                          | 5                   |
 * |   08   | Code                          | 3                   |
 * |   0E   | Data                          | 7                   |
 * |   10   | Code                          | 4                   |
 * |   13   | Data                          | 2                   |
 * |   15   | Data                          | 6                   |
 * |   16   | Data                          | 1                   |
 * |   19   | Data                          | 3                   |
 * |   1A   | Data                          | 4                   |
 * |   1C   | Data                          | 0                   |
 * |   06   | —                             | All-zeroes noncorrectable error |
 * |   1F   | —                             | All-ones noncorrectable error   |
 * | All others | —                         | Noncorrectable error |
 * +--------+-------------------------------+---------------------+
 */

ErrorSyndrome getErrorSyndrome(void) {
    // Read the register value
    uint32_t reg_value = *RERRSYNR;
    
    ErrorSyndrome err_syndrome;
    err_syndrome.BE3 = (reg_value >> 31) & 0x01;
    err_syndrome.SYND3 = (reg_value >> 24) & 0x1F;
    err_syndrome.BE2 = (reg_value >> 23) & 0x01;
    err_syndrome.SYND2 = (reg_value >> 16) & 0x1F;
    err_syndrome.BE1 = (reg_value >> 15) & 0x01;
    err_syndrome.SYND1 = (reg_value >> 8) & 0x1F;
    err_syndrome.BE0 = (reg_value >> 7) & 0x01;
    err_syndrome.SYND0 = (reg_value >> 0) & 0x1F;

    return err_syndrome;
}


//----------------------------------------------------------------------

/*

Contains the status bits of the error correction and detection operations. These flags can be cleared by writing 1 to them. Writing
0 has no effect.

*/

ErrorInterruptFlags getErrorInterruptFlags() {
    ErrorInterruptFlags flags;
    uint32_t regValue = *ERRSR;  // Read the register value

    // Map the register value to the ErrorInterruptFlags structure
    flags.HANCEIF = (regValue >> 19) & 0x01;
    flags.FANCEIF = (regValue >> 18) & 0x01;
    flags.CEIF = (regValue >> 16) & 0x01;
    flags.HANCEIOF = (regValue >> 3) & 0x01;
    flags.FANCEIOF = (regValue >> 2) & 0x01;
    flags.CEIOF = (regValue >> 0) & 0x01;

    // Reserved bits can be handled if necessary
    flags.reserved1 = (regValue >> 4) & 0x0F;  // This handles the reserved bits

    return flags;
}

void setErrorInterruptFlags(const ErrorInterruptFlags* flags) {
    uint32_t regValue = *ERRSR;  // Read the current register value

    // Clear the bits that will be updated
    regValue &= ~(0x01 << 19); // Clear HANCEIF bit
    regValue &= ~(0x01 << 18); // Clear FANCEIF bit
    regValue &= ~(0x01 << 16); // Clear CEIF bit
    regValue &= ~(0x01 << 3);  // Clear HANCEIOF bit
    regValue &= ~(0x01 << 2);  // Clear FANCEIOF bit
    regValue &= ~(0x01 << 0);  // Clear CEIOF bit

    // Set the new values
    regValue |= ((flags->HANCEIF & 0x01) << 19);
    regValue |= ((flags->FANCEIF & 0x01) << 18);
    regValue |= ((flags->CEIF & 0x01) << 16);
    regValue |= ((flags->HANCEIOF & 0x01) << 3);
    regValue |= ((flags->FANCEIOF & 0x01) << 2);
    regValue |= ((flags->CEIOF & 0x01) << 0);

    *ERRSR = regValue;  // Write the updated value back to the register
}

//-------------------------------------------------------------

/*


Defines the CAN bit timing prescalers for the nominal phase and data phase when CTRL2[BTE] = 1.
Used by the module only if CTRL2[BTE] = 1; otherwise a write operation has no effect and all fields are read as zero.
This register can be written only in Freeze mode; the module blocks it in other modes.
Soft reset does not affect the contents of this register.

*/

ExtendedPrescalerFactors getEPRS(void) {
    ExtendedPrescalerFactors value;
    uint32_t reg_value = *EPRS;

    value.EDPRESDIV = (reg_value >> 16) & 0xFF; // Extract bits 25-16
    value.ENPRESDIV = reg_value & 0x3FF;        // Extract bits 9-0

    return value;
}

void setEPRS(ExtendedPrescalerFactors value) {
    uint32_t reg_value = 0;

    reg_value |= ((uint32_t)value.EDPRESDIV << 16); // Set bits 25-16
    reg_value |= ((uint32_t)value.ENPRESDIV & 0x3FF); // Set bits 9-0

    *EPRS = reg_value;
}


//-----------------------------------------------------------------

/*
 * Enhanced Nominal CAN Bit Timing (ENCBT)
 * ----------------------------------------
 * Offset Register: ENCBT BF4h
 * 
 * Function:
 * - Provides an alternative way to store the CAN bit timing variables that are usually described in the
 *   Control 1 (CTRL1) and CAN Bit Timing (CBT) registers, offering higher resolution for CAN bit timing.
 * 
 * Usage:
 * - This register is utilized by the CAN module only if CTRL2[BTE] = 1. 
 * - If CTRL2[BTE] = 0, any write operation to this register has no effect, and all fields are read as zero.
 * 
 * Restrictions:
 * - The contents of this register are not affected by a soft reset.
 * - This register can only be written to in Freeze mode; attempts to write in other modes will be blocked by the module.
 */



NominalTiming get_ENCBT(void) {
    NominalTiming timing;
    uint32_t reg_value = *ENCBT;
    
    // Extract fields from the register value
    timing.NRJW = (reg_value >> 22) & 0x7F;   // 7 bits
    timing.NTSEG2 = (reg_value >> 12) & 0x7F; // 7 bits
    timing.NTSEG1 = reg_value & 0xFF;         // 8 bits
    
    return timing;
}

void set_ENCBT(NominalTiming timing) {
    uint32_t reg_value = 0;
    
    // Set fields in the register value
    reg_value |= (timing.NRJW & 0x7F) << 22; // 7 bits
    reg_value |= (timing.NTSEG2 & 0x7F) << 12; // 7 bits
    reg_value |= timing.NTSEG1 & 0xFF;         // 8 bits
    
    // Write the value to the register
    *ENCBT = reg_value;
}

//------------------------------------------------------

/*

Provides an alternative way to store the data phase CAN bit timing variables described in CAN FD Bit Timing (FDCBT) to achieve
higher CAN bit timing resolution.
This register is used by the module only if CTRL2[BTE] = 1; otherwise a write operation has no effect and all fields are read as zero.
Soft reset does not affect the contents of this register.
This register can be written only in Freeze mode; the module blocks it in other modes.

*/

DataPhaseTiming get_EDCBT(void) {
    DataPhaseTiming timing;
    uint32_t reg_value = *EDCBT;

    timing.DRJW = (reg_value >> 22) & 0x0F;     // Extract bits 25-22
    timing.DTSEG2 = (reg_value >> 12) & 0x0F;   // Extract bits 15-12
    timing.DTSEG1 = reg_value & 0x1F;           // Extract bits 4-0

    return timing;
}

void set_EDCBT(DataPhaseTiming timing) {
    uint32_t reg_value = *EDCBT;

    reg_value &= ~(0x0F << 22);                // Clear bits 25-22
    reg_value |= (timing.DRJW & 0x0F) << 22;  // Set bits 25-22

    reg_value &= ~(0x0F << 12);                // Clear bits 15-12
    reg_value |= (timing.DTSEG2 & 0x0F) << 12;// Set bits 15-12

    reg_value &= ~0x1F;                        // Clear bits 4-0
    reg_value |= timing.DTSEG1 & 0x1F;        // Set bits 4-0

    *EDCBT = reg_value;
}


//----------------------------------------------------------------------------------


/*


Contains extended versions of FDCTRL[TDCOFF] and FDCTRL[TDCVAL]. This register is used by the module only if
CTRL2[BTE] = 1. Otherwise, a write operation has no effect and all fields are read as zero.

*/

TransceiverDelayCompensation get_ETDC(void) {
    uint32_t reg_value = *ETDC;  // Read the register value
    TransceiverDelayCompensation result;

    result.ETDCEN    = (reg_value >> 31) & 0x01;
    result.TDMDIS    = (reg_value >> 30) & 0x01;
    result.ETDCOFF   = (reg_value >> 16) & 0x7F;
    result.ETDCFAIL  = (reg_value >> 15) & 0x01;
    result.ETDCVAL   = reg_value & 0xFF;

    return result;
}

void set_ETDC(TransceiverDelayCompensation value) {
    uint32_t reg_value = 0;

    reg_value |= (value.ETDCEN & 0x01) << 31;
    reg_value |= (value.TDMDIS & 0x01) << 30;
    reg_value |= (value.ETDCOFF & 0x7F) << 16;
    reg_value |= (value.ETDCFAIL & 0x01) << 15;

    *ETDC = reg_value;  // Write the register value
}

//------------------------------------------------------------------------

/*

Contains control bits for CAN FD operation. It also defines the data size of message buffers allocated in different partitions of RAM
(memory blocks

When an 8-byte payload is selected:


/*
 * Message Buffer Allocation and Payload Size Limitations
 * -------------------------------------------------------
 * Block R0 allocates Message Buffers (MB) 0–31.
 * Block R1 allocates MB32–MB63.
 * Block R2 allocates MB64–MB95.
 *
 * When a payload larger than eight bytes is selected, the maximum number of message buffers per block is limited as follows:
 * 
 * +-----------------+---------------------------------------+
 * | Payload Size    | Maximum Number of Message Buffers per Block |
 * +-----------------+---------------------------------------+
 * | 8 bytes         | 32                                    |
 * | 16 bytes        | 21                                    |
 * | 32 bytes        | 12                                    |
 * | 64 bytes        | 7                                     |
 * +-----------------+---------------------------------------+
 * 
 * Note:
 * - One memory block fits exactly 32 message buffers with an 8-byte payload.
 * - For other payload sizes, empty memory may exist between the last message buffer in a block and the beginning of the next block.
 *   This empty memory corresponds to less than one message buffer and must not be used.
 * - A soft reset does not affect the contents of the message buffers.
 */

*/


TransceiverDelayCompensation getFDCTRL(void) {
    uint32_t reg_value = *FDCTRL;
    
    TransceiverDelayCompensation_fd ctrl;
    ctrl.FDRATE = (reg_value >> 31) & 0x01;
    ctrl.MBDSR2 = (reg_value >> 22) & 0x03;
    ctrl.MBDSR1 = (reg_value >> 19) & 0x03;
    ctrl.MBDSR0 = (reg_value >> 16) & 0x03;
    ctrl.TDCEN = (reg_value >> 15) & 0x01;
    ctrl.TDCFAIL = (reg_value >> 14) & 0x01;
    ctrl.TDCOFF = (reg_value >> 8) & 0x1F;
    ctrl.TDCVAL = reg_value & 0x3F;
    
    return ctrl;
}

// Function to set the value in the FDCTRL register
void setFDCTRL(TransceiverDelayCompensation_fd ctrl) {
    uint32_t reg_value = 0;
    
    reg_value |= (ctrl.FDRATE & 0x01) << 31;
    reg_value |= (ctrl.MBDSR2 & 0x03) << 22;
    reg_value |= (ctrl.MBDSR1 & 0x03) << 19;
    reg_value |= (ctrl.MBDSR0 & 0x03) << 16;
    reg_value |= (ctrl.TDCEN & 0x01) << 15;
    reg_value |= (ctrl.TDCFAIL & 0x01) << 14;
    reg_value |= (ctrl.TDCOFF & 0x1F) << 8;
    
    *FDCTRL = reg_value;
}

//-----------------------------------------------------------------------

/*



Stores the CAN bit timing variables used in the data phase of CAN FD messages when the FDCTRL[FDRATE] = 1, compatible
with the CAN FD specification. Fields in this register define:
• The time quantum duration
• The number of time quanta per CAN bit
• The sample point position for the data bit rate portion of a CAN FD message with BRS = 1
Soft reset does not affect the contents of this register.
The sum of the Fast Propagation Segment (FPROPSEG) and Fast Phase Segment 1 (FPSEG1) must be at least two time quanta.
Ensure bit time settings and protocol engine tolerance are in compliance with the CAN Protocol standard (ISO 11898-1:2015)

*/

FastPrescalerConfig get_FDCBT(void) {
    uint32_t reg_value = *FDCBT;
    FastPrescalerConfig config;

    // Extract each field from the register value
    config.FPRESDIV = (reg_value >> 20) & 0x3FF;  // Bits 29-20 (10 bits)
    config.FRJW = (reg_value >> 16) & 0x07;       // Bits 18-16 (3 bits)
    config.FPROPSEG = (reg_value >> 10) & 0x1F;   // Bits 14-10 (5 bits)
    config.FPSEG1 = (reg_value >> 5) & 0x07;      // Bits 7-5 (3 bits)
    config.FPSEG2 = reg_value & 0x07;             // Bits 2-0 (3 bits)

    return config;
}


void set_FDCBT(FastPrescalerConfig config) {
    uint32_t reg_value = 0;

    // Set each field in the register value
    reg_value |= (config.FPRESDIV & 0x3FF) << 20;  // Bits 29-20 (10 bits)
    reg_value |= (config.FRJW & 0x07) << 16;       // Bits 18-16 (3 bits)
    reg_value |= (config.FPROPSEG & 0x1F) << 10;   // Bits 14-10 (5 bits)
    reg_value |= (config.FPSEG1 & 0x07) << 5;      // Bits 7-5 (3 bits)
    reg_value |= (config.FPSEG2 & 0x07);           // Bits 2-0 (3 bits)

    *FDCBT = reg_value;
}

//------------------------------------------------------------------------------

/*

Function
Provides information about the cyclic redundancy check (CRC) of transmitted messages.
FlexCAN uses different CRC polynomials for different frame formats.
• The CRC_15 polynomial is used for all frames in CAN format.
• The CRC_17 polynomial is used for frames in CAN FD format with a DATA FIELD up to 16 bytes.
• The CRC_21 polynomial is used for frames in CAN FD format with a DATA FIELD longer than 16 bytes.
Each polynomial shown below results in a Hamming distance of 6. This register is updated at the same time that the TX Interrupt
flag is set.

CRC_15 = C599h: (x 15 + x14 + x10 + x8 + x7 + x4 + x3 + 1)
CRC_17 = 3685Bh: (x 17 + x16 + x14 + x13 + x11 + x6 + x4 + x3 + x1 + 1)
CRC_21 = 302899h: (x 21 + x20 + x13 + x11 + x7 + x4 + x3 + 1)

*/

FDCRC_Config get_FDCRC(void) {
    uint32_t reg_value = *FDCRC;
    FDCRC_Config config;

    // Extract each field from the register value
    config.FD_MBCRC = (reg_value >> 24) & 0x7F;     // Bits 30-24 (7 bits)
    config.FD_TXCRC = reg_value & 0x1FFFFF;         // Bits 20-0 (21 bits)

    return config;
}


void set_FDCRC(FDCRC_Config config) {
    uint32_t reg_value = 0;

    // Set each field in the register value
    reg_value |= (config.FD_MBCRC & 0x7F) << 24;    // Bits 30-24 (7 bits)
    reg_value |= config.FD_TXCRC & 0x1FFFFF;        // Bits 20-0 (21 bits)

    *FDCRC = reg_value;
}


//-------------------------------------------------------------------------


/*

Defines the Enhanced RX FIFO configuration.
This register can be written only in Freeze mode.
Soft reset does not affect any of the contents of this register.


*/

Enhanced_RX_FIFO_Config get_ERFCR(void) {
    Enhanced_RX_FIFO_Config config;
    uint32_t reg_value = *ERFCR;

    config.ERFWM = (uint8_t)(reg_value & 0x1F);                // Bits 4-0
    config.NFE = (uint8_t)((reg_value >> 8) & 0x3F);           // Bits 13-8
    config.NEXIF = (uint8_t)((reg_value >> 16) & 0x7F);        // Bits 22-16
    config.DMALW = (uint8_t)((reg_value >> 26) & 0x1F);        // Bits 30-26
    config.ERFEN = (uint8_t)((reg_value >> 31) & 0x01);        // Bit 31

    return config;
}

void set_ERFCR(Enhanced_RX_FIFO_Config config) {
    uint32_t reg_value = 0;

    reg_value |= ((uint32_t)(config.ERFWM) & 0x1F);            // Bits 4-0
    reg_value |= ((uint32_t)(config.NFE) & 0x3F) << 8;         // Bits 13-8
    reg_value |= ((uint32_t)(config.NEXIF) & 0x7F) << 16;      // Bits 22-16
    reg_value |= ((uint32_t)(config.DMALW) & 0x1F) << 26;      // Bits 30-26
    reg_value |= ((uint32_t)(config.ERFEN) & 0x01) << 31;      // Bit 31

    *ERFCR = reg_value;
}



//----------------------------------------------------------------------



/*

Contains the interrupt enables for the Enhanced RX FIFO.
Soft reset does not affect this register.

*/

void set_ERFIER(Enhanced_RX_FIFO_Interrupt_Config config) {
    uint32_t value = 0;

    value |= ((uint32_t)(config.ERFDAIE) << 28);
    value |= ((uint32_t)(config.ERFWMIIE) << 29);
    value |= ((uint32_t)(config.ERFOVFIE) << 30);
    value |= ((uint32_t)(config.ERFUFWIE) << 31);

    *ERFIER = value;
}

Enhanced_RX_FIFO_Interrupt_Config get_ERFIER() {
    Enhanced_RX_FIFO_Interrupt_Config config;
    uint32_t value = *ERFIER;

    config.ERFDAIE = (uint8_t)((value >> 28) & 0x01);
    config.ERFWMIIE = (uint8_t)((value >> 29) & 0x01);
    config.ERFOVFIE = (uint8_t)((value >> 30) & 0x01);
    config.ERFUFWIE = (uint8_t)((value >> 31) & 0x01);

    return config;
}

//-------------------------------------------------------------------


/*

Contains the status fields of the Enhanced RX FIFO including error indications and a clear FIFO field.
Soft reset does not affect this register.

*/


Enhanced_RX_FIFO_Status get_ERFSR(void) {
    uint32_t register_value = *ERFSR;
    Enhanced_RX_FIFO_Status status;

    status.ERFEL = (uint8_t)(register_value & 0x3F);          // Extract bits 5-0
    status.ERFF = (uint8_t)((register_value >> 16) & 0x01);   // Extract bit 16
    status.ERFE = (uint8_t)((register_value >> 17) & 0x01);   // Extract bit 17
    status.ERFDA = (uint8_t)((register_value >> 28) & 0x01);  // Extract bit 28
    status.ERFWMI = (uint8_t)((register_value >> 29) & 0x01); // Extract bit 29
    status.ERFOVF = (uint8_t)((register_value >> 30) & 0x01); // Extract bit 30
    status.ERFUFW = (uint8_t)((register_value >> 31) & 0x01); // Extract bit 31

    return status;
}

void set_ERFSR(int set[]){
*ERFSR=set[0]|set[1]||set[2]|set[3]|set[4];
}

//----------------------------------------------


/*
 * High-Resolution Timestamp Registers (HR_TIME_STAMP)
 * -----------------------------------------------------
 * - Stores a copy of a 32-bit timer at the start or end of a CAN frame.
 * - HR_TIME_STAMP0 stores the 32-bit timestamp associated with MB0, HR_TIME_STAMP1 stores the 32-bit timestamp
 *   associated with MB1, and so on.
 * - The contents of these registers are not affected by a reset.
 * - Do not write to these registers outside Freeze mode.
 *
 * NOTE:
 * +---------------------------------------------------------------+
 * | Table 510. High-Resolution Timestamp Register Operation        |
 * +----------------+-----------------------------------------------+
 * | TSTAMPCAP      | Captured Timebase   | Capture Point           |
 * +----------------+-----------------------------------------------+
 * | b00            | None                | None                    |
 * | b01            | 32 bits of high-    | Seventh bit of the end-  |
 * |                | resolution on-chip  | of-frame field for       |
 * |                | timer               | transmission and sixth   |
 * |                |                     | bit of the end-of-frame  |
 * |                |                     | field for reception.     |
 * | b10            | 32 bits of high-    | Start of frame           |
 * |                | resolution on-chip  |                          |
 * |                | timer               |                          |
 * | b11            | 32 bits of high-    | Start of frame for       |
 * |                | resolution on-chip  | classical CAN frame      |
 * |                | timer               | format and res bit for   |
 * |                |                     | CAN FD frame format      |
 * +----------------+-----------------------------------------------+
 */


uint32_t get_High_Resolution_Timestamp(uint32_t n){
return *HR_TIME_STAMP(n);
}

void set_High_Resolution_Timestamp(uint32_t n,uint32_t TS){
*(HR_TIME_STAMP(n))=TS;
}

//------------------------------------------


/*


Stores the filter elements of the Enhanced RX FIFO.
For standard ID filtering, each ERFFEL register stores one filter element. For extended ID filtering, each pair of ERFFEL registers
stores one filter element.
ERFFEL registers can be written only in Freeze mode; otherwise, the module blocks them. Reset does not affect these registers.
They are located in RAM and must be explicitly initialized prior to any reception.


*/

uint32_t get_Enhanced_RX_FIFO_Filter_Element(uint8_t n){
return *(ERFFEL(n));
}

void set_Enhanced_RX_FIFO_Filter_Element(uint8_t n,uint32_t FEL){
*(ERFFEL(n))=FEL;
}
