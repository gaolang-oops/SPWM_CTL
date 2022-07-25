/* 
 * File:   Pwm.h
 * Author: GaoLa
 *
 * Created on 2022年6月28日, 下午8:01
 */

#ifndef PWM_H
#define	PWM_H
#include "../USER/User.h"

#if PWM_MODE
/*--------------方波控制：上桥斩波，下桥恒通。独立时基边沿对齐 PWM模块寄存器初始值宏定义--------------------*/
#define PTCON_INIT      0x0000
#define PTCON2_INIT     0x0000  //设置PWM模块的计数器的计数频率。使用默认的1分频，PWM模块以Fosc = 120MHz进行计数
//PWM发生器1寄存器初始值宏定义
#define PWMCON1_INIT    0x0280  //选择独立时基模式：ITB=1。PDC1寄存器为PWM发生器1提供占空比：MDCS=0。使用边沿对齐模式：CAM=0
#define IOCON1_INIT     0xcd00  //PWM引脚由PWM模块来控制，PWM输出有效电平是高电平，使能PWM1L引脚改写，PWM1L引脚输出低电平
#define FCLCON1_INIT    0x0003  //故障控制信号源选择位 选择故障1，3表示禁用故障输入
#define PHASE1_INIT     PWM_PERIOD_VALUE  //PWM载波频率6000=FOSC/PWM载波频率/预分频比=120MHZ/20KHZ/1
#define PDC1_INIT       300     //占空比初始值300 120Mhz时，300/6000表示占空比为5%
#define DTR1_INIT       0x0000  //死区寄存器为0，因为是边沿对齐模式
#define ALTDTR1_INIT    0x0000  //死区寄存器为0，因为是边沿对齐模式
#define TRGCON1_INIT    0x0000  //TRGCON1_INIT触发控制寄存器，0x0000就是触发事件没有延时，每个触发事件都会有触发信号的输出。触发ADC采样转换。
#define TRIG1_INIT      300     //设置触发值。也就是设置触发时刻点。当独立时基计数器（PTMRx）寄存器值与指定的TRIGx 寄存器值匹配时，将会产生ADC 触发信号。
//PWM发生器2寄存器初始值宏定义
#define PWMCON2_INIT    0x0280
#define IOCON2_INIT     0xcd00
#define FCLCON2_INIT    0x0003  
#define PHASE2_INIT     PWM_PERIOD_VALUE 
#define PDC2_INIT       300     
#define DTR2_INIT       0x0000  
#define ALTDTR2_INIT    0x0000  
//PWM发生器3寄存器初始值宏定义
#define PWMCON3_INIT    0x0280 
#define IOCON3_INIT     0xcd00  
#define FCLCON3_INIT    0x0003  
#define PHASE3_INIT     PWM_PERIOD_VALUE    
#define PDC3_INIT       300     
#define DTR3_INIT       0x0000  
#define ALTDTR3_INIT    0x0000
#else
/*--------------独立时基中心对齐 PWM模块寄存器初始值宏定义--------------------*/
#define PTCON_INIT      0x0000
#define PTCON2_INIT     0x0000
//PWM发生器1寄存器初始值宏定义
#define PWMCON1_INIT    0x0204  //选择独立时基模式：ITB=1。施加正死区DTC=00。PDC1寄存器为PWM发生器1提供占空比：MDCS=0。使用中心对齐模式：CAM=1
#define IOCON1_INIT     0xc000  //PWM引脚1H和1L全部由PWM模块来控制，PWM输出有效电平是高电平。pwm互补输出模式
#define FCLCON1_INIT    0x0003  //故障控制信号源选择位 选择故障1，3表示禁用故障输入
#define PHASE1_INIT     PWM_PERIOD_VALUE  //设置PWM载波频率为20KHZ. PHASE1：3000=FOSC/PWM载波频率/预分频比/2=120MHZ/20KHZ/1/2
#define PDC1_INIT       300     //占空比初始值300 120Mhz时，300表示占空比为10%
//互补pwm方式有死区，不能将初始占空比设置为0，不然无法插入死区
#define DTR1_INIT       0x0000  //中心对齐模式下，死区只由ALTDTR1决定
#define ALTDTR1_INIT    ALIGN_CENTER_DEAD_TIME  //中心对齐模式，死区时间为2us。ALTDTR1=Fosc*死区时间/pwm时钟预分频比=120*2/1=240=F0 
#define TRGCON1_INIT    0x1000  //TRGCON1_INIT触发控制寄存器，0x1000就是产生第一个触发事件前不用等待PWM周期。每2个触发事件触发信号的输出。触发ADC采样转换。
#define TRIG1_INIT      3000    //设置触发值。也就是设置触发时刻点。在下桥开通，PWMxL高电平的中点去触发ADC采样
//PWM2 PWM2不设置TRGCON1和TRIG1，因为我们只需要一个触发源就可以触发ADC开始转换了

//PWM发生器2寄存器初始值宏定义
#define PWMCON2_INIT    0x0204
#define IOCON2_INIT     0xc000
#define FCLCON2_INIT    0x0003  
#define PHASE2_INIT     PWM_PERIOD_VALUE 
#define PDC2_INIT       300     
#define DTR2_INIT       0x0000  
#define ALTDTR2_INIT    ALIGN_CENTER_DEAD_TIME  
//PWM发生器3寄存器初始值宏定义
#define PWMCON3_INIT    0x0204 
#define IOCON3_INIT     0xc000  
#define FCLCON3_INIT    0x0003  
#define PHASE3_INIT     PWM_PERIOD_VALUE    
#define PDC3_INIT       300     
#define DTR3_INIT       0x0000  
#define ALTDTR3_INIT    ALIGN_CENTER_DEAD_TIME
#endif 

extern void INIT_SECTION McuPwmInitialize(void);
/*占空比输入：PwmDuty% [0,100] */
extern void PWM_SECTION PwmDutySet(unsigned int PwmDuty1, unsigned int PwmDuty2, unsigned int PwmDuty3);

#endif	/* PWM_H */

