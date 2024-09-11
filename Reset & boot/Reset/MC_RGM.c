#include "MC_RGM.h"
#include <stdint.h>



void Set_Destructive_Event_Status_Register(Event_Status* event) {
    //This register contains the status of the 'destructive' reset sources.This register can be accessed as read/write in supervisor
//modeand read-only in user mode. Register bits are cleared on write '1'. This register is reset only on power-on reset.
    // Clear existing bits
    *DES &= ~(0x01 << 30);  // Clear DEBUG_DEST bit
    *DES &= ~(0x01 << 29);  // Clear SW_DEST bit
    *DES &= ~(0x01 << 18);  // Clear HSE_SNVS_RST bit
    *DES &= ~(0x01 << 17);  // Clear HSE_TMPR_RST bit
    *DES &= ~(0x01 << 16);  // Clear CM7_CORE_CLK_FAIL bit
    *DES &= ~(0x01 << 15);  // Clear SYS_DIV_FAIL bit
    *DES &= ~(0x01 << 14);  // Clear HSE_CLK_FAIL bit
    *DES &= ~(0x01 << 12);  // Clear AIPS_PLAT_CLK_FAIL bit
    *DES &= ~(0x01 << 10);  // Clear CORE_CLK_FAIL bit
    *DES &= ~(0x01 << 9);   // Clear PLL_LOL bit
    *DES &= ~(0x01 << 8);   // Clear FXOSC_FAIL bit
    *DES &= ~(0x01 << 6);   // Clear MC_RGM_FRE bit
    *DES &= ~(0x01 << 4);   // Clear STCU_URF bit
    *DES &= ~(0x01 << 3);   // Clear FCCU_FTR bit
    *DES &= ~(0x01 << 0);   // Clear F_POR bit

    // Set new values
    *DES |= (event->DEBUG_DEST << 30);
    *DES |= (event->SW_DEST << 29);
    *DES |= (event->HSE_SNVS_RST << 18);
    *DES |= (event->HSE_TMPR_RST << 17);
    *DES |= (event->CM7_CORE_CLK_FAIL << 16);
    *DES |= (event->SYS_DIV_FAIL << 15);
    *DES |= (event->HSE_CLK_FAIL << 14);
    *DES |= (event->AIPS_PLAT_CLK_FAIL << 12);
    *DES |= (event->CORE_CLK_FAIL << 10);
    *DES |= (event->PLL_LOL << 9);
    *DES |= (event->FXOSC_FAIL << 8);
    *DES |= (event->MC_RGM_FRE << 6);
    *DES |= (event->STCU_URF << 4);
    *DES |= (event->FCCU_FTR << 3);
    *DES |= (event->F_POR << 0);
}


Event_Status Get_Destructive_Event_Status_Register() {
    Event_Status event;

    event.DEBUG_DEST = (uint8_t)((*DES & (0x01 << 30)) >> 30);
    event.SW_DEST = (uint8_t)((*DES & (0x01 << 29)) >> 29);
    event.HSE_SNVS_RST = (uint8_t)((*DES & (0x01 << 18)) >> 18);
    event.HSE_TMPR_RST = (uint8_t)((*DES & (0x01 << 17)) >> 17);
    event.CM7_CORE_CLK_FAIL = (uint8_t)((*DES & (0x01 << 16)) >> 16);
    event.SYS_DIV_FAIL = (uint8_t)((*DES & (0x01 << 15)) >> 15);
    event.HSE_CLK_FAIL = (uint8_t)((*DES & (0x01 << 14)) >> 14);
    event.AIPS_PLAT_CLK_FAIL = (uint8_t)((*DES & (0x01 << 12)) >> 12);
    event.CORE_CLK_FAIL = (uint8_t)((*DES & (0x01 << 10)) >> 10);
    event.PLL_LOL = (uint8_t)((*DES & (0x01 << 9)) >> 9);
    event.FXOSC_FAIL = (uint8_t)((*DES & (0x01 << 8)) >> 8);
    event.MC_RGM_FRE = (uint8_t)((*DES & (0x01 << 6)) >> 6);
    event.STCU_URF = (uint8_t)((*DES & (0x01 << 4)) >> 4);
    event.FCCU_FTR = (uint8_t)((*DES & (0x01 << 3)) >> 3);
    event.F_POR = (uint8_t)((*DES & (0x01 << 0)) >> 0);

    return event;
}

//----------------------------------------------------------------------

    //This register contains the status of the 'functional' and external reset sources.This register can be accessed as read/write in
//supervisor modeand read-only in user mode. Register bits are cleared on write '1' if the triggering event has already been cleared
//at the source. This register is reset only on power-on reset.
void Set_Functional_External_Reset_Status_Register(reset_status_t *status) {

    // Apply mask to clear all bits in the FES register
    (*FES) &= ~((0x01 << 0) |   // F_EXR
                (0x01 << 3) |   // FCCU_RST
                (0x01 << 4) |   // ST_DONE
                (0x01 << 6) |   // SWT0_RST
                (0x01 << 7) |   // SWT1_RST
                (0x01 << 8) |   // SWT2_RST
                (0x01 << 9) |   // JTAG_RST
                (0x01 << 10) |  // SWT3_RST
                (0x01 << 12) |  // PLL_AUX
                (0x01 << 16) |  // HSE_SWT_RST
                (0x01 << 20) |  // HSE_BOOT_RST
                (0x01 << 29) |  // SW_FUNC
                (0x01 << 30));  // DEBUG_FUNC

    // Set the values based on the status structure
    (*FES) |= (status->F_EXR << 0) |
              (status->FCCU_RST << 3) |
              (status->ST_DONE << 4) |
              (status->SWT0_RST << 6) |
              (status->SWT1_RST << 7) |
              (status->SWT2_RST << 8) |
              (status->JTAG_RST << 9) |
              (status->SWT3_RST << 10) |
              (status->PLL_AUX << 12) |
              (status->HSE_SWT_RST << 16) |
              (status->HSE_BOOT_RST << 20) |
              (status->SW_FUNC << 29) |
              (status->DEBUG_FUNC << 30);
}

reset_status_t Get_Functional_External_Reset_Status_Register() {
    reset_status_t status;

    status.F_EXR = (uint8_t)((*FES & (0x01 << 0)) >> 0);
    status.FCCU_RST = (uint8_t)((*FES & (0x01 << 3)) >> 3);
    status.ST_DONE = (uint8_t)((*FES & (0x01 << 4)) >> 4);
    status.SWT0_RST = (uint8_t)((*FES & (0x01 << 6)) >> 6);
    status.SWT1_RST = (uint8_t)((*FES & (0x01 << 7)) >> 7);
    status.SWT2_RST = (uint8_t)((*FES & (0x01 << 8)) >> 8);
    status.JTAG_RST = (uint8_t)((*FES & (0x01 << 9)) >> 9);
    status.SWT3_RST = (uint8_t)((*FES & (0x01 << 10)) >> 10);
    status.PLL_AUX = (uint8_t)((*FES & (0x01 << 12)) >> 12);
    status.HSE_SWT_RST = (uint8_t)((*FES & (0x01 << 16)) >> 16);
    status.HSE_BOOT_RST = (uint8_t)((*FES & (0x01 << 20)) >> 20);
    status.SW_FUNC = (uint8_t)((*FES & (0x01 << 29)) >> 29);
    status.DEBUG_FUNC = (uint8_t)((*FES & (0x01 << 30)) >> 30);

    return status;
}



//----------------------------------------------------------------------------------
//This register contains the status of the 'functional' and external reset sources.This register can be accessed as read/write in
//supervisor modeand read-only in user mode. Register bits are cleared on write '1' if the triggering event has already been cleared
//at the source. This register is reset only on power-on reset.

void Set_Functional_Event_Reset_Disable_Register(disable_control_t* control) {
    // Apply mask to all bits
    *FERD &= ~((0x01 << 30) | (0x01 << 29) | (0x01 << 28) | (0x01 << 27) |
                (0x01 << 26) | (0x01 << 25) | (0x01 << 24) | (0x01 << 23) |
                (0x01 << 22) | (0x01 << 21) | (0x01 << 20) | (0x01 << 19) |
                (0x01 << 18) | (0x01 << 17) | (0x01 << 16) | (0x01 << 15) |
                (0x01 << 14) | (0x01 << 13) | (0x01 << 12) | (0x01 << 11) |
                (0x01 << 10) | (0x01 << 9) | (0x01 << 8) | (0x01 << 7) |
                (0x01 << 6) | (0x01 << 5) | (0x01 << 4) | (0x01 << 3) |
                (0x01 << 2) | (0x01 << 1) | (0x01 << 0));

    // Set the values
    *FERD |= (control->D_DEBUG_FUNC << 30) |
             (control->D_SWT3_RST << 10) |
             (control->D_JTAG_RST << 9) |
             (control->D_SWT2_RST << 8) |
             (control->D_SWT1_RST << 7) |
             (control->D_SWT0_RST << 6) |
             (control->D_FCCU_RST << 3);
}

disable_control_t Get_Functional_Event_Reset_Disable_Register() {
    disable_control_t control;

    control.D_DEBUG_FUNC = (uint8_t)((*FERD & (0x01 << 30)) >> 30);
    control.D_SWT3_RST = (uint8_t)((*FERD & (0x01 << 10)) >> 10);
    control.D_JTAG_RST = (uint8_t)((*FERD & (0x01 << 9)) >> 9);
    control.D_SWT2_RST = (uint8_t)((*FERD & (0x01 << 8)) >> 8);
    control.D_SWT1_RST = (uint8_t)((*FERD & (0x01 << 7)) >> 7);
    control.D_SWT0_RST = (uint8_t)((*FERD & (0x01 << 6)) >> 6);
    control.D_FCCU_RST = (uint8_t)((*FERD & (0x01 << 3)) >> 3);

    // Reserved bits are not set or cleared as they are not used

    return control;
}

//---------------------------------------------------------------

//This register enables the generation of an external reset on 'functional' reset.This register can be accessed as read/write in
//supervisor modeand read-only in user mode.This register is reset on power-on and any 'destructive' reset.

bidirectional_reset_enable_t Get_Bidirectional_Reset_Enable_Register() {
    bidirectional_reset_enable_t reset_enable;
    uint32_t temp = *FBRE;

    reset_enable.BE_DEBUG_FUNC    = (temp >> 30) & 0x01;
    reset_enable.BE_SW_FUNC       = (temp >> 29) & 0x01;
    reset_enable.BE_HSE_BOOT_RST  = (temp >> 20) & 0x01;
    reset_enable.BE_HSE_SWT_RST   = (temp >> 16) & 0x01;
    reset_enable.BE_PLL_AUX       = (temp >> 12) & 0x01;
    reset_enable.BE_SWT3_RST      = (temp >> 10) & 0x01;
    reset_enable.BE_JTAG_RST      = (temp >> 9)  & 0x01;
    reset_enable.BE_SWT2_RST      = (temp >> 8)  & 0x01;
    reset_enable.BE_SWT1_RST      = (temp >> 7)  & 0x01;
    reset_enable.BE_SWT0_RST      = (temp >> 6)  & 0x01;
    reset_enable.BE_ST_DONE       = (temp >> 4)  & 0x01;
    reset_enable.BE_FCCU_RST      = (temp >> 3)  & 0x01;

    return reset_enable;
}


void Set_Bidirectional_Reset_Enable_Register(bidirectional_reset_enable_t reset_enable) {


    //Bidirectional Reset Enables for 'Functional' Reset SWT3_RST
//0b - External reset pin is asserted on a 'Functional' reset SWT3_RST event if the reset is enabled.
//1b - External reset pin is not asserted on a 'functional' reset SWT3_RST event.
    uint32_t temp = 0;
    temp |= (reset_enable.BE_SWT3_RST      & 0x01) << 10;

    *FBRE = temp;
}


//--------------------------------------------------------------------------------------------

//This register provides the current value of functional reset escalation counter. It can be accessed in read/write, either in
//supervisor mode. It can be accessed in read in the user mode. This register is reset by power-on reset, destructive reset, when
//you reconfigure the FREC field to Fh and when you write any value to the Functional Reset Escalation Threshold Register
//(FRET) register.

void Set_Functional_Reset_Escalation_Counter_Register(uint8_t frec){
*FREC &= ~(0b1111);//apply mask
*FREC|=frec;
}

uint8_t Get_Functional_Reset_Escalation_Counter_Register(){
//This bit field provides the value of functional reset escalation counter.
return (uint8_t)(*FREC & 0b1111);
}


//------------------------------------------------------------------------------------------------

/*
This register sets the threshold for 'functional' reset escalation to a 'destructive' reset.It can be accessed in read/write, either
in supervisor mode. It can be accessed in read-only in the user mode. Writing a non-zero value to the FRET field enables
the 'functional' reset escalation function. Writing any value to this register resets the 'functional' reset escalation counter. See
Functional reset escalation for details on the 'functional' reset escalation function. This register is reset on power-on and any
'destructive' reset

Functional' Reset Escalation Threshold
If the value of this field is 0, the 'functional' reset escalation function is disabled. Any other value is the
number of 'functional' resets that causes a 'destructive' reset

*/


void Set_Functional_Reset_Escalation_Threshold_Register(uint8_t fret){
*FRET&=~(0b1111);
*FRET|=(fret);
}

uint8_t Get_Functional_Reset_Escalation_Threshold_Register(){
return (uint8_t)(*FRET & 0b1111);
}

//--------------------------------------------------------------------------------------


/*

this register sets the threshold for 'destructive' reset escalation to keeping the chip in the reset state until the next power-on reset
triggers a new reset sequence. It can be accessed in read/write, either in supervisor mode. It can be accessed in read-only in the
user mode. Writing a non-zero value to the DRET field enables the 'destructive' reset escalation function. Writing any value to
this register resets the 'destructive' reset counter.

If the value of this field is 0, the 'destructive' reset escalation function is disabled. Any other value is
the number of 'destructive' resets which keeps the chip in the reset state until the next power-on reset
triggers a new reset sequence.

*/

void Set_Destructive_Reset_Escalation_Threshold_Register(uint8_t dret){
*DRET&=~(0b1111);
*DRET|=(dret);
}



uint8_t Get_Destructive_Reset_Escalation_Threshold_Register(){
return (uint8_t)(*DRET & 0b1111);
}


//--------------------------------------------------------------------------------------

/*

This register allows software to control the assertion of External reset pin. It can be accessed in read/write, in supervisor mode.
It can be accessed in read-only in the user mode. This register is reset on all resets.

Setting ERASSERT to 1b also safe states most of the chip's pins. See the IOMUX table for
each pin's safe state value. Software must use the ERASSERT bit for this purpose only as
part of the main reset domain self-test entry procedure. Using it at any other time may result
in unpredictable system behavior.

0b - No change
1b - External reset is asserted
*/
void Set_External_Reset_Control_Register(uint8_t ERASSERT){
*ERCTRL &=~(0b1);
*ERCTRL|=ERASSERT;
}

uint8_t Get_External_Reset_Control_Register(){
return (uint8_t)(*ERCTRL & 0b1);
}



//--------------------------------------------------------------------------------------------------

/*
This register provides status of whether a reset event occurred during standby mode.Register bits are cleared on write '1'. This
register is reset only on power-on reset.


*/


void Set_Reset_During_Standby_Status_Register(Reset_sdb rdss){
(*RDSS)&=~((0b1)|(0b1<<1));
(*RDSS)|=(rdss.DES_RES& 0b1);
(*RDSS)|=(rdss.FES_RES& 0b1)<<1;
}

Reset_sdb Get_Reset_During_Standby_Status_Register(){
    return (uint8_t)(*RDSS & 0b11);
}

//-------------------------------------------------------------------------------------------------

