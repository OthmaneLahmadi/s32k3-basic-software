#ifndef _CMU_FM_
#define _CMU_FM_

#include <stdint.h>


#define CMU_FM_BASE1 0x40000000U 

// Define the registers using the offsets
#define CMU_GCR   (volatile uint32_t*)(CMU_FM_BASE1 + 0x00)// Global Configuration Register
#define CMU_RCCR  (volatile uint32_t*)(CMU_FM_BASE1 + 0x04)// Reference Count Configuration Register
#define CMU_SR    (volatile uint32_t*)(CMU_FM_BASE1 + 0x08)// Status Register
#define CMU_IER   (volatile uint32_t*)(CMU_FM_BASE1 + 0x0C)// Interrupt Enable Register


typedef struct CMF_FM_STATUS{
uint32_t MET_CNT ;//Meter Clock Count
uint8_t FMTO;
uint8_t FMC; 
}CMF_FM_STATUS;

#endif