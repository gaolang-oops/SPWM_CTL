/*==================================================
文件描述：外设初始化文件
使用MCU：dsPIC33EP128MC506
文件功能：初始化所有外设
作者：高朗
==================================================*/
#include "HardWare.h"
#include "Sfr_Init.h"

/*=============端口初始化====================*/
static void INIT_SECTION McuPortInitialize(void) {

    /*-----------PORTA寄存器初始化----------------------*/
    TRISA = TRISA_INIT;
    PORTA = PORTA_INIT;
    LATA = LATA_INIT;
    ODCA = ODCA_INIT;
    CNENA = CNENA_INIT;
    CNPUA = CNPUA_INIT;
    CNPDA = CNPDA_INIT;
    ANSELA = ANSELA_INIT;
    /*-----------PORTB寄存器初始化----------------------*/
    TRISB = TRISB_INIT;
    PORTB = PORTB_INIT;
    LATB = LATB_INIT;
    ODCB = ODCB_INIT;
    CNENB = CNENB_INIT;
    CNPUB = CNPUB_INIT;
    CNPDB = CNPDB_INIT;
    ANSELB = ANSELB_INIT;
    /*-----------PORTC寄存器初始化----------------------*/
    TRISC = TRISC_INIT;
    PORTC = PORTC_INIT;
    LATC = LATC_INIT;
    ODCC = ODCC_INIT;
    CNENC = CNENC_INIT;
    CNPUC = CNPUC_INIT;
    CNPDC = CNPDC_INIT;
    ANSELC = ANSELC_INIT;
    /*-----------PORTD寄存器初始化----------------------*/
    TRISD = TRISD_INIT;
    PORTD = PORTD_INIT;
    LATD = LATD_INIT;
    ODCD = ODCD_INIT;
    CNEND = CNEND_INIT;
    CNPUD = CNPUD_INIT;
    CNPDD = CNPDD_INIT;
    /*-----------PORTE寄存器初始化----------------------*/
    TRISE = TRISE_INIT;
    PORTE = PORTE_INIT;
    LATE = LATE_INIT;
    ODCE = ODCE_INIT;
    CNENE = CNENE_INIT;
    CNPUE = CNPUE_INIT;
    CNPDE = CNPDE_INIT;
    ANSELE = ANSELE_INIT;

    /*-----------PORTG寄存器初始化----------------------*/
    TRISG = TRISG_INIT;
    PORTG = PORTG_INIT;
    LATG = LATG_INIT;
    ODCG = ODCG_INIT;
    CNENG = CNENG_INIT;
    CNPUG = CNPUG_INIT;
    CNPDG = CNPDG_INIT;
}

/*=============外设引脚选择配置功能初始化====================*/
static void INIT_SECTION McuPpsInitialize(void) {
    //外设引脚选择配置输入寄存器初始化
    //    RPINR0 = RPINR0_INIT;
    //    RPINR1 = RPINR1_INIT;
    //    RPINR3 = RPINR3_INIT;
    RPINR7 = RPINR7_INIT;  //输入捕获IC1 IC2开启
    RPINR8 = RPINR8_INIT;  //输入捕获IC3开启
    //    RPINR11 = RPINR11_INIT;
    //    RPINR12 = RPINR12_INIT;
    //    RPINR14 = RPINR14_INIT;
    //    RPINR15 = RPINR15_INIT;
    //    RPINR18 = RPINR18_INIT;
    //    RPINR19 = RPINR19_INIT;
    //    RPINR22 = RPINR22_INIT;
    //    RPINR23 = RPINR23_INIT;
    //    RPINR26 = RPINR26_INIT;
    //    RPINR37 = RPINR37_INIT;
    //    RPINR38 = RPINR38_INIT;
    //    RPINR39 = RPINR39_INIT;
    //外设引脚选择配置输出寄存器初始化
    //    RPOR0 = RPOR0_INIT;
    //    RPOR1 = RPOR1_INIT;
    //    RPOR2 = RPOR2_INIT;
    //    RPOR3 = RPOR3_INIT;
    //    RPOR4 = RPOR4_INIT;
    //    RPOR5 = RPOR5_INIT;
    //    RPOR6 = RPOR6_INIT;
    //    RPOR7 = RPOR7_INIT;
    //    RPOR8 = RPOR8_INIT;
    //    RPOR9 = RPOR9_INIT;
}


/*=============MCU中断初始化====================*/
static void INIT_SECTION McuIntInitialize(void) {
    //IcIntInitialize(6);
    AdcIntInitialize(7);//用户中断里，优先级7为最高
}

/*=============MCU初始化====================*/
void INIT_SECTION McuInitialize(void) {
    McuPortInitialize();
    McuPpsInitialize();
    McuSpi1Initialize();
    McuTimer3Initialize();
    McuIcInitialize();
    //McuUart2Initialize();
    McuPwmInitialize();
    McuCompInitialize();
    McuAdcInitialize();
    McuIntInitialize();
}





