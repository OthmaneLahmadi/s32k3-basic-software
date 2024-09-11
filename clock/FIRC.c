#include "FIRC.h"

uint8_t Status_Register(){
return (uint8_t)(*Status_FIRC_Register & 0x01);
}

uint8_t Get_Standby_Enable_Register(){
return (uint8_t)(*STDBY_FIRC_ENABLE & 0x01);
}

void Set_Standby_Enable_Register(uint8_t STDBY_EN){
(*STDBY_FIRC_ENABLE)&=~(0x01);
(*STDBY_FIRC_ENABLE)|=STDBY_EN;
}