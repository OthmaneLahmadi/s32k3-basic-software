#ifndef _MC_RGM_
#define _MC_RGM_

#define DES   (volatile uint32_t*)(MC_RGM_BASE + 0x00)
#define FES   (volatile uint32_t*)(MC_RGM_BASE + 0x08)
#define FERD  (volatile uint32_t*)(MC_RGM_BASE + 0x0C)
#define FBRE  (volatile uint32_t*)(MC_RGM_BASE + 0x10)
#define FREC  (volatile uint32_t*)(MC_RGM_BASE + 0x14)
#define FRET  (volatile uint32_t*)(MC_RGM_BASE + 0x18)
#define DRET  (volatile uint32_t*)(MC_RGM_BASE + 0x1C)
#define ERCTRL (volatile uint32_t*)(MC_RGM_BASE + 0x20)
#define RDSS  (volatile uint32_t*)(MC_RGM_BASE + 0x24)

typedef struct Event_Status{
uint8_t DEBUG_DEST;
uint8_t SW_DEST;
uint8_t HSE_SNVS_RST;
uint8_t HSE_TMPR_RST;
uint8_t CM7_CORE_CLK_FAIL;
uint8_t SYS_DIV_FAIL;
uint8_t HSE_CLK_FAIL;
uint8_t AIPS_PLAT_CLK_FAIL;
uint8_t CORE_CLK_FAIL;
uint8_t PLL_LOL;
uint8_t FXOSC_FAIL;
uint8_t MC_RGM_FRE;
uint8_t STCU_URF;
uint8_t FCCU_FTR;
uint8_t F_POR;
}Event_Status;


typedef struct reset_status_t{
    uint8_t F_EXR           : 1; // Bit 0
    uint8_t reserved_1      : 2; // Bits 1-2, reserved
    uint8_t FCCU_RST        : 1; // Bit 3
    uint8_t ST_DONE         : 1; // Bit 4
    uint8_t reserved_2      : 1; // Bit 5, reserved
    uint8_t SWT0_RST        : 1; // Bit 6
    uint8_t SWT1_RST        : 1; // Bit 7
    uint8_t SWT2_RST        : 1; // Bit 8
    uint8_t JTAG_RST        : 1; // Bit 9
    uint8_t SWT3_RST        : 1; // Bit 10
    uint8_t reserved_3      : 1; // Bit 11, reserved
    uint8_t PLL_AUX         : 1; // Bit 12
    uint8_t reserved_4      : 3; // Bits 13-15, reserved
    uint8_t HSE_SWT_RST     : 1; // Bit 16
    uint8_t reserved_5      : 3; // Bits 17-19, reserved
    uint8_t HSE_BOOT_RST    : 1; // Bit 20
    uint8_t reserved_6      : 1; // Bit 21, reserved
    uint8_t reserved_7      : 1; // Bit 22, reserved
    uint8_t reserved_8      : 1; // Bit 23, reserved
    uint8_t reserved_9      : 5; // Bits 24-28, reserved
    uint8_t SW_FUNC         : 1; // Bit 29
    uint8_t DEBUG_FUNC      : 1; // Bit 30
    uint8_t reserved_10     : 1; // Bit 31, reserved
} reset_status_t;

typedef struct disable_control_t{
    uint8_t reserved_1      : 1; // Bit 0, reserved
    uint8_t reserved_2      : 1; // Bit 1, reserved
    uint8_t reserved_3      : 1; // Bit 2, reserved
    uint8_t D_FCCU_RST      : 1; // Bit 3
    uint8_t reserved_4      : 2; // Bits 4-5, reserved
    uint8_t D_SWT0_RST      : 1; // Bit 6
    uint8_t D_SWT1_RST      : 1; // Bit 7
    uint8_t D_JTAG_RST      : 1; // Bit 9
    uint8_t D_SWT2_RST      : 1; // Bit 8
    uint8_t D_SWT3_RST      : 1; // Bit 10
    uint8_t reserved_5      : 5; // Bits 13-17, reserved
    uint8_t reserved_6      : 1; // Bit 18, reserved
    uint8_t reserved_7      : 7; // Bits 19-25, reserved
    uint8_t reserved_8      : 1; // Bit 26, reserved
    uint8_t reserved_9      : 4; // Bits 27-29, reserved
    uint8_t D_DEBUG_FUNC    : 1; // Bit 30
    uint8_t reserved_10     : 1: // bit 30
} disable_control_t;


typedef struct bidirectional_reset_enable_t{
    uint8_t BE_DEBUG_FUNC;    // Bidirectional Reset Enables for 'Functional' Reset DEBUG_FUNC
    uint8_t BE_SW_FUNC;       // Bidirectional Reset Enables for 'Functional' Reset SW_FUNC
    uint8_t BE_HSE_BOOT_RST;  // Bidirectional Reset Enables for 'Functional' Reset HSE_BOOT_RST
    uint8_t BE_HSE_SWT_RST;   // Bidirectional Reset Enables for 'Functional' Reset HSE_SWT_RST
    uint8_t BE_PLL_AUX;       // Bidirectional Reset Enables for 'Functional' Reset PLL_AUX
    uint8_t BE_SWT3_RST;      // Bidirectional Reset Enables for 'Functional' Reset SWT3_RST
    uint8_t BE_JTAG_RST;      // Bidirectional Reset Enables for 'Functional' Reset JTAG_RST
    uint8_t BE_SWT2_RST;      // Bidirectional Reset Enables for 'Functional' Reset SWT2_RST
    uint8_t BE_SWT1_RST;      // Bidirectional Reset Enables for 'Functional' Reset SWT1_RST
    uint8_t BE_SWT0_RST;      // Bidirectional Reset Enables for 'Functional' Reset SWT0_RST
    uint8_t BE_ST_DONE;       // Bidirectional Reset Enables for 'Functional' Reset ST_DONE
    uint8_t BE_FCCU_RST;      // Bidirectional Reset Enables for 'Functional' Reset FCCU_RST
} bidirectional_reset_enable_t;



typedef struct Reset_sdb{

uint8_t FES_RES;
uint8_t DES_RES;
}Reset_sdb;

#endif