#include "SIRC.h"
#include <stdint.h>


uint8_t SIRC_Status_Register(){
return (uint8_t)(*Status_SIRC_Register & 0x01);
}

uint8_t Get_Miscellaneous_input(){
return (uint8_t)((*MMISCELLANEOUS_IN & (0x01<<8))>>8);
}

void Set_Miscellaneous_input(uint8_t STANDBY_ENABLE){
(*MMISCELLANEOUS_IN)&=~(0x01<<8);
(*MMISCELLANEOUS_IN)|=(STANDBY_ENABLE<<8);
}