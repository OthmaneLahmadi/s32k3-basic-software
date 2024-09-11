#ifndef _LPUART_
#define _LPUART_


#define LPUART_BASE0 (volatile uint32_t*)(0x40328000)
#define VERID        (volatile uint32_t*)(LPUART_BASE0 + 0x00)
#define PARAM        (volatile uint32_t*)(LPUART_BASE0 + 0x04)
#define GLOBAL       (volatile uint32_t*)(LPUART_BASE0 + 0x08)
#define PINCFG       (volatile uint32_t*)(LPUART_BASE0 + 0x0C)
#define BAUD         (volatile uint32_t*)(LPUART_BASE0 + 0x10)
#define STAT         (volatile uint32_t*)(LPUART_BASE0 + 0x14)
#define CTRL         (volatile uint32_t*)(LPUART_BASE0 + 0x18)
#define DATA         (volatile uint32_t*)(LPUART_BASE0 + 0x1C)
#define MATCH        (volatile uint32_t*)(LPUART_BASE0 + 0x20)
#define MODIR        (volatile uint32_t*)(LPUART_BASE0 + 0x24)
#define FIFO         (volatile uint32_t*)(LPUART_BASE0 + 0x28)
#define WATER        (volatile uint32_t*)(LPUART_BASE0 + 0x2C)
#define DATARO       (volatile uint32_t*)(LPUART_BASE0 + 0x30)
#define MCR          (volatile uint32_t*)(LPUART_BASE0 + 0x40)
#define MSR          (volatile uint32_t*)(LPUART_BASE0 + 0x44)
#define REIR         (volatile uint32_t*)(LPUART_BASE0 + 0x48)
#define TEIR         (volatile uint32_t*)(LPUART_BASE0 + 0x4C)
#define HDCR         (volatile uint32_t*)(LPUART_BASE0 + 0x50)
#define TOCR         (volatile uint32_t*)(LPUART_BASE0 + 0x58)
#define TOSR         (volatile uint32_t*)(LPUART_BASE0 + 0x5C)
#define TIMEOUT0     (volatile uint32_t*)(LPUART_BASE0 + 0x60)
#define TIMEOUT1     (volatile uint32_t*)(LPUART_BASE0 + 0x64)
#define TIMEOUT2     (volatile uint32_t*)(LPUART_BASE0 + 0x68)
#define TIMEOUT3     (volatile uint32_t*)(LPUART_BASE0 + 0x6C)
#define TCBR(n)      ((volatile uint32_t*)(LPUART_BASE0 + 0x200 + ((n) * 0x04)))
#define TDBR(n)      ((volatile uint32_t*)(LPUART_BASE0 + 0x400 + ((n) * 0x04)))


typedef struct VersionRegister{
    uint16_t feature;  // Bits 15-0
    uint8_t minor;    // Bits 23-16
    uint8_t major;    // Bits 31-24
} VersionRegister;


typedef struct parameter{

uint8_t  RXFIFO; // 15-8 Receive FIFO Size
uint8_t  TXFIFO; // 7-0 Transmit FIFO Size
}parameter;


typedef struct BaudeConfig{
    uint16_t SBR;       // Baud Rate Modulo Divisor (bits 12-0)
    uint8_t  SBNS;      // Stop Bit Number Select (bit 13)
    uint8_t  RXEDGIE;   // RX Input Active Edge Interrupt Enable (bit 14)
    uint8_t  LBKDIE;    // LIN Break Detect Interrupt Enable (bit 15)
    uint8_t  RESYNCDIS; // Resynchronization Disable (bit 16)
    uint8_t  BOTHEDGE;  // Both Edge Sampling (bit 17)
    uint8_t  MATCFG;    // Match Configuration (bits 18-19)
    uint8_t  RDMAE;     // Receiver Full DMA Enable (bit 21)
    uint8_t  TDMAE;     // Transmitter DMA Enable (bit 23)
    uint8_t  OSR;       // Oversampling Ratio (bits 24-28)
    uint8_t  M10;       // 10-Bit Mode Select (bit 29)
    uint8_t  MAEN2;     // Match Address Mode Enable 2 (bit 30)
    uint8_t  MAEN1;     // Match Address Mode Enable 1 (bit 31)
} BaudeConfig;


typedef struct StatusRegister{
    uint32_t LBKDIF   ; // LIN Break Detect Interrupt Flag (bit 31)
    uint32_t RXEDGIF  ; // RXD Pin Active Edge Interrupt Flag (bit 30)
    uint32_t MSBF     ; // MSB First (bit 29)
    uint32_t RXINV    ; // Receive Data Inversion (bit 28)
    uint32_t RWUID    ; // Receive Wake Up Idle Detect (bit 27)
    uint32_t BRK13    ; // Break Character Generation Length (bit 26)
    uint32_t LBKDE    ; // LIN Break Detection Enable (bit 25)
    uint32_t RAF      ; // Receiver Active Flag (bit 24)
    uint32_t TDRE     ; // Transmit Data Register Empty Flag (bit 23)
    uint32_t TC       ; // Transmission Complete Flag (bit 22)
    uint32_t RDRF     ; // Receive Data Register Full Flag (bit 21)
    uint32_t IDLE     ; // Idle Line Flag (bit 20)
    uint32_t OR       ; // Receiver Overrun Flag (bit 19)
    uint32_t NF       ; // Noise Flag (bit 18)
    uint32_t FE       ; // Framing Error Flag (bit 17)
    uint32_t PF       ; // Parity Error Flag (bit 16)
    uint32_t MA1F     ; // Match 1 Flag (bit 15)
    uint32_t MA2F     ; // Match 2 Flag (bit 14)
    uint32_t Reserved ; // Reserved bits (bits 13-9)
    uint32_t TSF      ; // Timeout Status Flag (bit 9)
    uint32_t MSF      ; // MODEM Status Flag (bit 8)
    uint32_t AME      ; // Address Mark Enable (bit 1)
    uint32_t LBKFE    ; // LIN Break Flag Enable (bit 0)
} StatusRegister;


typedef struct ControlConfig {
    uint8_t  R8T9      ; // Receive Bit 8 Transmit Bit 9 (bit 31)
    uint8_t  R9T8      ; // Receive Bit 9 Transmit Bit 8 (bit 30)
    uint8_t  TXDIR     ; // TXD Pin Direction in Single-Wire Mode (bit 29)
    uint8_t  TXINV     ; // Transmit Data Inversion (bit 28)
    uint8_t  ORIE      ; // Overrun Interrupt Enable (bit 27)
    uint8_t  NEIE      ; // Noise Error Interrupt Enable (bit 26)
    uint8_t  FEIE      ; // Framing Error Interrupt Enable (bit 25)
    uint8_t  PEIE      ; // Parity Error Interrupt Enable (bit 24)
    uint8_t  TIE       ; // Transmit Interrupt Enable (bit 23)
    uint8_t  TCIE      ; // Transmission Complete Interrupt Enable (bit 22)
    uint8_t  RIE       ; // Receiver Interrupt Enable (bit 21)
    uint8_t  ILIE      ; // Idle Line Interrupt Enable (bit 20)
    uint8_t  TE        ; // Transmitter Enable (bit 19)
    uint8_t  RE        ; // Receiver Enable (bit 18)
    uint8_t  RWU       ; // Receiver Wake-Up Control (bit 17)
    uint8_t  SBK       ; // Send Break (bit 16)
    uint8_t  MA1IE     ; // Match 1 (MA1F) Interrupt Enable (bit 15)
    uint8_t  MA2IE     ; // Match 2 (MA2F) Interrupt Enable (bit 14)
    uint8_t  Reserved1 ; // Reserved bits (bits 11-9)
    uint8_t  M7        ; // 7-Bit Mode Select (bit 11)
    uint8_t  IDLECFG   ; // Idle Configuration (bits 10-8)
    uint8_t  LOOPS     ; // Loop Mode Select (bit 7)
    uint8_t  DOZEEN    ; // Doze Mode (bit 6)
    uint8_t  RSRC      ; // Receiver Source Select (bit 5)
    uint8_t  M         ; // 9-Bit Or 8-Bit Mode Select (bit 4)
    uint8_t  WAKE      ; // Receiver Wake-Up Method Select (bit 3)
    uint8_t  ILT       ; // Idle Line Type Select (bit 2)
    uint8_t  PE        ; // Parity Enable (bit 1)
    uint8_t  PT        ; // Parity Type (bit 0)
} ControlConfig;



typedef struct DATA_cfg {
    uint8_t  NOISY    ; // Noisy Data Received (bit 15)
    uint8_t  PARITYE  ; // Parity Error (bit 14)
    uint8_t  FRETSC   ; // Frame Error Transmit Special Character (bit 13)
    uint8_t  RXEMPT   ; // Receive Buffer Empty (bit 12)
    uint8_t  IDLINE   ; // Idle Line (bit 11)
    uint8_t  LINBRK   ; // LIN Break (bit 10)
    uint8_t  R9T9     ; // Read receive FIFO bit 9 or write transmit FIFO bit 9 (bit 9)
    uint8_t  R8T8     ; // Read receive FIFO bit 8 or write transmit FIFO bit 8 (bit 8)
    uint8_t  R7T7     ; // Read receive FIFO bit 7 or write transmit FIFO bit 7 (bit 7)
    uint8_t  R6T6     ; // Read receive FIFO bit 6 or write transmit FIFO bit 6 (bit 6)
    uint8_t  R5T5     ; // Read receive FIFO bit 5 or write transmit FIFO bit 5 (bit 5)
    uint8_t  R4T4     ; // Read receive FIFO bit 4 or write transmit FIFO bit 4 (bit 4)
    uint8_t  R3T3     ; // Read receive FIFO bit 3 or write transmit FIFO bit 3 (bit 3)
    uint8_t  R2T2     ; // Read receive FIFO bit 2 or write transmit FIFO bit 2 (bit 2)
    uint8_t  R1T1     ; // Read receive FIFO bit 1 or write transmit FIFO bit 1 (bit 1)
    uint8_t  R0T0     ; // Read receive FIFO bit 0 or write transmit FIFO bit 0 (bit 0)
} DATA_cfg;


typedef struct MatchAddressRegister {
    uint16_t MA1;   // Match Address 1 (bits 9-0)
    uint16_t MA2;   // Match Address 2 (bits 25-16)
} MatchAddressRegister;


typedef struct Setting_MODEM {
    uint8_t  TXCTSE   ; // Transmitter CTS Enable (bit 0)
    uint8_t  TXRTSE   ; // Transmitter RTS Enable (bit 1)
    uint8_t  TXRTSPOL ; // Transmitter RTS Polarity (bit 2)
    uint8_t  RXRTSE   ; // Receiver RTS Enable (bit 3)
    uint8_t  TXCTSC   ; // Transmit CTS Configuration (bit 4)
    uint8_t  TXCTSSRC ; // Transmit CTS Source (bit 5)
    uint8_t  Reserved ; // Reserved bits (bits 7-6)
    uint8_t  RTSWATER ; // Receive RTS Configuration (bits 11-8)
    uint8_t  TNP      ; // Transmitter Narrow Pulse (bits 17-16)
    uint8_t  IREN     ; // IR Enable (bit 18)
} Setting_MODEM;


typedef struct FIFORegister {
    uint8_t  RXFIFOSIZE    ; // Receive FIFO Buffer Depth (bits 2-0)
    uint8_t  RXFE          ; // Receive FIFO Enable (bit 3)
    uint8_t  TXFIFOSIZE    ; // Transmit FIFO Buffer Depth (bits 6-4)
    uint8_t  TXFE          ; // Transmit FIFO Enable (bit 7)
    uint8_t  RXUFE         ; // Receive FIFO Underflow Interrupt Enable (bit 8)
    uint8_t  TXOFE         ; // Transmit FIFO Overflow Interrupt Enable (bit 9)
    uint8_t  RXIDEN        ; // Receiver Idle Empty Enable (bits 12-10)
    uint8_t  RXFLUSH       ; // Receive FIFO Flush (bit 14)
    uint8_t  TXFLUSH       ; // Transmit FIFO Flush (bit 15)
    uint8_t  RXUF          ; // Receiver FIFO Underflow Flag (bit 16)
    uint8_t  TXOF          ; // Transmitter FIFO Overflow Flag (bit 17)
    uint8_t  RXEMPT        ; // Receive FIFO Or Buffer Empty (bit 22)
    uint8_t  TXEMPT        ; // Transmit FIFO Or Buffer Empty (bit 23)
} FIFORegister;

typedef struct WatermarkCounterRegister {
    uint8_t  TXWATER   ; // Transmit Watermark (bits 3-0)
    uint8_t  TXCOUNT   ; // Transmit Counter (bits 12-8)
    uint8_t  RXWATER   ; // Receive Watermark (bits 19-16)
    uint8_t  RXCOUNT   ; // Receive Counter (bits 28-24)
} WatermarkCounterRegister;



typedef struct MODEM_Control  {
    uint8_t CTS  ; // Clear To Send (bit 0)
    uint8_t DSR  ; // Data Set Ready (bit 1)
    uint8_t RIN  ; // Ring Indicator (bit 2)
    uint8_t DCD  ; // Data Carrier Detect (bit 3)
    uint8_t DTR  ; // Data Terminal Ready (bit 8)
    uint8_t RTS  ; // Request To Send (bit 9)
} MODEM_Control ;


typedef struct MODEM_Status {
    uint8_t DCTS ; // Delta Clear To Send (bit 0)
    uint8_t DDSR ; // Delta Data Set Ready (bit 1)
    uint8_t DRI  ; // Delta Ring Indicator (bit 2)
    uint8_t DDCD ; // Delta Data Carrier Detect (bit 3)
    uint8_t CTS  ; // Clear To Send (bit 4)
    uint8_t DSR  ; // Data Set Ready (bit 5)
    uint8_t RIN  ; // Ring Indicator (bit 6)
    uint8_t DCD  ; // Data Carrier Detect (bit 7)
} MODEM_Status;


typedef struct Half_Duplex_Control {
    uint8_t TXSTALL   ; // Transmit Stall (bit 0)
    uint8_t RXSEL     ; // Receive Select (bit 1)
    uint8_t RXWRMSK   ; // Receive FIFO Write Mask (bit 2)
    uint8_t RXMSK     ; // Receive Mask (bit 3)
    uint8_t Reserved  ; // Reserved bits (bits 7-4)
    uint8_t RTSEXT    ; // RTS Extended (bits 15-8)
} Half_Duplex_Control;


typedef struct TimeoutControl {
    uint8_t TOEN      ; // Timeout Enable (bits 3-0)
    uint8_t TOIE      ; // Timeout Interrupt Enable (bits 11-8)
    uint8_t Reserved  ; // Reserved bits (bits 15-12)
} TimeoutControl;

typedef struct TimeoutStatus {
    uint8_t TOZ       ; // Timeout Zero (bits 3-0)
    uint8_t TOF       ; // Timeout Flag (bits 11-8)
    uint8_t Reserved  ; // Reserved bits (bits 15-12)
} TimeoutStatus;


typedef struct Timeout {
    uint16_t TIMEOUT  ; // Timeout Value (bits 13-0)
    uint8_t  CFG      ; // Idle Configuration (bits 31-30)
    uint8_t  Reserved ; // Reserved bits (bits 29-14)
} Timeout;


typedef struct data_burs {
    uint8_t  DATA3; // Data3 (bits 31-24)
    uint8_t  DATA2; // Data2 (bits 23-16)
    uint8_t  DATA1; // Data1 (bits 15-8)
    uint8_t  DATA0; // Data0 (bits 7-0)
} data_burs;


#endif