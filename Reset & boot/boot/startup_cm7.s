
#ifdef MULTIPLE_IMAGE
    #define RAM_DATA_INIT_ON_ALL_CORES
#endif

/* If this is a secodary core, it shall wait for the MSCM clock to be initialized */
#if defined(CORE1)||defined(CORE2)||defined(CORE3)
    #define NO_MSCM_CLOCK_INIT
#endif

#define MAIN_CORE 0
#define CORE_M7_0 0
#define CORE_M7_1 1
#define CORE_M7_2 2
#define CORE_M7_3 3

#define MCME_CTL_KEY                0x402DC000
#define MCME_PRTN1_PUPD             0x402DC304
#define MCME_PRTN1_STAT             0x402DC308
#define MCME_PRTN1_COFB0_CLKEN      0x402DC330
#define MCME_PRTN1_COFB0_STAT       0x402DC310
#define MCRGM_DES                   0x4028C000


//#define MCM_0_CM7					0x00800000


#define MCME_MSCM_REQ               (1 << 24)
#define MCRGM_DES_F_POR             (1)
#define MCME_KEY                    0x5AF0
#define MCME_INV_KEY                0xA50F

#define CM7_ITCMCR                  0xE000EF90
#define CM7_DTCMCR                  0xE000EF94

#define SBAF_BOOT_MARKER            (0x5AA55AA5)
#define CM7_0_ENABLE_SHIFT          (0)
#define CM7_1_ENABLE_SHIFT          (1)
#define CM7_2_ENABLE_SHIFT          (2)

#define CM7_0_ENABLE                (1)
#ifndef CM7_1_ENABLE
    #define CM7_1_ENABLE            (0)
#endif
#ifndef CM7_2_ENABLE
    #define CM7_2_ENABLE            (0)
#endif
#define CM7_0_VTOR_ADDR             (__CORE0_VTOR)
#define CM7_1_VTOR_ADDR             (__CORE1_VTOR)
#define CM7_2_VTOR_ADDR             (__CORE2_VTOR)
#define XRDC_CONFIG_ADDR            (0)
#define LF_CONFIG_ADDR              (0)

    .syntax unified
    .arch armv7-m

.section ".init_table", "a"
  .long 6
  .long __RAM_CACHEABLE_START
  .long __ROM_CACHEABLE_START
  .long __ROM_CACHEABLE_END
  .long __RAM_NO_CACHEABLE_START
  .long __ROM_NO_CACHEABLE_START
  .long __ROM_NO_CACHEABLE_END
  .long __RAM_SHAREABLE_START
  .long __ROM_SHAREABLE_START
  .long __ROM_SHAREABLE_END
  .long __RAM_INTERRUPT_START
  .long __INIT_INTERRUPT_START
  .long __INIT_INTERRUPT_END
  .long __RAM_ITCM_START
  .long __ROM_ITCM_START
  .long __ROM_ITCM_END
  .long __RAM_DTCM_DATA_START
  .long __ROM_DTCM_DATA_START
  .long __ROM_DTCM_END
.section ".zero_table", "a"
  .long 3
  .long __BSS_SRAM_SH_START
  .long __BSS_SRAM_SH_END
  .long __BSS_SRAM_NC_START
  .long __BSS_SRAM_NC_END
  .long __BSS_SRAM_START
  .long __BSS_SRAM_END

.globl RESET_CATCH_CORE
.globl _core_loop
.section ".core_loop","ax"
.thumb

_core_loop:
    nop
    nop
    nop
    nop
    b _core_loop

.section ".boot_header","ax"
  .long SBAF_BOOT_MARKER /* IVT marker */
  .long (CM7_0_ENABLE << CM7_0_ENABLE_SHIFT) | (CM7_1_ENABLE << CM7_1_ENABLE_SHIFT) | (CM7_2_ENABLE << CM7_2_ENABLE_SHIFT) | (1<<3) /* Boot configuration word */
  .long 0 /* Reserved */
  .long CM7_0_VTOR_ADDR /* CM7_0 Start address */
  .long 0 /* Reserved */
  .long CM7_1_VTOR_ADDR /* CM7_1 Start address */
  .long 0 /* Reserved */
  .long CM7_2_VTOR_ADDR /* CM7_2 Start address */
  .long 0 /* Reserved */
  .long XRDC_CONFIG_ADDR /* XRDC configuration pointer */
  .long LF_CONFIG_ADDR /* Lifecycle configuration pointer */
  .long 0 /* Reserved */

.globl VTABLE
.section ".startup","ax"
.thumb


.set VTOR_REG, 0xE000ED08
.thumb
.thumb_func
.globl Reset_Handler
.globl _start
_start:
Reset_Handler:
/*****************************************************/
/* Skip normal entry point as nothing is initialized */
/*****************************************************/
 cpsid i
 mov   r0, #0
 mov   r1, #0
 mov   r2, #0
 mov   r3, #0
 mov   r4, #0
 mov   r5, #0
 mov   r6, #0
 mov   r7, #0



#ifndef NO_MSCM_CLOCK_INIT

InitMSCMClock:
  /* If the MSCM clock is enabled, skip this sequence */
  ldr r0, =MCME_PRTN1_COFB0_STAT     /* 0x402DC310*/

  ldr r1, [r0]
  ldr r2, =MCME_MSCM_REQ   /*  1<<24 */
  and r1, r1, r2
  cmp r1, 0
  bne SetVTOR

  /* Enable clock in PRTN1 */
  ldr r0, =MCME_PRTN1_COFB0_CLKEN
  ldr r1, [r0]
  ldr r2, =MCME_MSCM_REQ
  orr r1, r2
  str r1, [r0]

  /* Set PUPD field */
  ldr r0, =MCME_PRTN1_PUPD
  ldr r1, [r0]
  ldr r2, =1
  orr r1, r2
  str r1, [r0]

  /* Trigger update */
  ldr r0, =MCME_CTL_KEY
  ldr r1, =MCME_KEY
  str r1, [r0]
  ldr r1, =MCME_INV_KEY
  str r1, [r0]
#endif




/* Check MSCM clock in PRTN1 */

#ifndef SIM_TYPE_VDK
WaitForClock:
  ldr r0, =MCME_PRTN1_COFB0_STAT
  ldr r1, [r0]
  ldr r2, =MCME_MSCM_REQ
  and r1, r1, r2
  cmp r1, 0
  beq WaitForClock
#endif




SetVTOR:
/* relocate vector table to RAM */
ldr  r0, =VTOR_REG
ldr  r1, =__RAM_START
str  r1,[r0]



/* Enable TCM and Disable RETEN bit */
LDR r1, =CM7_DTCMCR
LDR r0, [r1]
bic r0, r0, #0x4
orr r0, r0, #0x1
str r0, [r1]
/* Enable TCM and Disable RETEN bit */
LDR r1, =CM7_ITCMCR
LDR r0, [r1]
bic r0, r0, #0x4
orr r0, r0, #0x1
str r0, [r1]


/* set up stack; r13 SP*/
ldr  r0, =__Stack_dtcm_start   // on va l'importer a partir de linker script
msr MSP, r0






DisableSWT0:
  ldr  r0, =0x40270010
  ldr  r1, =0xC520
  str  r1, [r0]
  ldr  r1, =0xD928
  str  r1, [r0]
  ldr  r0, =0x40270000
  ldr  r1, =0x00000040
  str  r1, [r0]
  b    RamInit

DisableSWT1:
  ldr  r0, =0x4046C010
  ldr  r1, =0xC520
  str  r1, [r0]
  ldr  r1, =0xD928
  str  r1, [r0]
  ldr  r0, =0x4046C000
  ldr  r1, =0x00000040
  str  r1, [r0]
  b    RamInit

void init(param ){


}


//clock system












