#include "FXOSC.h"

CTRL Get_FXOSC_Control_Register(){
CTRL cfg;
cfg.OSC_BYP =(uint8_t)((*FXOSC_CTRL & 0x01<<31)>>31);
cfg.COMP_EN =(uint8_t)((*FXOSC_CTRL & 0x01<<24)>>24);
cfg.EOCV    =(uint8_t)((*FXOSC_CTRL & 0xFF<<16)>>16);
cfg.GM_SEL  =(uint8_t)((*FXOSC_CTRL & 0xF<<4)>>4);
cfg.ALC_D   =(uint8_t)((*FXOSC_CTRL & 0x01<<2)>>2);
cfg.OSCON   =(uint8_t)((*FXOSC_CTRL & 0x01<<0)>>0);
return cfg;
}

void Set_FXOSC_Control_Register(CTRL* cfg){
(*FXOSC_CTRL)&=~(1<<31);
(*FXOSC_CTRL)&=~(1<<24);
(*FXOSC_CTRL)&=~(0xFF<<16);
(*FXOSC_CTRL)&=~(0xF<<4);
(*FXOSC_CTRL)&=~(1<<2);
(*FXOSC_CTRL)&=~(1<<0);

(*FXOSC_CTRL)|=((cfg->OSC_BYP)<<31);
(*FXOSC_CTRL)|=((cfg->COMP_EN)<<24);
(*FXOSC_CTRL)|=((cfg->EOCV)<<16);
(*FXOSC_CTRL)|=((cfg->GM_SEL)<<4);
(*FXOSC_CTRL)|=((cfg->ALC_D)<<2);
(*FXOSC_CTRL)|=((cfg->OSCON)<<0);
}

uint8_t Oscillator_Status_Register(){
    return (uint8_t)(*FXOSC_STAT & (0x01<<31));
}