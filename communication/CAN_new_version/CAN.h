#ifndef CAN_H
#define CAN_H

#include <stdint.h>

#define CAN_BASE0 (volatile uint32_t*)(0x40304000)

#define MCR         (volatile uint32_t*)(CAN_BASE0 + 0x00)
#define CTRL1       (volatile uint32_t*)(CAN_BASE0 + 0x04)
#define TIMER       (volatile uint32_t*)(CAN_BASE0 + 0x08)
#define RXMGMASK    (volatile uint32_t*)(CAN_BASE0 + 0x10)
#define RX14MASK    (volatile uint32_t*)(CAN_BASE0 + 0x14)
#define RX15MASK    (volatile uint32_t*)(CAN_BASE0 + 0x18)
#define ECR         (volatile uint32_t*)(CAN_BASE0 + 0x1C)
#define ESR1        (volatile uint32_t*)(CAN_BASE0 + 0x20)
#define IMASK2      (volatile uint32_t*)(CAN_BASE0 + 0x24)
#define IMASK1      (volatile uint32_t*)(CAN_BASE0 + 0x28)
#define IFLAG2      (volatile uint32_t*)(CAN_BASE0 + 0x2C)
#define IFLAG1      (volatile uint32_t*)(CAN_BASE0 + 0x30)
#define CTRL2       (volatile uint32_t*)(CAN_BASE0 + 0x34)
#define ESR2        (volatile uint32_t*)(CAN_BASE0 + 0x38)
#define CRCR        (volatile uint32_t*)(CAN_BASE0 + 0x44)
#define RXFGMASK    (volatile uint32_t*)(CAN_BASE0 + 0x48)
#define RXFIR       (volatile uint32_t*)(CAN_BASE0 + 0x4C)
#define CBT         (volatile uint32_t*)(CAN_BASE0 + 0x50)
#define IMASK3      (volatile uint32_t*)(CAN_BASE0 + 0x6C)
#define IFLAG3      (volatile uint32_t*)(CAN_BASE0 + 0x74)
#define RXIMR(n)    ((volatile uint32_t*)(CAN_BASE0 + 0x880 + ((n) * 0x04)))
#define MECR        (volatile uint32_t*)(CAN_BASE0 + 0xAE0)
#define ERRIAR      (volatile uint32_t*)(CAN_BASE0 + 0xAE4)
#define ERRIDPR     (volatile uint32_t*)(CAN_BASE0 + 0xAE8)
#define ERRIPPR     (volatile uint32_t*)(CAN_BASE0 + 0xAEC)
#define RERRAR      (volatile uint32_t*)(CAN_BASE0 + 0xAF0)
#define RERRDR      (volatile uint32_t*)(CAN_BASE0 + 0xAF4)
#define RERRSYNR    (volatile uint32_t*)(CAN_BASE0 + 0xAF8)
#define ERRSR       (volatile uint32_t*)(CAN_BASE0 + 0xAFC)
#define EPRS        (volatile uint32_t*)(CAN_BASE0 + 0xBF0)
#define ENCBT       (volatile uint32_t*)(CAN_BASE0 + 0xBF4)
#define EDCBT       (volatile uint32_t*)(CAN_BASE0 + 0xBF8)
#define ETDC        (volatile uint32_t*)(CAN_BASE0 + 0xBFC)
#define FDCTRL      (volatile uint32_t*)(CAN_BASE0 + 0xC00)
#define FDCBT       (volatile uint32_t*)(CAN_BASE0 + 0xC04)
#define FDCRC       (volatile uint32_t*)(CAN_BASE0 + 0xC08)
#define ERFCR       (volatile uint32_t*)(CAN_BASE0 + 0xC0C)
#define ERFIER      (volatile uint32_t*)(CAN_BASE0 + 0xC10)
#define ERFSR       (volatile uint32_t*)(CAN_BASE0 + 0xC14)
#define HR_TIME_STAMP(n)  ((volatile uint32_t*)(CAN_BASE0 + 0xC30+ ((n) * 0x04)))
#define ERFFEL(n)     ((volatile uint32_t*)(CAN_BASE0 + 0x3000+ ((n)* 0x04)))



typedef struct CAN_config{
uint8_t MDIS;
uint8_t FRZ;
uint8_t RFEN;
uint8_t HALT;
uint8_t NOTRDY;
uint8_t SOFTRST;
uint8_t FRZACK;
uint8_t SUPV;
uint8_t WRNEN;
uint8_t LPMACK;
uint8_t SRXDIS;
uint8_t IRMQ;
uint8_t DMA;
uint8_t LPRIOEN;
uint8_t AEN;
uint8_t FDEN;
uint8_t IDAM;
uint8_t MAXMB;
}CAN_config;



typedef struct CAN_Control{
    uint8_t PRESDIV;   // 31-24: Prescaler Divider
    uint8_t RJW;       // 23-22: Resynchronization Jump Width
    uint8_t PSEG1;     // 21-19: Phase Segment 1
    uint8_t PSEG2;     // 18-16: Phase Segment 2
    uint8_t BOFFMSK;   // 15: Bus Off Mask
    uint8_t ERRMSK;    // 14: Error Interrupt Mask
    uint8_t LPB;       // 12: Loopback Mode
    uint8_t TWRNMSK;   // 11: TX Warning Interrupt Mask
    uint8_t RWRNMSK;   // 10: RX Warning Interrupt Mask
    uint8_t SMP;       // 7: Sampling
    uint8_t BOFFREC;   // 6: Bus Off Recovery
    uint8_t TSYN;      // 5: Timer Sync
    uint8_t LBUF;      // 4: Lower Buffer
    uint8_t LOM;       // 3: Listen-Only Mode
    uint8_t PROPSEG;   // 2-0: Propagation Segment
} CAN_Control;


typedef struct CAN_Error_Counters{
    uint8_t RXERRCNT_FAST; // 31-24: Receive Error Counter for Fast Bits (8 bits)
    uint8_t TXERRCNT_FAST; // 23-16: Transmit Error Counter for Fast Bits (8 bits)
    uint8_t RXERRCNT;      // 15-8: Receive Error Counter (8 bits)
    uint8_t TXERRCNT;      // 7-0: Transmit Error Counter (8 bits)
} CAN_Error_Counters;



// Define the structure for the CAN Error and Status register
typedef struct CAN_Error_Status{
    uint8_t BIT1ERR_FAST;    // 31: Fast Bit1 Error Flag
    uint8_t BIT0ERR_FAST;    // 30: Fast Bit0 Error Flag
    uint8_t CRCERR_FAST;     // 28: Fast CRC Error Flag
    uint8_t FRMERR_FAST;     // 27: Fast Form Error Flag
    uint8_t STFERR_FAST;     // 26: Fast Stuffing Error Flag
    uint8_t reserved1;       // 25-21: Reserved
    uint8_t ERROVR;          // 21: Error Overrun Flag
    uint8_t ERRINT_FAST;     // 20: Fast Error Interrupt Flag
    uint8_t BOFFDONEINT;     // 19: Bus Off Done Interrupt Flag
    uint8_t SYNCH;           // 18: CAN Synchronization Status Flag
    uint8_t TWRNINT;         // 17: TX Warning Interrupt Flag
    uint8_t RWRNINT;         // 16: RX Warning Interrupt Flag
    uint8_t BIT1ERR;         // 15: Bit1 Error Flag
    uint8_t BIT0ERR;         // 14: Bit0 Error Flag
    uint8_t ACKERR;          // 13: Acknowledge Error Flag
    uint8_t CRCERR;          // 12: CRC Error Flag
    uint8_t FRMERR;          // 11: Form Error Flag
    uint8_t STFERR;          // 10: Stuffing Error Flag
    uint8_t TXWRN;           // 9: TX Error Warning Flag
    uint8_t RXWRN;           // 8: RX Error Warning Flag
    uint8_t IDLE;            // 7: Idle
    uint8_t TX;              // 6: FlexCAN In Transmission
    uint8_t FLTCONF;         // 5-4: Fault Confinement State
    uint8_t RX;              // 3: FlexCAN in Reception Flag
    uint8_t BOFFINT;         // 2: Bus Off Interrupt Flag
    uint8_t ERRINT;          // 1: Error Interrupt Flag
    uint8_t reserved2;       // 0: Reserved
} CAN_Error_Status;


typedef struct CAN_Buffer_Interrupt {
    uint16_t BUF31TO8I; // 31-8: Buffer MBi Interrupt
    uint8_t BUF7I;     // 7: Buffer MB7 Interrupt or Legacy RX FIFO Overflow
    uint8_t BUF6I;     // 6: Buffer MB6 Interrupt or Legacy RX FIFO Warning
    uint8_t BUF5I;     // 5: Buffer MB5 Interrupt or Frames available in Legacy RX FIFO
    uint8_t BUF4TO1I;  // 4-1: Buffer MBi Interrupt or Reserved (4 bits)
    uint8_t BUF0I;     // 0: Buffer MB0 Interrupt or Clear Legacy FIFO bit
} CAN_Buffer_Interrupt;


typedef struct CAN_Config2{
    uint8_t ERRMSK_FAST;     // 31: Error Interrupt Mask for Errors Detected in the Data Phase of Fast CAN FD Frames
    uint8_t BOFFDONEMSK;     // 30: Bus Off Done Interrupt Mask
    uint8_t ECRWRE;          // 29: Error Correction Configuration Register Write Enable
    uint8_t WRMFRZ;          // 28: Write Access to Memory in Freeze Mode
    uint8_t RFFN;            // 27-24: Number of Legacy Receive FIFO Filters (4 bits)
    uint8_t TASD;           // 23-19: Transmission Arbitration Start Delay (5 bits)
    uint8_t MRP;            // 18: Message Buffers Reception Priority
    uint8_t RRS;            // 17: Remote Request Storing
    uint8_t EACEN;          // 16: Entire Frame Arbitration Field Comparison Enable for RX Message Buffers
    uint8_t TIMER_SRC;      // 15: Timer Source
    uint8_t PREXCEN;        // 14: Protocol Exception Enable
    uint8_t BTE;            // 13: Bit Timing Expansion Enable
    uint8_t ISOCANFDEN;     // 12: ISO CAN FD Enable
    uint8_t EDFLTDIS;       // 11: Edge Filter Disable
    uint8_t MBTSBASE;       // 9-8: Message Buffer Timestamp Base (2 bits)
    uint8_t TSTAMPCAP;      // 7-6: Timestamp Capture Point (2 bits)
} CAN_Config2;


typedef struct CAN_Status{
    uint8_t LPTM; // 22-16: Lowest Priority TX Message Buffer (7 bits)
    uint8_t VPS;  // 14: Valid Priority Status
    uint8_t IMB;  // 13: Inactive Message Buffer
} CAN_Status;

typedef struct CRC_check{
uint8_t MBCRC:
uint16_t TXCRC;
}CRC_check;

typedef struct Extended_CAN_Config{
    uint8_t BTF;       // 31: Bit Timing Format Enable
    uint16_t EPRESDIV; // 30-21: Extended Prescaler Division Factor (10 bits)
    uint8_t ERJW;      // 20-16: Extended Resync Jump Width (5 bits)
    uint8_t EPROPSEG;  // 15-10: Extended Propagation Segment (6 bits)
    uint8_t EPSEG1;    // 9-5: Extended Phase Segment 1 (5 bits)
    uint8_t EPSEG2;    // 4-0: Extended Phase Segment 2 (5 bits)
} Extended_CAN_Config;


typedef struct CAN_ErrorControl{
    uint8_t ECRWRDIS;      // 31: Error Configuration Register Write Disable
    uint8_t HANCEI_MSK;    // 19: Host Access with Noncorrectable Errors Interrupt Mask
    uint8_t FANCEI_MSK;    // 18: FlexCAN Access with Noncorrectable Errors Interrupt Mask
    uint8_t CEI_MSK;       // 16: Correctable Errors Interrupt Mask
    uint8_t HAERRIE;       // 15: Host Access Error Injection Enable
    uint8_t FAERRIE;       // 14: FlexCAN Access Error Injection Enable
    uint8_t EXTERRIE;      // 13: Extended Error Injection Enable
    uint8_t RERRDIS;       // 9: Error Report Disable
    uint8_t ECCDIS;        // 8: Error Correction Disable
    uint8_t NCEFAFRZ;      // 7: Noncorrectable Errors in FlexCAN Access Put Chip in Freeze Mode
} CAN_ErrorControl;


typedef struct Error_injection{
uint16_t INJADDR_H; //13-2 : Error Injection Address High
uint8_t INJADDR_L; //1-0 : Error Injection Address Low
}Error_injection;


typedef struct ParityFlipPattern{
    uint8_t PFLIP3;  // 28-24: Parity Flip Pattern for Byte 3 (Most Significant)
    uint8_t PFLIP2;  // 20-16: Parity Flip Pattern for Byte 2
    uint8_t PFLIP1;  // 12-8: Parity Flip Pattern for Byte 1
    uint8_t PFLIP0;  // 4-0: Parity Flip Pattern for Byte 0 (Least Significant)
} ParityFlipPattern;


typedef struct  ErrorStatus{
    uint8_t NCE;       // 24: Noncorrectable Error (1 bit)
    uint8_t SAID;      // 18-16: SAID (3 bits)
    uint16_t ERRADDR;  // 13-0: Address Where Error Detected (14 bits)
} ErrorStatus;


typedef struct {
    uint8_t BE3;   // 31: Byte Enabled for Byte 3 (Most Significant)
    uint8_t SYND3; // 28-24: Error Syndrome for Byte 3 (Most Significant)
    uint8_t BE2;   // 23: Byte Enabled for Byte 2
    uint8_t SYND2; // 20-16: Error Syndrome for Byte 2
    uint8_t BE1;   // 15: Byte Enabled for Byte 1
    uint8_t SYND1; // 12-8: Error Syndrome for Byte 1
    uint8_t BE0;   // 7: Byte Enabled for Byte 0 (Least Significant)
    uint8_t SYND0; // 4-0: Error Syndrome for Byte 0 (Least Significant)
} ErrorSyndrome;


typedef struct ErrorInterruptFlags{
    uint8_t HANCEIF;   // 19: Host Access with Noncorrectable Error Interrupt Flag
    uint8_t FANCEIF;   // 18: FlexCAN Access with Noncorrectable Error Interrupt Flag
    uint8_t CEIF;      // 16: Correctable Error Interrupt Flag
    uint8_t reserved1; // Reserved bits (15-3)
    uint8_t HANCEIOF;  // 3: Host Access With Noncorrectable Error Interrupt Overrun Flag
    uint8_t FANCEIOF;  // 2: FlexCAN Access with Noncorrectable Error Interrupt Overrun Flag
    uint8_t CEIOF;     // 0: Correctable Error Interrupt Overrun Flag
} ErrorInterruptFlags;


typedef struct ExtendedPrescalerFactors {
    uint8_t EDPRESDIV; // 25-16: Extended Data Phase Prescaler Division Factor
    uint16_t ENPRESDIV; // 9-0: Extended Nominal Prescaler Division Factor
} ExtendedPrescalerFactors;


typedef struct NominalTiming{
    uint8_t NRJW;   // 28-22: Nominal Resynchronization Jump Width (7 bits)
    uint8_t NTSEG2; // 18-12: Nominal Time Segment 2 (7 bits)
    uint8_t NTSEG1; // 7-0: Nominal Time Segment 1 (8 bits)
} NominalTiming;

typedef struct DataPhaseTiming{
    uint8_t DRJW;   // 25-22: Data Phase Resynchronization Jump Width (4 bits)
    uint8_t DTSEG2; // 15-12: Data Phase Time Segment 2 (4 bits)
    uint8_t DTSEG1; // 4-0: Data Phase Segment 1 (5 bits)
} DataPhaseTiming;

typedef struct TransceiverDelayCompensation{
    uint8_t ETDCEN;    // 31: Transceiver Delay Compensation Enable (1 bit)
    uint8_t TDMDIS;    // 30: Transceiver Delay Measurement Disable (1 bit)
    uint8_t ETDCOFF;   // 22-16: Enhanced Transceiver Delay Compensation Offset (7 bits)
    uint8_t ETDCFAIL;  // 15: Transceiver Delay Compensation Fail (1 bit)
    uint8_t ETDCVAL;   // 7-0: Enhanced Transceiver Delay Compensation Value (8 bits)
} TransceiverDelayCompensation;

typedef struct TransceiverDelayCompensation_fd{
    uint8_t FDRATE;    // 31: Bit Rate Switch Enable (1 bit)
    uint8_t MBDSR2;    // 23-22: Message Buffer Data Size for Region 2 (2 bits)
    uint8_t MBDSR1;    // 20-19: Message Buffer Data Size for Region 1 (2 bits)
    uint8_t MBDSR0;    // 17-16: Message Buffer Data Size for Region 0 (2 bits)
    uint8_t TDCEN;     // 15: Transceiver Delay Compensation Enable (1 bit)
    uint8_t TDCFAIL;   // 14: Transceiver Delay Compensation Fail (1 bit)
    uint8_t TDCOFF;    // 12-8: Transceiver Delay Compensation Offset (5 bits)
    uint8_t TDCVAL;    // 5-0: Transceiver Delay Compensation Value (6 bits)
}TransceiverDelayCompensation_fd;



typedef struct FastPrescalerConfig{
    uint8_t FPRESDIV;   // 29-20: Fast Prescaler Division Factor (10 bits)
    uint8_t FRJW;       // 18-16: Fast Resync Jump Width (3 bits)
    uint8_t FPROPSEG;   // 14-10: Fast Propagation Segment (5 bits)
    uint8_t FPSEG1;     // 7-5: Fast Phase Segment 1 (3 bits)
    uint8_t FPSEG2;     // 2-0: Fast Phase Segment 2 (3 bits)
} FastPrescalerConfig;

typedef struct  FDCRC_Config{
    uint8_t FD_MBCRC;  // 30-24: CRC Message Buffer Number for FD_TXCRC (7 bits)
    uint32_t FD_TXCRC; // 20-0: Extended Transmitted CRC value (21 bits)
} FDCRC_Config;



typedef struct Enhanced_RX_FIFO_Config{
    uint8_t ERFWM;      // 4-0: Enhanced RX FIFO Watermark (5 bits)
    uint8_t NFE;        // 13-8: Number of Enhanced RX FIFO Filter Elements (6 bits)
    uint8_t NEXIF;      // 22-16: Number of Extended ID Filter Elements (7 bits)
    uint8_t DMALW;      // 30-26: DMA Last Word (5 bits)
    uint8_t ERFEN;      // 31: Enhanced RX FIFO enable (1 bit)
} Enhanced_RX_FIFO_Config;


typedef struct Enhanced_RX_FIFO_Interrupt_Config{
    uint8_t ERFDAIE;   // Bit 28: Enhanced RX FIFO Data Available Interrupt Enable
    uint8_t ERFWMIIE;  // Bit 29: Enhanced RX FIFO Watermark Indication Interrupt Enable
    uint8_t ERFOVFIE;  // Bit 30: Enhanced RX FIFO Overflow Interrupt Enable
    uint8_t ERFUFWIE;  // Bit 31: Enhanced RX FIFO Underflow Interrupt Enable
} Enhanced_RX_FIFO_Interrupt_Config;


typedef struct Enhanced_RX_FIFO_Status{
    uint8_t ERFEL;    // Bits 5-0: Enhanced RX FIFO Elements
    uint8_t ERFF;     // Bit 16: Enhanced RX FIFO Full Flag
    uint8_t ERFE;     // Bit 17: Enhanced RX FIFO Empty Flag
    uint8_t ERFDA;    // Bit 28: Enhanced RX FIFO Data Available Flag
    uint8_t ERFWMI;   // Bit 29: Enhanced RX FIFO Watermark Indication Flag
    uint8_t ERFOVF;   // Bit 30: Enhanced RX FIFO Overflow Flag
    uint8_t ERFUFW;   // Bit 31: Enhanced RX FIFO Underflow Flag
} Enhanced_RX_FIFO_Status;

#endif