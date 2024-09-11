#ifndef H_FCCU_H
#define H_FCCU_H

#include <stdint.h>

#define FCCU_BASE 0x40384000

#define CTRL_FCCU               (volatile uint32_t*)(FCCU_BASE + 0x00) // Control Register
#define CTRLK              (volatile uint32_t*)(FCCU_BASE + 0x04) // Control Key Register
#define CFG                (volatile uint32_t*)(FCCU_BASE + 0x08) // Configuration Register
#define NCF_CFG0           (volatile uint32_t*)(FCCU_BASE + 0x1C) // Non-critical Fault Configuration 0 Register
#define NCFS_CFG0          (volatile uint32_t*)(FCCU_BASE + 0x4C) // Non-critical Fault-State Configuration 0 Register
#define NCF_S0             (volatile uint32_t*)(FCCU_BASE + 0x80) // Non-critical Fault Status 0 Register
#define NCFK               (volatile uint32_t*)(FCCU_BASE + 0x90) // Non-critical Fault Key Register
#define NCF_E0             (volatile uint32_t*)(FCCU_BASE + 0x94) // Non-critical Fault Enable 0 Register
#define NCF_TOE0           (volatile uint32_t*)(FCCU_BASE + 0xA4) // Non-critical-Fault Alarm-State Timeout Enable 0 Register
#define NCF_TO             (volatile uint32_t*)(FCCU_BASE + 0xB4) // Non-critical-Fault Alarm-State Timeout Interval Register
#define CFG_TO             (volatile uint32_t*)(FCCU_BASE + 0xB8) // Configuration-State Timeout Interval Register
#define EINOUT             (volatile uint32_t*)(FCCU_BASE + 0xBC) // IO Control Register
#define STAT               (volatile uint32_t*)(FCCU_BASE + 0xC0) // Status Register
#define N2AF_STATUS        (volatile uint32_t*)(FCCU_BASE + 0xC4) // Normal-to-Alarm Freeze Status Register
#define A2FF_STATUS        (volatile uint32_t*)(FCCU_BASE + 0xC8) // Alarm-to-Fault Freeze Status Register
#define N2FF_STATUS        (volatile uint32_t*)(FCCU_BASE + 0xCC) // Normal-to-Fault Freeze Status Register
#define F2AF_STATUS        (volatile uint32_t*)(FCCU_BASE + 0xD0) // Fault-to-Alarm Freeze Status Register
#define NCFF               (volatile uint32_t*)(FCCU_BASE + 0xDC) // Non-critical Fault Fake Register
#define IRQ_STAT           (volatile uint32_t*)(FCCU_BASE + 0xE0) // IRQ Status Register
#define IRQ_EN             (volatile uint32_t*)(FCCU_BASE + 0xE4) // IRQ Enable Register
#define TRANS_LOCK         (volatile uint32_t*)(FCCU_BASE + 0xF0) // Transient Configuration Lock Register
#define PERMNT_LOCK        (volatile uint32_t*)(FCCU_BASE + 0xF4) // Permanent Configuration Lock Register
#define DELTA_T            (volatile uint32_t*)(FCCU_BASE + 0xF8) // Delta T Register
#define IRQ_ALARM_EN0      (volatile uint32_t*)(FCCU_BASE + 0xFC) // Non-critical Alarm-State Interrupt-Request Enable 0 Register
#define NMI_EN0            (volatile uint32_t*)(FCCU_BASE + 0x10C)// Non-critical Fault-State Non-maskable-Interrupt-Request Enable 0 Register
#define EOUT_SIG_EN0       (volatile uint32_t*)(FCCU_BASE + 0x11C)// Non-critical Fault-State EOUT Signaling Enable 0 Register
#define TMR_ALARM          (volatile uint32_t*)(FCCU_BASE + 0x12C)// Alarm-State Timer Register
#define TMR_CFG            (volatile uint32_t*)(FCCU_BASE + 0x134)// Configuration-State Timer Register
#define TMR_ETMR           (volatile uint32_t*)(FCCU_BASE + 0x138)// Fault-Output Timer Register

typedef struct CTRL_t{
    uint8_t OPR;    // Bits 4-0
    uint8_t OPS;    // Bits 7-6
    uint8_t DEBUG;  // Bit 9
} CTRL_t;


typedef struct CFG_t{
    uint8_t FOM;                  // Bits 8-6
    uint8_t PS;                   // Bit 9
    uint8_t CM;                   // Bit 11
    uint8_t FCCU_SET_CLEAR;       // Bits 23-22
    uint8_t FCCU_SET_AFTER_RESET; // Bit 24
} CFG_t;

typedef struct EINOUT_t{
    uint8_t EOUT0 ;  // Bit 0
    uint8_t EOUT1 ;  // Bit 1
    uint8_t EIN0  ;  // Bit 4
    uint8_t EIN1  ;  // Bit 5
} EINOUT_t;

typedef struct STAT_t{
    uint8_t STATUS ;         // Bits 2-0
    uint8_t ESTAT  ;         // Bit 3
    uint8_t PhysicErrorPin ; // Bits 5-4
} STAT_t;

typedef struct A2FF_STATUS_t{
    uint8_t AFFS   ; // Bits 7-0
    uint8_t AF_SRC ; // Bits 9-8
} A2FF_STATUS_t;

typedef struct N2FF_STATUS_t{
    uint8_t NFFS   ; // Bits 7-0
    uint8_t NF_SRC ; // Bits 9-8
} N2FF_STATUS_t;

typedef struct IRQ_STAT_t {
    uint8_t CFG_TO_STAT ; // Bit 0
    uint8_t ALRM_STAT   ; // Bit 1
    uint8_t NMI_STAT    ; // Bit 2
} IRQ_STAT_t;



#endif 