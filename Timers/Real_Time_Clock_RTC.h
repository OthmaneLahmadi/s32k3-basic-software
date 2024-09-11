#ifndef _RTC_H
#define _RTC_H

#include <stdint.h>

#define RTC_Base 0x40288000

#define RTCSUPV  (volatile uint32_t*)(RTC_BASE0 + 0x00)// RTC Supervisor Control Register
#define RTCC    (volatile uint32_t*)(RTC_BASE0 + 0x04)// RTC Control Register
#define RTCS    (volatile uint32_t*)(RTC_BASE0 + 0x08)// RTC Status Register
#define RTCCNT  (volatile uint32_t*)(RTC_BASE0 + 0x0C)// RTC Counter Register
#define APIVAL  (volatile uint32_t*)(RTC_BASE0 + 0x10)// API Compare Value Register
#define RTCVAL  (volatile uint32_t*)(RTC_BASE0 + 0x14)// RTC Compare Value Register


typedef struct RTC_CONTROL{
    uint8_t  TRIG_EN      ;  // Trigger enable for Analog Comparator
    uint8_t  DIV32EN      ;  // Divide by 32 enable
    uint8_t  DIV512EN     ;  // Divide by 512 enable
    uint8_t  CLKSEL       ;  // Clock select (needs 2 bits)
    uint8_t  APIIE        ;  // API Interrupt Enable
    uint8_t  APIEN        ;  // Autonomous Periodic Interrupt Enable
    uint8_t  ROVREN       ;  // Counter Roll Over wakeup/Interrupt Enable
    uint8_t  FRZEN        ;  // Freeze Enable Bit
    uint8_t  RTCIE        ;  // RTC Interrupt Enable
    uint8_t  CNTEN        ;  // Counter Enable
} RTC_CONTROL;

typedef struct RTC_STATUS{
    uint8_t RTCF       ;  // RTC Interrupt Flag
    uint8_t INV_RTC    ;  // Invalid RTC write
    uint8_t INV_API    ;  // Invalid APIVAL write
    uint8_t APIF       ;  // API Interrupt Flag
    uint8_t ROVRF      ;  // Counter Roll Over Interrupt Flag
} RTC_STATUS;

#endif