#ifndef FXOSC_H
#define FXOSC_H

#include <stdint.h>

#define FXOSC_base_address      (volatile uint32_t*)(0x402D4000)
#define FXOSC_CTRL              (volatile uint32_t*)(FXOSC_base_address + 0x00)
#define FXOSC_STAT              (volatile uint32_t*)(FXOSC_STAT + 0x04)

typedef struct CTRL
{
  uint8_t OSC_BYP;
  uint8_t COMP_EN;
  uint8_t EOCV;
  uint8_t GM_SEL;
  uint8_t ALC_D;
  uint8_t OSCON;
}CTRL ;


CTRL Get_FXOSC_Control_Register();
void Set_FXOSC_Control_Register(CTRL* cfg);
uint8_t Oscillator_Status_Register();


#endif