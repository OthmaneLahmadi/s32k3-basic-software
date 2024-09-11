#ifndef _MC_CGM
#define _MC_CGM


#define MC_CGM_base_address  0x402D8000


#define PCFS_SDUR        (volatile uint32_t*)(MC_CGM_base_address + 0x0)
#define PCFS_DIVC8       (volatile uint32_t*)(MC_CGM_base_address + 0x58)
#define PCFS_DIVE8       (volatile uint32_t*)(MC_CGM_base_address + 0x5C)
#define PCFS_DIVS8       (volatile uint32_t*)(MC_CGM_base_address + 0x60)
#define MUX_0_CSC        (volatile uint32_t*)(MC_CGM_base_address + 0x300)
#define MUX_0_CSS        (volatile uint32_t*)(MC_CGM_base_address + 0x304)
#define MUX_0_DC_0       (volatile uint32_t*)(MC_CGM_base_address + 0x308)
#define MUX_0_DC_1       (volatile uint32_t*)(MC_CGM_base_address + 0x30C)
#define MUX_0_DC_2       (volatile uint32_t*)(MC_CGM_base_address + 0x310)
#define MUX_0_DC_3       (volatile uint32_t*)(MC_CGM_base_address + 0x314)
#define MUX_0_DC_4       (volatile uint32_t*)(MC_CGM_base_address + 0x318)
#define MUX_0_DC_5       (volatile uint32_t*)(MC_CGM_base_address + 0x31C)
#define MUX_0_DC_6       (volatile uint32_t*)(MC_CGM_base_address + 0x320)
#define MUX_0_DC_7       (volatile uint32_t*)(MC_CGM_base_address + 0x324)
#define MUX_0_DIV_TRIG_CTRL (volatile uint32_t*)(MC_CGM_base_address + 0x334)
#define MUX_0_DIV_TRIG   (volatile uint32_t*)(MC_CGM_base_address + 0x338)
#define MUX_0_DIV_UPD_STAT (volatile uint32_t*)(MC_CGM_base_address + 0x33C)
#define MUX_1_CSC        (volatile uint32_t*)(MC_CGM_base_address + 0x340)
#define MUX_1_CSS        (volatile uint32_t*)(MC_CGM_base_address + 0x344)
#define MUX_1_DC_0       (volatile uint32_t*)(MC_CGM_base_address + 0x348)
#define MUX_1_DIV_UPD_STAT (volatile uint32_t*)(MC_CGM_base_address + 0x37C)
#define MUX_2_CSC        (volatile uint32_t*)(MC_CGM_base_address + 0x380)
#define MUX_2_CSS        (volatile uint32_t*)(MC_CGM_base_address + 0x384)
#define MUX_2_DC_0       (volatile uint32_t*)(MC_CGM_base_address + 0x388)
#define MUX_2_DIV_UPD_STAT (volatile uint32_t*)(MC_CGM_base_address + 0x3BC)
#define MUX_3_CSC        (volatile uint32_t*)(MC_CGM_base_address + 0x3C0)
#define MUX_3_CSS        (volatile uint32_t*)(MC_CGM_base_address + 0x3C4)
#define MUX_3_DC_0       (volatile uint32_t*)(MC_CGM_base_address + 0x3C8)
#define MUX_3_DIV_UPD_STAT (volatile uint32_t*)(MC_CGM_base_address + 0x3FC)
#define MUX_4_CSC        (volatile uint32_t*)(MC_CGM_base_address + 0x400)
#define MUX_4_CSS        (volatile uint32_t*)(MC_CGM_base_address + 0x404)
#define MUX_4_DC_0       (volatile uint32_t*)(MC_CGM_base_address + 0x408)
#define MUX_4_DIV_UPD_STAT (volatile uint32_t*)(MC_CGM_base_address + 0x43C)
#define MUX_5_CSC        (volatile uint32_t*)(MC_CGM_base_address + 0x440)
#define MUX_5_CSS        (volatile uint32_t*)(MC_CGM_base_address + 0x444)
#define MUX_5_DC_0       (volatile uint32_t*)(MC_CGM_base_address + 0x448)
#define MUX_5_DIV_UPD_STAT (volatile uint32_t*)(MC_CGM_base_address + 0x47C)
#define MUX_6_CSC        (volatile uint32_t*)(MC_CGM_base_address + 0x480)
#define MUX_6_CSS        (volatile uint32_t*)(MC_CGM_base_address + 0x484)
#define MUX_6_DC_0       (volatile uint32_t*)(MC_CGM_base_address + 0x488)
#define MUX_6_DIV_UPD_STAT (volatile uint32_t*)(MC_CGM_base_address + 0x4BC)
#define MUX_7_CSC        (volatile uint32_t*)(MC_CGM_base_address + 0x4C0)
#define MUX_7_CSS        (volatile uint32_t*)(MC_CGM_base_address + 0x4C4)
#define MUX_7_DC_0       (volatile uint32_t*)(MC_CGM_base_address + 0x4C8)
#define MUX_7_DIV_UPD_STAT (volatile uint32_t*)(MC_CGM_base_address + 0x4FC)
#define MUX_8_CSC        (volatile uint32_t*)(MC_CGM_base_address + 0x500)
#define MUX_8_CSS        (volatile uint32_t*)(MC_CGM_base_address + 0x504)
#define MUX_8_DC_0       (volatile uint32_t*)(MC_CGM_base_address + 0x508)
#define MUX_8_DIV_UPD_STAT (volatile uint32_t*)(MC_CGM_base_address + 0x53C)
#define MUX_9_CSC        (volatile uint32_t*)(MC_CGM_base_address + 0x540)
#define MUX_9_CSS        (volatile uint32_t*)(MC_CGM_base_address + 0x544)
#define MUX_9_DC_0       (volatile uint32_t*)(MC_CGM_base_address + 0x548)
#define MUX_9_DIV_UPD_STAT (volatile uint32_t*)(MC_CGM_base_address + 0x57C)
#define MUX_10_CSC       (volatile uint32_t*)(MC_CGM_base_address + 0x580)
#define MUX_10_CSS       (volatile uint32_t*)(MC_CGM_base_address + 0x584)
#define MUX_10_DC_0      (volatile uint32_t*)(MC_CGM_base_address + 0x588)
#define MUX_10_DIV_UPD_STAT   (volatile uint32_t*)(MC_CGM_base_address + 0x5BC)
#define MUX_11_CSC            (volatile uint32_t*)(MC_CGM_base_address + 0x5C0)
#define MUX_11_CSS            (volatile uint32_t*)(MC_CGM_base_address + 0x5C4)
#define MUX_11_DC_0           (volatile uint32_t*)(MC_CGM_base_address + 0x5C8)
#define MUX_11_DIV_UPD_STAT   (volatile uint32_t*)(MC_CGM_base_address + 0x5FC)
#define MUX_13_CSC            (volatile uint32_t*)(MC_CGM_base_address + 0x640)
#define MUX_13_CSS            (volatile uint32_t*)(MC_CGM_base_address + 0x644)
#define MUX_13_DC_0           (volatile uint32_t*)(MC_CGM_base_address + 0x648)
#define MUX_13_DIV_UPD_STAT   (volatile uint32_t*)(MC_CGM_base_address + 0x67C)
#define MUX_14_CSC            (volatile uint32_t*)(MC_CGM_base_address + 0x680)
#define MUX_14_CSS            (volatile uint32_t*)(MC_CGM_base_address + 0x684)
#define MUX_14_DC_0           (volatile uint32_t*)(MC_CGM_base_address + 0x688)
#define MUX_14_DIV_UPD_STAT   (volatile uint32_t*)(MC_CGM_base_address + 0x6BC)
#define MUX_15_CSC            (volatile uint32_t*)(MC_CGM_base_address + 0x6C0)
#define MUX_15_CSS            (volatile uint32_t*)(MC_CGM_base_address + 0x6C4)
#define MUX_15_DC_0           (volatile uint32_t*)(MC_CGM_base_address + 0x6C8)
#define MUX_15_DIV_UPD_STAT   (volatile uint32_t*)(MC_CGM_base_address + 0x6FC)
#define MUX_16_CSC            (volatile uint32_t*)(MC_CGM_base_address + 0x700)
#define MUX_16_CSS            (volatile uint32_t*)(MC_CGM_base_address + 0x704)
#define MUX_16_DC_0           (volatile uint32_t*)(MC_CGM_base_address + 0x708)
#define MUX_16_DIV_UPD_STAT   (volatile uint32_t*)(MC_CGM_base_address + 0x73C)
#define MUX_18_CSC            (volatile uint32_t*)(MC_CGM_base_address + 0x780)
#define MUX_18_CSS            (volatile uint32_t*)(MC_CGM_base_address + 0x784)
#define MUX_18_DC_0           (volatile uint32_t*)(MC_CGM_base_address + 0x788)
#define MUX_18_DIV_UPD_STAT   (volatile uint32_t*)(MC_CGM_base_address + 0x7BC)
#define MUX_19_CSC            (volatile uint32_t*)(MC_CGM_base_address + 0x7C0)
#define MUX_19_CSS            (volatile uint32_t*)(MC_CGM_base_address + 0x7C4)
#define MUX_19_DC_0           (volatile uint32_t*)(MC_CGM_base_address + 0x7C8)
#define MUX_19_DIV_UPD_STAT   (volatile uint32_t*)(MC_CGM_base_address + 0x7FC)

typedef struct cfg{
uint8_t SELCTL; // 4bits
uint8_t SAFE_SW; // 1bits
uint8_t CLK_SW;//1 bits
uint8_t RAMPDOWN;// 1 bits
uint8_t RAMPUP; // 1 bits
}cfg;


typedef struct clock_Mux_register{
uint8_t DE;
uint8_t DIV;
}clock_Mux_register;


typedef struct trigger_Control_Registe{
uint8_t HHEN;
uint8_t TCTL;
}trigger_Control_Registe;

typedef struct  Mux_1_control_register{
uint8_t SELCTL;
uint8_t SAFE_SW;
uint8_t CLK_SW; 
}Mux_1_control_register;


typedef struct mux1_select_status{
uint8_t SELSTAT;
uint8_t SWTRG;
uint8_t SWIP;
uint8_t SAFE_SW;
uint8_t CLK_SW;
}mux1_select_status;



typedef struct mux_5_register{
uint8_t SELCTL;
uint8_t FCG;
uint8_t CG;
}mux_5_register;


typedef struct register_5_status{
uint8_t SELCTL;
uint8_t CS;
uint8_t GRIP;
}register_5_status;




#endif