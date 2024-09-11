#include "CRC.h"
#include <stdint.h>

//------------------------
/*
CRC Data (DATA)
Offset
Register Offset
DATA 0h
Function
Contains the value of the seed, data, and checksum. When CTRL[WAS] = 1 , any write to this register is regarded as the seed
value. When CTRL[WAS] becomes 0, any write to this register is regarded as data for general CRC computation.
In 16-bit CRC mode, the DATA[HU] and DATA[HL] are not used for programming the seed value, and reads of these fields return
an indeterminate value. In 32-bit CRC mode, all fields are used for programming the seed value.
When programming data values, you can write 8 bits, 16 bits, or 32 bits at a time, provided all bytes are contiguous; with the MSB
of data value written first.
After writing all data values, you can read the CRC result from this register. In 16-bit CRC mode, the CRC result is available
in DATA[LU] and DATA[LL]. In 32-bit CRC mode, all fields contain the result. Reads of this register, at any time, return the
intermediate CRC value, if the CRC module is configured.

*/


CRC_DATA get_CRC_DATA(void) {
    CRC_DATA data;
    uint32_t reg_value = *CRC_DATA;

    data.HU = (reg_value >> 24) & 0xFF;
    data.HL = (reg_value >> 16) & 0xFF;
    data.LU = (reg_value >> 8) & 0xFF;
    data.LL = reg_value & 0xFF;

    return data;
}

// Function to set the value of the CRC_DATA register
void set_CRC_DATA(CRC_DATA data) {
    uint32_t reg_value = 0;

    reg_value |= (uint32_t)(data.HU) << 24;
    reg_value |= (uint32_t)(data.HL) << 16;
    reg_value |= (uint32_t)(data.LU) << 8;
    reg_value |= (uint32_t)(data.LL);

    *CRC_DATA = reg_value;
}

//----------------------------------------------

/*
CRC Polynomial (GPOLY)
Offset
Register Offset
GPOLY 4h
Function
Contains the value of the polynomial for CRC calculation.
• Contains the upper 16 bits of the CRC polynomial that are used only in 32-bit CRC mode. Writes to this field are ignored in
16-bit CRC mode.
• Contains the lower 16 bits of the CRC polynomial that are used in both 16-bit and 32-bit CRC modes
*/

void set_CRC_GPOLY(CRC_polynome polynome) {
    uint32_t value = ((uint32_t)(polynome.HIGH) << 16) | (uint32_t)(polynome.LOW);
    *CRC_GPOLY = value;
}

CRC_polynome get_CRC_GPOLY(void) {
    CRC_polynome polynome;
    uint32_t value = *CRC_GPOLY;
    polynome.HIGH = (uint16_t)(value >> 16); // Extract bits 31-16
    polynome.LOW = (uint16_t)(value & 0xFFFF); // Extract bits 15-0
    return polynome;
}
//-------------------------------------------

/*
CRC Control (CTRL)
Offset
Register Offset
CTRL 8h
Function
Controls the configuration and working of CRC module. You must write 1 to the appropriate fields of this register before
starting a new CRC calculation, which you can initialize by writing 1 to CTRL[WAS] and then writing the seed into CRC Data
(DATA).
*/

void set_CRC_CTRL(CRC_CTRL_t config) {
    uint32_t value = 0;
    
    value |= ((uint32_t)(config.TOT & 0x3) << 30);
    value |= ((uint32_t)(config.TOTR & 0x3) << 28);
    value |= ((uint32_t)(config.FXOR & 0x1) << 26);
    value |= ((uint32_t)(config.WAS & 0x1) << 25);
    value |= ((uint32_t)(config.TCRC & 0x1) << 24);
    *CRC_CTRL = value;
}

CRC_CTRL_t get_CRC_CTRL(void) {
    CRC_CTRL_t config;
    uint32_t value = *CRC_CTRL;
    config.TOT = (uint8_t)((value >> 30) & 0x3);
    config.TOTR = (uint8_t)((value >> 28) & 0x3);
    config.FXOR = (uint8_t)((value >> 26) & 0x1);
    config.WAS = (uint8_t)((value >> 25) & 0x1);
    config.TCRC = (uint8_t)((value >> 24) & 0x1);    
    return config;
}
