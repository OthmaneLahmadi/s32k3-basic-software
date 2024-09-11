#ifndef _PIT_H
#define _PIT_H


#define PIT_BASE0 0x40000000u

// Register definitions
#define PIT_MCR                 (volatile uint32_t*)(PIT_BASE0 + 0x00)// PIT Module Control
#define PIT_LTMR64H             (volatile uint32_t*)(PIT_BASE0 + 0xE0)// PIT Upper Lifetimer
#define PIT_LTMR64L             (volatile uint32_t*)(PIT_BASE0 + 0xE4)// PIT Lower Lifetimer
#define PIT_RTI_LDVAL_STAT      (volatile uint32_t*)(PIT_BASE0 + 0xEC)// RTI Timer Load Value Sync Status
#define PIT_RTI_LDVAL           (volatile uint32_t*)(PIT_BASE0 + 0xF0)// RTI Timer Load Value
#define PIT_RTI_CVAL            (volatile uint32_t*)(PIT_BASE0 + 0xF4)// Current RTI Timer Value
#define PIT_RTI_TCTRL           (volatile uint32_t*)(PIT_BASE0 + 0xF8)// RTI Timer Control
#define PIT_RTI_TFLG            (volatile uint32_t*)(PIT_BASE0 + 0xFC)// RTI Timer Interrupt Flag

#define PIT_LDVAL(n)              (volatile uint32_t*)(PIT_BASE0 + 0x100+n*0x10)
#define PIT_CVAL(n)               (volatile uint32_t*)(PIT_BASE0 + 0x104+n*0x10)

#define PIT_TCTRL(n)              (volatile uint32_t*)(PIT_BASE0 + 0x108+n*0x10)
#define PIT_TFLG(n)               (volatile uint32_t*)(PIT_BASE0 + 0x10C+n*0x10)// Timer Flag 0


typedef struct PIT_MCR_t{
    uint8_t FRZ ;       // Freeze (bit 0)
    uint8_t MDIS ;      // Module Disable for PIT (bit 1)
    uint8_t MDIS_RTI ;  // Module Disable for RTI (bit 2)

} PIT_MCR_t;

typedef struct RTI_control{

uint8_t TIE;
uint8_t TEN;
}RTI_control;

typedef struct Control_timer{
    uint8_t TEN ;   // Timer Enable (bit 0)
    uint8_t TIE ;   // Timer Interrupt Enable (bit 1)
    uint8_t CHN ;   // Chain Mode (bit 2)
} Control_timer;


#endif