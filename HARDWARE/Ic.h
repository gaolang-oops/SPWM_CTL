/* 
 * File:   HALL_IC.h
 * Author: GaoLa
 *
 * Created on 2022年6月26日, 下午8:24
 */

#ifndef HALL_IC_H
#define	HALL_IC_H
#include "../USER/User.h"

/*--------------输入捕捉模块控制寄存器初始值宏定义--------------------*/
/*
 * ICxCON1：输入捕捉x 控制寄存器1
 * 0 = 在CPU 空闲模式下输入捕捉将继续工作
 * 000 = T3CLK 是ICx 的时钟源
 * 00 = 每次捕捉事件产生一次中断
 * 0 = 未发生输入捕捉缓冲区溢出
 * 001 = 捕捉模式，每个边沿（上升沿和下降沿）捕捉一次
 * 
 * ICxCON2：输入捕捉x 控制寄存器2
 * 0 = 禁止级联模块操作
 * 我们这里的需求很简单，只需要定时器能够计数满之后，复位清零即可，
 * 不需要其它条件的参与来让定时器复位。所以，实际上，
 * 我们完全用不到触发或者同步功能。所以，这5个位，
 * 我们需要设置为，没有触发源或者同步源工作。也就是让定时器自己计满复位。
 */
//个人理解：需要使能T3CLK，这样ICxBUF才有计数值。如果不需要计算沿之间的时间，可以不使能T3CLK
//T3CLK是16位的计数器，1us计数1次 则这个输入捕捉定时器的最大计数时长是 65.535ms
#define IC1CON1_INIT      0x0001
#define IC1CON2_INIT      0x0000
#define IC2CON1_INIT      0x0001
#define IC2CON2_INIT      0x0000
#define IC3CON1_INIT      0x0001
#define IC3CON2_INIT      0x0000

extern void INIT_SECTION McuIcInitialize(void);
extern void INIT_SECTION IcIntInitialize(unsigned int IPC);
#endif	/* HALL_IC_H */

