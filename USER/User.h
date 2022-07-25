/* 
 * File:   User.h
 * Author: GaoLa
 *
 * Created on 2022年6月26日, 下午6:46
 */
/*============================================================================*/
//使用MCU：dsPIC33EP128MC506
//文件功能：用户设定参数头文件
/*============================================================================*/
#ifndef USER_H
#define	USER_H
#include "../SOC/p33EP128MC506.h"

/*=============宏定义====================*/
/*==============================================================================
中断使能/失能宏定义 GIC控制中断开和关
==============================================================================*/
#define    ENIE()     {INTCON2 = 0x8000;} 
#define    DISIE()    {INTCON2 = 0x0000;} 
// 寄存器7-1： SR：CPU 状态寄存器(1)：上电默认000 = CPU 中断优先级为0 （8）所有用户中断都可以响应
/*==============================================================================
 * 利用CPU_IPL寄存器设置中断门槛 可以达到同样效果
//#define ENIE()  SET_CPU_IPL(6)//如果程序里只有Timer3一个中断，
//把CPU中断优先级降低1位（7-1=6），这样就可以响应用户中断优先级为7的中断
//#define DISIE()  SET_CPU_IPL(7)

////SET_CPU_IPL宏在506.h内定义：
//// #define SET_CPU_IPL(ipl) {       \
////  SRbits.IPL = ipl;              \
////  __builtin_nop();               \
//// } (void) 0
==============================================================================*/

/*==============================================================================
//代码段宏定义
==============================================================================*/
#define MAIN_SECTION    __attribute__((section(".main_section")))
#define INIT_SECTION    __attribute__((section(".init_section")))
#define SYS_SECTION     __attribute__((section(".sys_section")))
#define ERROR_SECTION     __attribute__((section(".error_section")))
#define MOTO_SECTION     __attribute__((section(".moto_section")))
#define ROTOR_SECTION     __attribute__((section(".rotor_section")))
#define LED_SECTION     __attribute__((section(".led_section")))
#define KEY_SECTION     __attribute__((section(".key_section")))
#define IC_SECTION      __attribute__((section(".ic_section")))
#define TIMER_SECTION   __attribute__((section(".timer_section")))
#define PWM_SECTION     __attribute__((section(".pwm_section")))
#define ADC_SECTION     __attribute__((section(".adc_section")))
#define SPI_SECTION     __attribute__((section(".spi_section")))
#define MATH_SECTION     __attribute__((section(".math_section")))
/*==============================================================================
//数据段宏定义
==============================================================================*/
#define MAIN_RAM    __attribute__((section(".main_ram")))
#define SYS_RAM     __attribute__((section(".sys_ram")))
#define SYSTICK_RAM     __attribute__((section(".systick_ram")))
#define ERROR_RAM     __attribute__((section(".error_ram")))
#define LED_RAM     __attribute__((section(".led_ram")))
#define KEY_RAM     __attribute__((section(".key_ram")))
#define HALL_RAM    __attribute__((section(".hall_ram")))
#define PWM_RAM     __attribute__((section(".pwm_ram")))
#define ADC_RAM     __attribute__((section(".adc_ram")))
#define SPI_RAM     __attribute__((section(".spi_ram")))
#define MOTO_RAM     __attribute__((section(".moto_ram")))
#define ROTOR_RAM     __attribute__((section(".rotor_ram")))
#define ROTORTMP_RAM     __attribute__((section(".rotortmp_ram")))
#define MATH_RAM     __attribute__((section(".math_ram")))
/*==============================================================================
 PWM - 模式宏定义
==============================================================================*/
#define PWM_MODE PWM_CENTER_ALIGNMENT
#define PWM_EDGE_ALIGNMENT 1
#define PWM_CENTER_ALIGNMENT 0
/*==============================================================================
 PWM - 载波频率宏定义
==============================================================================*/
#define    CARRIER_FREQUENCY   20000 //PWM载波频率 20KHz 既1s有20 000个波形
#if PWM_MODE 
#define    PWM_PERIOD_VALUE    (120000000 / CARRIER_FREQUENCY)  //120MHz/20KHz=6000 既时基计数6000为一个波形
/*
 * 最大、最小占空比设置
 */
#define    MAXDUTY    6000
#define    MINDUTY    300
#else
#define    PWM_PERIOD_VALUE    (120000000 / CARRIER_FREQUENCY / 2)  //120MHz/20KHz/2=3000 独立时基 中心对齐
#define    MAXDUTY    3000
#define    MINDUTY    300
#endif 
/*==============================================================================
 PWM - 参数宏定义
==============================================================================*/
#define ALIGN_CENTER_DEAD_TIME    0x00F0  //中心对齐模式，死区时间为2us。ALTDTR1=Fosc*死区时间/pwm时钟预分频比=120*2/1=240=F0 
#define PWM_NUM_1MS   (CARRIER_FREQUENCY/1000) //PWM频率是CARRIER_FREQUENCY，除以1000既是每1ms需要有多少个PWM产生



/*
 * 电压监测系数
 */
#define    VBUS_FACTOR        53
#define    VBUS_LOW_LIMIT     18    //18v报警
#define    VBUS_HIGH_LIMIT    30    //30v报警

/*
 * 电机旋转方向
 * counterclockwise：逆时针方向的;
 * clockwise：顺时针方向的; 顺时针方向(的);
 */
#define    CW     0 
#define    CCW    1  

/*
 * 宏定义限制大小 及限制范围
 */
#define Limit_Max(x,max) ((x)>(max)?(max):(x))
#define Limit_Min(x,min) ((x)<(min)?(min):(x))
#define Limit_Val(x,min,max) ((x)<(min)?(min):((x)>(max)?(max):(x)))

/*---------------------------------------------------------------------------*/
//NOP操作宏定义
#define     NOP()       __builtin_nop()
#define     DELAY100NS()    NOP();NOP();NOP();NOP();NOP();NOP()
/*---------------------------------------------------------------------------*/

/*
 * 联合体类型定义
 */
typedef union {
    unsigned long U32;
    struct {
        unsigned int Low;
        unsigned int High;
    } Words;
} UNION_U32;

typedef union {
    signed long S32;
    struct {
        signed int Low;
        signed int High;
    } Words;
} UNION_S32;

typedef union {
    unsigned int Word;
    struct {
        unsigned B0 : 1;
        unsigned B1 : 1;
        unsigned B2 : 1;
        unsigned B3 : 1;
        unsigned B4 : 1;
        unsigned B5 : 1;
        unsigned B6 : 1;
        unsigned B7 : 1;
        unsigned B8 : 1;
        unsigned B9 : 1;
        unsigned B10 : 1;
        unsigned B11 : 1;
        unsigned B12 : 1;
        unsigned B13 : 1;
        unsigned B14 : 1;
        unsigned B15 : 1;
    } Bits;
} UNION_WORD;

#endif	/* USER_H */

