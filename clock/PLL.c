#include "PLL.h"
#include <stdint.h>


//Configures PLL functionality.
void Set_PLL_Control(uint8_t PLLPD){
*PLLCR &=~(0b1<<31);
*PLLCR |=PLLPD<<31;
}

uint8_t Get_PLL_Control(){
return (uint8_t)((*PLLCR & 0b1<<31)>>31);
}

//----------------------------------------------------------------------
//Shows the PLL status.

void Set_PLL_Status(PLL_stats stats){
(*PLLSR) &=~(0b1<<3);// apply mask to the two bits 
(*PLLSR) |=(stats.LOL & 0b1)<<3;
}

PLL_stats Get_PLL_Status(){
PLL_stats stats;
stats.LOL=(uint8_t)((*PLLSR & 0b1<<3)>>3);
stats.LOCK=(uint8_t)((*PLLSR & 0b1<<2)>>2);
}


//------------------------------------------
//Divides input clocks for PLL output generation.
void Set_PLL_DIV_Register(PLL_DIV_t pll_div) {
    uint32_t reg_value = 0;

    // Apply masks and shift bits to their correct positions
    reg_value |= (pll_div.ODIV2 & 0x3F) << 25;  // ODIV2 (6 bits)
    reg_value |= (pll_div.RDIV & 0x07) << 12;   // RDIV (3 bits)
    reg_value |= (pll_div.MFI & 0xFF);          // MFI (8 bits)

    // Write the value to the register
    *FBRE = reg_value;
}

PLL_DIV_t Get_PLL_DIV_Register() {
    PLL_DIV_t pll_div;
    uint32_t reg_value = *FBRE;

    // Extract and shift bits to retrieve the fields
    pll_div.ODIV2 = (uint8_t)((reg_value >> 25) & 0x3F);  // ODIV2 (6 bits)
    pll_div.RDIV = (uint8_t)((reg_value >> 12) & 0x07);   // RDIV (3 bits)
    pll_div.MFI = (uint8_t)(reg_value & 0xFF);            // MFI (8 bits)

    return pll_div;
}


//---------------------------------------------------------

//Configures PLL frequency modulation parameters.


void Set_Frequency_Modulation_Config_Register(Frequency_modulation_cfg_t cfg) {
    uint32_t reg_value = 0;

    // Apply masks and shift bits to their correct positions
    reg_value |= (cfg.SSCGBYP & 0x01) << 30;           // SSCGBYP (1 bit)
    reg_value |= (cfg.SPREADCTL & 0x01) << 29;         // SPREADCTL (1 bit)
    reg_value |= (cfg.STEPSIZE & 0x03FF) << 16;        // STEPSIZE (10 bits)
    reg_value |= (cfg.STEPNO & 0x07FF);                // STEPNO (11 bits)

    // Write the value to the register
    *PLLFM = reg_value;
}

Frequency_modulation_cfg_t Get_Frequency_Modulation_Config_Register() {
    Frequency_modulation_cfg_t cfg;
    uint32_t reg_value = *PLLFM;

    // Extract and shift bits to retrieve the fields
    cfg.SSCGBYP = (uint8_t)((reg_value >> 30) & 0x01);   // SSCGBYP (1 bit)
    cfg.SPREADCTL = (uint8_t)((reg_value >> 29) & 0x01); // SPREADCTL (1 bit)
    cfg.STEPSIZE = (uint16_t)((reg_value >> 16) & 0x03FF); // STEPSIZE (10 bits)
    cfg.STEPNO = (uint16_t)(reg_value & 0x07FF);         // STEPNO (11 bits)

    return cfg;
}


//----------------------------------------------------------------------
//Enables and configures frequency modulation.

void Set_PLL_Fraction_Div_Register(PLL_fraction_div_t div_cfg) {
    uint32_t reg_value = 0;

    // Apply masks and shift bits to their correct positions
    reg_value |= (div_cfg.SDMEN & 0x01) << 30;  // SDMEN (1 bit)
    reg_value |= (div_cfg.SDM2 & 0x01) << 29;   // SDM2 (1 bit)
    reg_value |= (div_cfg.SDM3 & 0x01) << 28;   // SDM3 (1 bit)
    reg_value |= (div_cfg.MFN & 0x7FFF);        // MFN (15 bits)

    // Write the value to the register
    *PLLFD = reg_value;
}



PLL_fraction_div_t Get_PLL_Fraction_Div_Register() {
    PLL_fraction_div_t div_cfg;
    uint32_t reg_value = *PLLFD;

    // Extract and shift bits to retrieve the fields
    div_cfg.SDMEN = (uint8_t)((reg_value >> 30) & 0x01);   // SDMEN (1 bit)
    div_cfg.SDM2 = (uint8_t)((reg_value >> 29) & 0x01);    // SDM2 (1 bit)
    div_cfg.SDM3 = (uint8_t)((reg_value >> 28) & 0x01);    // SDM3 (1 bit)
    div_cfg.MFN = (uint16_t)(reg_value & 0x7FFF);          // MFN (15 bits)

    return div_cfg;
}


//----------------------------------------------

/*Unlock Control Accuracy
Defines the accuracy necessary to achieve unlock.
*/
uint8_t Get_PLL_Calibration_Register(){
return (uint8_t)((*PLLCAL2 & 0b11<<7)>>7);
}

void Set_PLL_Calibration_Register(uint8_t ULKCTL){
(*PLLCAL2)&=~(0b11<<7);
*PLLCAL2|=ULKCTL;
}



//--------------------------------------------------

void Set_PLL_Out_Div_Register(PLL_out_div config, uint8_t instance) {
    uint32_t regValue = 0;

    // Choose the correct register based on the instance
    uint32_t* regAddr = (instance == 0) ? PLLODIV_0 : PLLODIV_1;

    // Read the current register value
    regValue = *regAddr;

    // Clear the bits for DE and DIV
    regValue &= ~((1U << 31) | (0xFF << 16));

    // Set the DE field
    regValue |= ((uint32_t)config.DE << 31);

    // Set the DIV field
    regValue |= ((uint32_t)config.DIV << 16);

    // Write the updated value back to the register
    *regAddr = regValue;
}


PLL_out_div Get_PLL_Out_Div_Register(uint8_t instance) {
    PLL_out_div config;
    uint32_t regValue = 0;

    // Choose the correct register based on the instance
    uint32_t* regAddr = (instance == 0) ? PLLODIV_0 : PLLODIV_1;

    // Read the current register value
    regValue = *regAddr;

    // Extract the DE field
    config.DE = (uint8_t)((regValue >> 31) & 0x01);

    // Extract the DIV field
    config.DIV = (uint8_t)((regValue >> 16) & 0xFF);

    return config;
}

