#ifndef CRC_H
#define CRC_H
#include <stdint.h>

// Base address of the CRC (Cyclic Redundancy Check) module
#define CRC_BASE 0x40380000 


// Define the registers using the offsets
#define CRC_DATA  (volatile uint32_t*)(CRC_BASE + 0x00)  // CRC Data Register
#define CRC_GPOLY (volatile uint32_t*)(CRC_BASE + 0x04)  // CRC Polynomial Register
#define CRC_CTRL  (volatile uint32_t*)(CRC_BASE + 0x08)  // CRC Control Register



typedef struct CRC_DATA{
uint8_t HU;//31-24
uint8_t HL;//23-16
uint8_t LU;//15-8
uint8_t LL;//7-0
}CRC_DATA;


typedef struct CRC_polynome{
uint16_t HIGH; //31-16
uint16_t LOW;  //15-0
}CRC_polynome;

typedef struct CRC_CTRL_t{
uint8_t TOT;//31-30
uint8_t TOTR;//29-28
uint8_t FXOR;//26
uint8_t WAS;//25
uint8_t TCRC;//24
}CRC_CTRL_t;

#endif