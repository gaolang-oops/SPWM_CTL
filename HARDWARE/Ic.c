#include "Ic.h"
#include "../SYSTEM/Rotor.h"
#include "../SYSTEM/Moto.h"
#include "Led.h"

/*=============MCU输入捕捉模块初始化====================*/
void INIT_SECTION McuIcInitialize(void) {
    //输入捕捉1模块寄存器初始化
    IC1CON1 = IC1CON1_INIT;
    IC1CON2 = IC1CON2_INIT;
    //输入捕捉2模块寄存器初始化
    IC2CON1 = IC2CON1_INIT;
    IC2CON2 = IC2CON2_INIT;
    //输入捕捉3模块寄存器初始化
    IC3CON1 = IC3CON1_INIT;
    IC3CON2 = IC3CON2_INIT;
    //输入捕捉4模块寄存器初始化
}

/*=============输入捕获中断初始化====================*/
void INIT_SECTION IcIntInitialize(unsigned int IPC) {
    //清除输入捕捉IC1~3中断标志位
    IFS0bits.IC1IF = 0;
    IFS0bits.IC2IF = 0;
    IFS2bits.IC3IF = 0;
    //设置输入捕捉IC1~3中断优先级位为7 用户中断里，优先级7为最高
    IPC0bits.IC1IP = IPC;
    IPC1bits.IC2IP = IPC;
    IPC9bits.IC3IP = IPC;
    //使能输入捕捉IC1~3中断允许位
    IEC0bits.IC1IE = 1;
    IEC0bits.IC2IE = 1;
    IEC2bits.IC3IE = 1;
}

#if 0
/*
 * 输入捕捉IC1~3的中断服务函数
 */
void __attribute__((section(".ic_section"), interrupt, no_auto_psv)) _IC1Interrupt(void) {
    //清除IC1的中断标志位
    IFS0bits.IC1IF = 0;
    if (Motor_Flag.Bits.Status == 1) {//电机正在运转
    GetRotorInfo(); //获取hall值
    //CommutationControl(); //换相
    }
}
void __attribute__((section(".ic_section"), interrupt, no_auto_psv)) _IC2Interrupt(void) {
    //清除IC2的中断标志位
    IFS0bits.IC2IF = 0;
    if (Motor_Flag.Bits.Status == 1) {//电机正在运转
    GetRotorInfo(); //获取hall值
    //CommutationControl(); //换相
   }
}
void __attribute__((section(".ic_section"), interrupt, no_auto_psv)) _IC3Interrupt(void) {
    //清除IC3的中断标志位
    IFS2bits.IC3IF = 0;
    if (Motor_Flag.Bits.Status == 1) {//电机正在运转
    GetRotorInfo(); //获取hall值
    //CommutationControl(); //换相
    }
}
#endif


