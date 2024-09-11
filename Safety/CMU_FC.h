#ifndef _CMU_FC_H
#define _CMU_FC_H


#include <stdint.h>
#define CMU_FC_BASE0 0x402BC000

#define CMU_GCR   (volatile uint32_t*)(CMU_FC_BASE0 + 0x00) // Global Configuration Register
#define CMU_RCCR  (volatile uint32_t*)(CMU_FC_BASE0 + 0x04) // Reference Count Configuration Register
#define CMU_HTCR  (volatile uint32_t*)(CMU_FC_BASE0 + 0x08) // High Threshold Configuration Register
#define CMU_LTCR  (volatile uint32_t*)(CMU_FC_BASE0 + 0x0C) // Low Threshold Configuration Register
#define CMU_SR    (volatile uint32_t*)(CMU_FC_BASE0 + 0x10) // Status Register
#define CMU_IER   (volatile uint32_t*)(CMU_FC_BASE0 + 0x14) // Interrupt Enable Register

typedef struct CMU_status_register{
uint8_t RS;//Run Status
uint8_t FHH;//Frequency higher than high frequency reference threshold event status
uint8_t FLL;//Frequency lower than low frequency reference threshold event status
}CMU_status_register;


typedef struct CMU_Interrupt {
uint8_t FHHAIE;//Frequency Higher than High Frequency Reference Threshold Asynchronous Interrupt Enable
uint8_t FLLAIE;//Frequency Lower than Low Frequency Reference Threshold Asynchronous Interrupt Enable
uint8_t FHHIE ;//Frequency Higher than High Frequency Reference Threshold Synchronous Interrupt Enable
uint8_t FLLIE ;//Frequency Lower than Low Frequency Reference Threshold Synchronous Interrupt Enable
}CMU_Interrupt;

#endif