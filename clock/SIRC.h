#ifndef SIRC_H
#define SIRC_H
#define SIRC_base_address       (volatile uint32_t*)(0x402C8000)
#define Status_SIRC_Register    (volatile uint32_t*)(SIRC_base_address + 0x04)
#define MMISCELLANEOUS_IN       (volatile uint32_t*)(SIRC_base_address + 0x0c)

uint8_t SIRC_Status_Register();
uint8_t Get_Miscellaneous_input();
void    Set_Miscellaneous_input(uint8_t STANDBY_ENABLE);

#endif