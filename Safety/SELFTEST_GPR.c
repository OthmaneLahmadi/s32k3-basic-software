#include "SELFTEST_GPR.h"
#include <stdint.h>


/*
Configuration register (CONFIG_REG)
Offset
Register Offset
CONFIG_REG 0h
*/
void set_CONFIG_REG(CONFIG_REG_t config) {
    uint32_t value = 0;
    value |= (uint32_t)((config.PCS_STEP_SIZE & 0x7) << 4);
    value |= (uint32_t)((config.PCS_ENABLE_START & 0x1) << 7);
    value |= (uint32_t)((config.PCS_ENABLE_END & 0x1) << 8);
    *CONFIG_REG = value;
}

CONFIG_REG_t get_CONFIG_REG(void) {
    CONFIG_REG_t config;
    uint32_t value = *CONFIG_REG;
    config.PCS_STEP_SIZE = (uint8_t)((value >> 4) & 0x7);
    config.PCS_ENABLE_START = (uint8_t)((value >> 7) & 0x1);
    config.PCS_ENABLE_END = (uint8_t)((value >> 8) & 0x1);
    return config;
}
//--------------------------------

/*
LBIST Program (LBIST_PROG_REG)
Offset
Register Offset
LBIST_PROG_REG 14h
Function
Configures the LBIST shift count.
*/

uint8_t get_LBIST_Program(){
return (uint8_t)(*LBIST_PROG_REG & 0xFF);
}

void set_LBIST_Program(uint8_t lbist){
*LBIST_PROG_REG&=~0xFF;
*LBIST_PROG_REG|=lbist;
}