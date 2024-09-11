#ifndef _STM_H
#define _STM_H

#include <stdint.h>

#define STM_BASE0 0x40274000




#define CR_STM     (volatile uint32_t*)(STM_BASE0 + 0x00) // Control Register
#define CNT        (volatile uint32_t*)(STM_BASE0 + 0x04) // Count Register


#define CCR(n)  (volatile uint32_t*)(STM_BASE0 + 0x10 * ((n) + 1))    // Channel Control n
#define CIR(n)  (volatile uint32_t*)(STM_BASE0 + 0x14 + 0x10 * (n))   // Channel Interrupt n
#define CMP(n)  (volatile uint32_t*)(STM_BASE0 + 0x18 + 0x10 * (n))   // Channel Compare n




typedef struct STM_Control{
    uint8_t TEN ;   // Timer Enable (bit 0)
    uint8_t FRZ ;   // Freeze (bit 1)
    uint8_t Reserved ; // Reserved (bits 2-7)

    uint8_t CPS ;   // Counter Prescaler (bits 8-15)

    uint16_t Reserved2 ; // Reserved (bits 16-31)
} STM_Control;



#endif;