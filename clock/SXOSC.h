#ifndef SXOSC_H
#define SXOSC_H
#include <stdint.h>

#define SXOSC_BASE  (volatile uint8_t*)(0x402CC000)
#define SXOSC_CTRL  (volatile uint8_t*)(SXOSC_BASE+0x00)
#define SXOSC_STAT  (volatile uint8_t*)(SXOSC_BASE+0x04)

typedef struct CTRL
{
uint8_t CURR_PRG_SF;
uint8_t CURR_PRG_COMP;
uint8_t EOCV;
uint8_t GM_SEL;
uint8_t OSCON;
}CTRL;



#endif