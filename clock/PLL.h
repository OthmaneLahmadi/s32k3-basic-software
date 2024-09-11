#ifndef _PLL_H
#define _PLL_H


#include <stdint.h>

#define PLLDIG_BASE_ADDRESS     (volatile uint32_t*)(0x402E0000)
#define PLLCR                   (volatile uint32_t*)(PLLDIG_BASE_ADDRESS + 0x00)  // PLL Control
#define PLLSR                   (volatile uint32_t*)(PLLDIG_BASE_ADDRESS + 0x04)  // PLL Status
#define PLLDV                   (volatile uint32_t*)(PLLDIG_BASE_ADDRESS + 0x08)  // PLL Divider
#define PLLFM                   (volatile uint32_t*)(PLLDIG_BASE_ADDRESS + 0x0C)  // PLL Frequency Modulation
#define PLLFD                   (volatile uint32_t*)(PLLDIG_BASE_ADDRESS + 0x10)  // PLL Fractional Divider
#define PLLCAL2                 (volatile uint32_t*)(PLLDIG_BASE_ADDRESS + 0x18)  // PLL Calibration Register 2
#define PLLODIV_0               (volatile uint32_t*)(PLLDIG_BASE_ADDRESS + 0x80)  // PLL Output Divider 0
#define PLLODIV_1               (volatile uint32_t*)(PLLDIG_BASE_ADDRESS + 0x84)  // PLL Output Divider 1


typedef struct PLL_stats{
uint8_t LOL;
uint8_t LOCK;
}PLL_stats;



typedef struct PLL_DIV{
uint8_t ODIV2;
uint8_t RDIV;
uint8_t MFI;
}PLL_DIV;


typedef struct Frequency_modulation_cfg{
uint8_t SSCGBYP;
uint8_t SPREADCTL;
uint16_t STEPSIZE;
uint16_t STEPNO;
}Frequency_modulation_cfg;


typedef struct PLL_fraction_div_t{
    uint8_t SDMEN;  // Bit 30
    uint8_t SDM2;   // Bit 29
    uint8_t SDM3;   // Bit 28
    uint16_t MFN;   // Bits 14-0
} PLL_fraction_div_t;


typedef struct PLL_out_div {
    uint8_t DE;   // Bit 31
    uint8_t DIV;  // Bits 23-16
} PLL_out_div;


#endif