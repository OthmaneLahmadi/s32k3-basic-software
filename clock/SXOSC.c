#include "SXOSC.h"

typedef struct CTRL
{
uint8_t CURR_PRG_SF;
uint8_t CURR_PRG_COMP;
uint8_t EOCV;
uint8_t GM_SEL;
uint8_t OSCON;
}CTRL;



CTRL Get_Oscillator_Control_Register(){
CTRL cfg;
cfg.CURR_PRG_SF=(uint8_t)((*SXOSC_CTRL & 0b11<<26)>>26);
cfg.CURR_PRG_COMP=(uint8_t)((*SXOSC_CTRL & 0b11<<24)>>24 );
cfg.EOCV=(uint8_t)((*SXOSC_CTRL & 0xFF<<16)>>16);
cfg.GM_SEL=(uint8_t)((*SXOSC_CTRL & 0b11<<6)>>6);
cfg.CURR_PRG_SF=(uint8_t)(*SXOSC_CTRL & 0b1);
return cfg;
}