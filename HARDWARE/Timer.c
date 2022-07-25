#include "Timer.h"

/*=============MCU_Timer3初始化====================*/
void INIT_SECTION McuTimer3Initialize(void) {
    T3CONbits.TON = 0; //关闭定时器3
    T3CON = T3CON_INIT; //T3CON寄存器配置
    TMR3 = TMR3_INIT; //设定定时器3初始计数值为零
    PR3 = PR3_INIT; //设定定时器3周期寄存器初始值，1ms中断一次
    T3CONbits.TON = 1; //打开定时器3
}
