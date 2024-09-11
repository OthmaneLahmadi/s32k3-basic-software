#include "MC_CGM.h"
#include <stdint.h>
#include <stdlib.h>

void PCFS_Step_Duration(uint16_t step_){
//This register specifies the step duration of each PCFS step. The value provided in this register specifies the PCFS step duration
//in terms of the number of cycles of FIRC
uint32_t step=*PCFS_SDUR;
uint16_t mask=0xFF;
step&=~(mask);
step|=step_;
}


void PCFS_Divider_Change_8_Registe(uint16_t INIT,uint8_t RATE){
//This register defines the rate of frequency change and initial change value on frequency ramp-up for the Progressive Clock
//Frequency switching of Reserved
#define mask_dev8 0xff
uint32_t PCFSDV=*PCFS_DIVC8;
PCFSDV&=~(mask_dev8);
PCFSDV|=RATE;
PCFSDV&=~(mask_dev8<<16);
PCFSDV|=INIT;
}


void PCFS_Divider_End_8_Registe(uint32_t DIVE){
uint32_t PCFS_DIvi=*PCFS_DIVE8;
uint32_t mask=0xFFFFF;
PCFS_DIvi~=&(mask);
PCFS_DIvi|=(DIVE);
}

void PCFS_Divider_Start_8_Register(uint32_t DIVS){
//This register defines the initial division value on frequency ramp-up for the progressive system clock switching of Reserved.
uint32_t PCFS_DIvi=*PCFS_DIVS8;
uint32_t mask=0xFFFFF;
PCFS_DIvi~=&(mask);
PCFS_DIvi|=(DIVS);
}




void Clock_Mux_0_Select_Control_Registe(mux0_cfg* cfg){
/*
*This register provides the clock source selection control for clock mux 0. Clock mux 0 implements hardware control clock switching
*ensuring that the clock switch happens in a graceful manner (without glitches). See the "Hardware-controlled clock multiplexer"
*section for details.
*An update to all the PCFS-related fields of this register must be an atomic write, which means a single write must update the
*CLK_SW, RAMPDOWN, and RAMPUP fields. It is necessary to set both RAMPUP and RAMPDOWN bits together even if you
*want to trigger either RAMPUP or RAMPDOWN process otherwise the desired PCFS sequence will not be executed.
*/
uint32_t mux0= *MUX_0_CSC;
uint8_t mask=0xF;
mux0&=~(mask<<24);
mux0|=(cfg->SELCTL<<3);
mux0|=(cfg->SAFE_SW<<2);
mux0|=(cfg->CLK_SW<<1);
mux0|=(cfg->RAMPDOWN<<0);
}

typedef status_register{
uint8_t SELSTAT;//4 bits
uint8_t SWTRG;// 3 bits
uint8_t SWIP;
uint8_t SAFE_SW;
uint8_t CLK_SW;
uint8_t RAMPDOWN;
uint8_t RAMPUP;
}status_register;

void Clock_Mux_0_Select_Status_Registe(status_register* cfg){
//This register provides the current clock source selection status for clock mux 0.
uint32_t mux =*MUX_0_CSS;
cfg->SELSTAT=(mux&(0xF<<24))>>24;
cfg->SWTRG=(mux&(0x7<<17))>>17;
cfg->SWIP=(mux&(0x01<<16))>>16;
cfg->SAFE_SW=(mux&(0X01<<3))>>3;
cfg->CLK_SW=(mux&(0x01<<2))>>2;
cfg->RAMPDOWN=(mux&(0x01<<1))>>2;
cfg->RAMPUP=(mux&(0x01<<0))>>0;
}


typedef struct clock_Mux_register{
uint8_t DE;
uint8_t DIV;
}clock_Mux_register;


uint8_t Clock_Mux_0_Divider_0_Control_Registe(){
uint32_t mux=*MUX_0_DC_0;
clock_Mux_register clk;
clk.DE=(mux&0x01<<31)>>31;
clk.DIV=(mux&0x07<<16)>>16;
return clk;
}

uint8_t Clock_Mux_0_Divider_1_Control_Registe(){
uint32_t mux=*MUX_0_DC_0;
clock_Mux_register clk;
clk.DE=(mux&0x01<<31)>>31;
clk.DIV=(mux&0x07<<16)>>16;
return clk;
}



uint8_t Clock_Mux_0_Divider_2_Control_Registe(){
uint32_t mux=*MUX_0_DC_0;
clock_Mux_register clk;
clk.DE=(mux&0x01<<31)>>31;
clk.DIV=(mux&0x07<<16)>>16;
return clk;
}

uint8_t Clock_Mux_0_Divider_3_Control_Registe(){
uint32_t mux=*MUX_0_DC_0;
clock_Mux_register clk;
clk.DE=(mux&0x01<<31)>>31;
clk.DIV=(mux&0x07<<16)>>16;
return clk;
}

uint8_t Clock_Mux_0_Divider_4_Control_Registe(){
uint32_t mux=*MUX_0_DC_0;
clock_Mux_register clk;
clk.DE=(mux&0x01<<31)>>31;
clk.DIV=(mux&0x07<<16)>>16;
return clk;
}

uint8_t Clock_Mux_0_Divider_5_Control_Registe(){
uint32_t mux=*MUX_0_DC_0;
clock_Mux_register clk;
clk.DE=(mux&0x01<<31)>>31;
clk.DIV=(mux&0x07<<16)>>16;
return clk;
}

uint8_t Clock_Mux_0_Divider_6_Control_Registe(){
uint32_t mux=*MUX_0_DC_0;
clock_Mux_register clk;
clk.DE=(mux&0x01<<31)>>31;
clk.DIV=(mux&0x07<<16)>>16;
return clk;
}


uint8_t Clock_Mux_0_Divider_7_Control_Registe(){
uint32_t mux=*MUX_0_DC_0;
clock_Mux_register clk;
clk.DE=(mux&0x01<<31)>>31;
clk.DIV=(mux&0x07<<16)>>16;
return clk;
}


void Set_Clock_Mux_0_Divider_Trigger_Control_Registe(trigger_Control_Registe* TRCR){
*(MUX_0_DIV_TRIG_CTRL)|=((TCRC->HEEN)&0x01)<<31;
*(MUX_0_DIV_TRIG_CTRL)|=((TCRC->TCLT)&0x01);
}

trigger_Control_Registe Get_Clock_Mux_0_Divider_Trigger_Control_Registe(){
trigger_Control_Registe TRCR;
TRCR.HEEN=((*MUX_0_DIV_TRIG_CTRL)&0x01)<<31;
TRCR.TCLT=((*MUX_0_DIV_TRIG_CTRL)&0x01); 
return TCRC;
}


void Clock_Mux_0_Divider_Trigger_Registe(uint32_t Trigger){
#define mask_trigger 0xFFFFFFFF
*(MUX_0_DIV_TRIG)&=~mask_trigger;
*(MUX_0_DIV_TRIG)|=Trigger;
}


uint8_t Clock_Mux_0_Divider_Update_Status_Register(){
return  (uint8_t)(*MUX_0_DIV_UPD_STAT)&0x01;
}



void Set_Clock_Mux_1_Select_Control_Register(Mux_1_control_register* ctrl){
uint8_t mask=0x1F;
uint32_t mux=*MUX_1_CSC;
mux&=~(mask<<24);
mux|=((ctrl->SELCTL)<<24);
mux|=(ctrl->SAFE_SW)<<3;
mux|=(ctrl->CLK_SW)<<2;
}

Mux_1_control_register Get_Clock_Mux_1_Select_Control_Register(){
uint32_t clock_data=*(MUX_1_CSC);
Mux_1_control_register ctrl;
ctrl.SELCTL=(uint8_t)(clock_data&(0x1F<<24))>>24;
ctrl.SAFE_SW=(uint8_t)(clock_data&(0x1 <<3))>>3;
ctrl.CLK_SW=(uint8_t)(clock_data&(0x01<<2))>>2;
return clock_data;
}

typedef struct mux1_select{
uint8_t SELSTAT;
uint8_t SAFE_SW;
uint8_t CLK_SW;  
};


mux1_select Get_Clock_Mux_1_Select_Status_Register(){
mux1_select mux;
mux_select.SELCTL=(uint8_t)(*MUX_1_CSC& (0x1F<<24))>>24;
mux.SAFE_SW=(uint8_t) ((*MUX_1_CSC & (0x01<<3) )>>3 );
mux.CLK_SW=(uint8_t) ((*MUX_1_CSC & (0x01<<2)) >> 3);
return mux;
}


void Set_Clock_Mux_1_Select_Status_Register(mux1_select* mux_sel){
uint8_t mask=0x1F;
(*MUX_1_CSC)&=~(mask<<24);
(*MUX_1_CSC)|=(mux_sel->SELSTAT)>>24;
(MUX_1_CSC)&=~(1<<3);
(*MUX_1_CSC)|=(mux_sel->SAFE_SW)>>3;
(MUX_1_CSC)&=~(1<<2);
(*MUX_1_CSC)|=(mux_sel->SELSTAT)>>2;
}





mux1_select_status Clock_Mux_1_Select_Status_Registe(){
mux1_select_status mux;
mux->SELSTAT  = (uint8_t)(((*MUX_1_CSS)&(1F<<24))>>24);
mux->SWTRG=(uint8_t)(((*MUX_1_CSC)&(7<<17))>>17);
mux->SWIP=(uint8_t)  ((*MUX_1_CSC)&(0x01<<16)>>16);
mux->SAFE_SW=(uint8_t) ((*MUX_1_CSC)&(0x01<<3))>>3;
mux->CLK_SW=(uint8_t) ((*MUX_1_CSC)&(0x01<<2))>>2;
return mux;
}




void Set_Clock_Mux_1_Divider_0_Control_Register(clock_Mux_register cfg){
MUX_1_DC_0 &=~(1<<31);
(*MUX_1_DC_0)|=(cfg->DE<<31);
MUX_1_DC_0 &=~(1<<16);
(*MUX_1_DC_0)|=(CFG->div<<16);
}

clock_Mux_register Get_Clock_Mux_1_Divider_0_Control_Register(){
clock_Mux_register clk;
clk->DE=(uint8_t)(((*MUX_1_DC_0)& (0x01<<31) )>>31);
clk->DIV=(uint8_t)(((*MUX_1_DC_0)&(0x01<<16))>>16);
return clk;
}

uint8_t Clock_Mux_1_Divider_Update_Status_Registe(){
return (uint8_t)(*MUX_1_DIV_UPD_STAT & (0x01)) ;
}


typedef struct  Mux_1_control_register{
uint8_t SELCTL;
uint8_t SAFE_SW;
uint8_t CLK_SW; 
}Mux_1_control_register;

Mux_1_control_register Get_Clock_Mux_2_Select_Control_Registe(){
Mux_1_control_register contrl;
contrl.SELCTL=(uint8_t)((*MUX_2_CSC & 0x1F<<24)>>24);
contrl.SAFE_SW= (uint8_t) ((*MUX_2_CSC & 0x01<<3)>>3);
contrl.CLK_SW=(uint8_t) ((*MUX_2_CSC & 0x01<<3) >>2);
return contrl;
}

void set_Clock_Mux_2_Select_Control_Registe(Mux_1_control_register* cfg){
(*MUX_2_CSC)&=~(0x1F<<24);
(*MUX_2_CSC)|=cfg->SELCTL;
(*MUX_2_CSC)&=~(0x01<<3);
(*MUX_2_CSC)|=cfg->SAFE_SW;
(*MUX_2_CSC)&=~(0x01<<2);
(*MUX_2_CSC)|=cfg->CLK_SW;
}


mux1_select_status Clock_Mux_2_Select_Status_Register(){
mux1_select_status mux;
(mux.SELCTL)=(uint8_t)(*MUX_2_CSS & 0x1F<<24) >> 24 ;
(mux.SELCTL)=(uint8_t)(*MUX_2_CSS & 0x7<<17) >> 17 ;
(mux.SELCTL)=(uint8_t)(*MUX_2_CSS & 0x1<<16) >> 16 ;
(mux.SELCTL)=(uint8_t)(*MUX_2_CSS & 0x1<<3) >> 3 ;
(mux.SELCTL)=(uint8_t)(*MUX_2_CSS & 0x1<<2) >> 2 ;
return mux;
}


typedef struct clock_Mux_register{
uint8_t DE;
uint8_t DIV;
}clock_Mux_register;

clock_Mux_register Get_Clock_Mux_2_Divider_0_Control_Registe(){

clock_Mux_register clk;
(clk.SELCTL)=(uint8_t)(*MUX_2_CSS & 0x01<<31) >> 31 ;
(clk.SELCTL)=(uint8_t)(*MUX_2_CSS & 0x01<<16) >> 16 ;
return clk;
}

void Set_Clock_Mux_2_Divider_0_Control_Registe(clock_Mux_register* cfg){
(*MUX_2_DC_0)&=~(0x1<<31);
(*MUX_2_DC_0)|=cfg->DE;
(*MUX_2_DC_0)&=~(0x01<<16);
(*MUX_2_DC_0)|=cfg->DIV;
}

uint8_t Clock_Mux_2_Divider_Update_Status_Registe(){
return (uint8_t) (*MUX_2_DIV_UPD_STAT & 0x01);
}

typedef struct  Mux_1_control_register{
uint8_t SELCTL;
uint8_t SAFE_SW;
uint8_t CLK_SW; 
}Mux_1_control_register;



void Set_Clock_Mux_3_Select_Control_Registe(Mux_1_control_register* cfg){
(*MUX_3_CSC)&=~(0x1F<<24);
(*MUX_3_CSC)|=((cfg->SELCTL)<<24);

(*MUX_3_CSC)&=~(0x01<<3);
(*MUX_3_CSC)&=~(0x01<<2);

(*MUX_3_CSC)|=(cfg->SAFE_SW<<3);
(*MUX_3_CSC)|=(cfg->CLK_SW <<2);
}


Mux_1_control_register Set_Clock_Mux_3_Select_Control_Registe(){
Mux_1_control_register contrl;
contrl.SELCTL=(uint8_t)((*MUX_3_CSC & 0x1F<<24)>>24);
contrl.SAFE_SW= (uint8_t) ((*MUX_3_CSC & 0x01<<3)>>3);
contrl.CLK_SW=(uint8_t) ((*MUX_3_CSC & 0x01<<3) >>2);
return contrl;
}


Set_Clock_Mux_3_Select_Status_Registe(Mux_1_control_register* cfg){

(*MUX_3_CSS)&=~(0x1F<<24);
(*MUX_3_CSS)&=~(0x07<<17);
(*MUX_3_CSS)&=~(0x01<<16);
(*MUX_3_CSS)&=~(0x01<<3);
(*MUX_3_CSS)&=~(0x01<<2);


(*MUX_3_CSS)|=(0x1F<<24);
(*MUX_3_CSS)|=(0x07<<17);
(*MUX_3_CSS)|=(0x01<<16);
(*MUX_3_CSS)|=(0x01<<3);
(*MUX_3_CSS)|=(0x01<<2);
}


Mux_1_control_register Get_Clock_Mux_3_Select_Status_Registe(){
Mux_1_control_register cntrl;
cntrl.SELCTL=(uint8_t)((*MUX_3_CSS & (0x1F<<24))>>24); 
cntrl.SELCTL=(uint8_t)((*MUX_3_CSS & (0x07<<17))>>17); 
cntrl.SELCTL=(uint8_t)((*MUX_3_CSS & (0x01<<16))>>16); 
cntrl.SELCTL=(uint8_t)((*MUX_3_CSS & (0x01<<3))>>3); 
cntrl.SELCTL=(uint8_t)((*MUX_3_CSS & (0x01<<2))>>2); 
return cntrl;
}



clock_Mux_register Get_Clock_Mux_3_Divider_0_Control_Registe(){
clock_Mux_register clk;
(clk.SELCTL)=(uint8_t)((*MUX_3_CSS & 0x01<<31) >> 31) ;
(clk.SELCTL)=(uint8_t)((*MUX_3_CSS & 0x01<<16) >> 16 );
return clk;
}


void Set_Clock_Mux_3_Divider_0_Control_Registe(clock_Mux_register* cfg){
(*MUX_3_DC_0)&=~(0x01<<31);
(*MUX_3_DC_0)|=cfg->DE;
(*MUX_3_DC_0)&=~(0x03<<16);
(*MUX_3_DC_0)|=cfg->DIV;
}


uint8_t Clock_Mux_3_Divider_Update_Status_Register(){
return  (uint8_t)(*MUX_3_DIV_UPD_STAT)&0x01;
}



void Set_Clock_Mux_4_Select_Control_Register(Mux_1_control_register* ctrl){
uint8_t mask=0x1F;
uint32_t mux=*MUX_4_CSC;
mux&=~(mask<<24);
mux|=((ctrl->SELCTL)<<24);
mux|=(ctrl->SAFE_SW)<<3;
mux|=(ctrl->CLK_SW)<<2;
}

Mux_1_control_register Get_Clock_Mux_4_Select_Control_Register(){
uint32_t clock_data=*(MUX_4_CSC);
Mux_1_control_register ctrl;
ctrl.SELCTL=(uint8_t)(clock_data&(0x1F<<24))>>24;
ctrl.SAFE_SW=(uint8_t)(clock_data&(0x1 <<3))>>3;
ctrl.CLK_SW=(uint8_t)(clock_data&(0x01<<2))>>2;
return clock_data;
}

Set_Clock_Mux_3_Select_Status_Registe(Mux_1_control_register* cfg){

(*MUX_3_CSS)&=~(0x1F<<24);
(*MUX_3_CSS)&=~(0x07<<17);
(*MUX_3_CSS)&=~(0x01<<16);
(*MUX_3_CSS)&=~(0x01<<3);
(*MUX_3_CSS)&=~(0x01<<2);


(*MUX_3_CSS)|=(0x1F<<24);
(*MUX_3_CSS)|=(0x07<<17);
(*MUX_3_CSS)|=(0x01<<16);
(*MUX_3_CSS)|=(0x01<<3);
(*MUX_3_CSS)|=(0x01<<2);
}


Mux_1_control_register Get_Clock_Mux_4_Select_Status_Registe(){
Mux_1_control_register cntrl;
cntrl.SELCTL=(uint8_t)((*MUX_4_CSS & (0x1F<<24))>>24); 
cntrl.SELCTL=(uint8_t)((*MUX_4_CSS & (0x07<<17))>>17); 
cntrl.SELCTL=(uint8_t)((*MUX_4_CSS & (0x01<<16))>>16); 
cntrl.SELCTL=(uint8_t)((*MUX_4_CSS & (0x01<<3))>>3); 
cntrl.SELCTL=(uint8_t)((*MUX_4_CSS & (0x01<<2))>>2); 
return cntrl;
}


clock_Mux_register Get_Clock_Mux_4_Divider_0_Control_Registe(){
clock_Mux_register clk;
(clk.SELCTL)=(uint8_t)((*MUX_4_CSS & 0x01<<31) >> 31) ;
(clk.SELCTL)=(uint8_t)((*MUX_4_CSS & 0x01<<16) >> 16 );
return clk;
}


void Set_Clock_Mux_4_Divider_0_Control_Registe(clock_Mux_register* cfg){
(*MUX_4_DC_0)&=~(0x01<<31);
(*MUX_4_DC_0)|=cfg->DE;
(*MUX_4_DC_0)&=~(0x03<<16);
(*MUX_4_DC_0)|=cfg->DIV;
}


uint8_t Clock_Mux_4_Divider_Update_Status_Register(){
return  (uint8_t)(*MUX_4_DIV_UPD_STAT)&0x01;
}

void Set_Clock_Mux_5_Select_Control_Register(mux_5_register* ctrl){
(*MUX_5_CSC)&=~(0x3F<<24);
(*MUX_5_CSC)&=~(0x01<<3);
(*MUX_5_CSC)&=~(0x01<<2);

(*MUX_5_CSC)&=(ctrl->SELCTL<<24)>>24;
(*MUX_5_CSC)&=(ctrl->FCG<<3)>>3;
(*MUX_5_CSC)&=(ctrl->CG<<2)>>2;
}


mux_5_register Get_Clock_Mux_5_Select_Control_Register(){
mux_5_register mux;
mux.SELCTL=(uint8_t)(clock_data&(0x3F<<24))>>24;
mux.FCG=(uint8_t)(clock_data&(0x1<<3))>>3;
mux.CG=(uint8_t)(clock_data&(0x01<<2))>>2;
return mux;
}




register_5_status Get_Clock_Mux_5_Select_Status_Registe(){
register_5_status cntrl;
cntrl.SELCTL=(uint8_t)((*MUX_5_CSS & (0x1F<<24))>>24); 
cntrl.CS=(uint8_t)((*MUX_5_CSS & (0x01<<17))>>17); 
cntrl.GRIP=(uint8_t)((*MUX_5_CSS & (0x01<<16))>>16); 
return cntrl;
}



void Set_Clock_Mux_5_Divider_0_Control_Register(clock_Mux_register cfg){
MUX_1_DC_0 &=~(1<<31);
(*MUX_5_DC_0)|=(cfg->DE<<31);
MUX_1_DC_0 &=~(0x3F<<16);
(*MUX_1_DC_0)|=(CFG->div<<16);
}

clock_Mux_register Get_Clock_Mux_5_Divider_0_Control_Register(){
clock_Mux_register clk;
clk->DE=(uint8_t)(((*MUX_1_DC_0)& (0x01<<31) )>>31);
clk->DIV=(uint8_t)(((*MUX_1_DC_0)&(0x1F<<16))>>16);
return clk;
}


uint8_t Clock_Mux_5_Divider_Update_Status_Register(){
return  (uint8_t)(*MUX_5_DIV_UPD_STAT)&0x01;
}


typedef struct mux_6_register{
uint8_t SELSTAT;
uint8_t CS;
uint8_t GRIP; 
}mux_6_register;


void Set_Clock_Mux_5_Select_Control_Register(mux_6_register* ctrl){
(*MUX_5_CSC)&=~(0x3F<<24);
(*MUX_5_CSC)&=~(0x01<<17);
(*MUX_5_CSC)&=~(0x01<<16);

(*MUX_5_CSC)&=(ctrl->SELCTL<<24)>>24;
(*MUX_5_CSC)&=(ctrl->CS<<17)>>17;
(*MUX_5_CSC)&=(ctrl->GRIP<<2)>>16;
}

mux_5_register Get_Clock_Mux_5_Select_Control_Register(){
mux_5_register mux;
mux.SELCTL=(uint8_t)(clock_data&(0x3F<<24))>>24;
mux.FCG=(uint8_t)(clock_data&(0x1<<3))>>3;
mux.CG=(uint8_t)(clock_data&(0x01<<2))>>2;
return mux;
}


