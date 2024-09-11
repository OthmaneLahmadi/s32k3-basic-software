#ifndef FRIC_H 
#define FIRC_H
#include <stdint.h>

#define FIRC_BASE               (volatile uint32_t*)(0x402D0000)
#define Status_FIRC_Register    (volatile uint32_t*)(FIRC_BASE + 0x04)
#define STDBY_FIRC_ENABLE       (volatile uint32_t*)(FIRC_BASE + 0x08)

uint8_t Status_Register();
uint8_t Get_Standby_Enable_Register();
void Set_Standby_Enable_Register(uint8_t STDBY_EN);

#endif