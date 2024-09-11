#ifndef _TIMER_H
#define _TIMER_H

#define SWT_BASE0 0x40270000;

#define CR  ((volatile uint32_t*)(SWT_BASE0 + 0x00))  // Control Register
#define IR  ((volatile uint32_t*)(SWT_BASE0 + 0x04))  // Interrupt Register
#define TO  ((volatile uint32_t*)(SWT_BASE0 + 0x08))  // Timeout Register
#define WN  ((volatile uint32_t*)(SWT_BASE0 + 0x0C))  // Window Register
#define SR  ((volatile uint32_t*)(SWT_BASE0 + 0x10))  // Service Register
#define CO  ((volatile uint32_t*)(SWT_BASE0 + 0x14))  // Counter Output Register
#define SK  ((volatile uint32_t*)(SWT_BASE0 + 0x18))  // Service Key Register
#define RRR ((volatile uint32_t*)(SWT_BASE0 + 0x1C))  // Event Request Register



typedef struct watchdog_register_t{
    uint8_t MAP0;  // Master Access Protection 0 (bit 31)
    uint8_t MAP1;  // Master Access Protection 1 (bit 30)
    uint8_t MAP2;  // Master Access Protection 2 (bit 29)
    uint8_t MAP3;  // Master Access Protection 3 (bit 28)
    uint8_t MAP4;  // Master Access Protection 4 (bit 27)
    uint8_t MAP5;  // Master Access Protection 5 (bit 26)
    uint8_t MAP6;  // Master Access Protection 6 (bit 25)
    uint8_t MAP7;  // Master Access Protection 7 (bit 24)

    uint16_t Reserved1; // Reserved (bits 12-23)

    uint8_t SMD;  // Service Mode (bits 10-9)
    uint8_t RIA;  // Reset on Invalid Access (bit 8)
    uint8_t WND;  // Window Mode (bit 7)
    uint8_t ITR;  // Interrupt Then Reset Request (bit 6)
    uint8_t HLK;  // Hard Lock (bit 5)
    uint8_t SLK;  // Soft Lock (bit 4)
    uint8_t Reserved2; // Reserved (bit 3)

    uint8_t STP;  // Stop Mode Control (bit 2)
    uint8_t FRZ;  // Debug Mode Control (bit 1)
    uint8_t WEN;  // Watchdog Enable (bit 0)
} watchdog_register_t;


#endif