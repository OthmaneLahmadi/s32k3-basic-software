#ifndef _SELFTEST_GPR_H
#define _SELFTEST_GPR_H
#include <stdint.h>


#define SELFTEST_GPR_BASE 0x403B0000
#define CONFIG_REG      (volatile uint32_t*)(SELFTEST_GPR_BASE + 0x0)
#define LBIST_PROG_REG  (volatile uint32_t*)(SELFTEST_GPR_BASE + 0x14)

typedef struct CONFIG_REG_t{
    uint8_t PCS_STEP_SIZE ; // Bits 6-4
    uint8_t PCS_ENABLE_START ; // Bit 7
    uint8_t PCS_ENABLE_END   ; // Bit 8
} CONFIG_REG_t;


#endif 