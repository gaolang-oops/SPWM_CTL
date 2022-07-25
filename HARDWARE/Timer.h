/* 
 * File:   Timer.h
 * Author: GaoLa
 *
 * Created on 2022年6月26日, 下午9:57
 */

#ifndef TIMER_H
#define	TIMER_H
#include "../USER/User.h"
/*--------------Timer3寄存器初始值宏定义--------------------*/
//在空闲模式下模块继续工作。时钟源选择内部时钟（FP）。输入时钟预分频比1:256 60MHZ
//如果是60MHz,  60/256=0.2344MHz 1/0.2344MHz=4.2662us,  4.2662*66536/1000=283.8559ms
#define T3CON_INIT      0x0030 
//计数器初始值设置为零
#define TMR3_INIT       0x0000 
//设定周期寄存器值为234(0x00EA)，如果想要一个周期既为1ms。1000us/4.27=234 
#define PR3_INIT        0x00EA 

extern void INIT_SECTION McuTimer3Initialize(void);

#endif	/* TIMER_H */

