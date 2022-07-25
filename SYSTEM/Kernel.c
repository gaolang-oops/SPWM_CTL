#include "Kernel.h"
#include "Error.h"
#include "Moto.h"
#include "Rotor.h"
#include "../HARDWARE/Led.h"
#include "../SYSTEM/Math.h"
/*
 * 系统时基定义
 */
tSysTick_Type SYSTICK_RAM tSysTick;
tKernel_Type SYS_RAM tKernel;

extern void Delay(void); //汇编延时函数 位于system目录内

/*
 * 该函数被adc中断调用
 * 20KHz的pwm波每50us触发ADC模块转换数据,则每50us tSysTick.Tick50us 自加1
 * 产生PWM_NUM_1MS个PMW波后，证明1ms时间到 tSysTick.TickStartup 自减1
 * SysTick.TickStartup 自减到零证明1s到了，MCU初始化延时结束
 */
void SYS_SECTION Sys_CntUp_Timer(void) {
    tSysTick.Tick50us++;
    if (tSysTick.Tick50us >= PWM_NUM_1MS)//20*50us=1ms
    {
        tSysTick.Tick50us = 0;
        //1000ms Sys_CntUp_Timer指示灯闪烁一次
        if (tSysTick.Tick1ms > 1000) {
            LED2_PIN = ~LED2_PIN;
            tSysTick.Tick1ms = 0;
        }
        tSysTick.Tick1ms++;
        if (tSysTick.TickStartup != 0)
            tSysTick.TickStartup--;
        if (Led_Count != 0) {
            Led_Count--;
        }
    }
}

/*
 * 函数功能：系统启动
 * 函数输入：无
 * 函数输出：无
 */
void SYS_SECTION KernelStartUp(void) {
    tKernel.State = KERNEL_STATE_READY;
}

/*
 * 函数功能：系统停止
 * 函数输入：无
 * 函数输出：无
 */
void SYS_SECTION KernelStop(void) {
    tKernel.State = KERNEL_STATE_STOP;
    CloseAllMos();
    LED0_PIN = LED_OFF;
}

/*
 * 函数功能：关闭六个MOS管
 * 函数输入：无
 * 函数输出：无
 * 从PWM发出关断信号到mos管真正关断是需要一定时间的
 * 如果这里closeAllMos立马根据输出带占空比的pwm波开通mos管，则可能还没有彻底关断就打开了，导致短路
 */
void SYS_SECTION CloseAllMos(void) {
    __builtin_write_PWMSFR(&IOCON1, IOCON_HL_INVALID, &PWMKEY);
    __builtin_write_PWMSFR(&IOCON2, IOCON_HL_INVALID, &PWMKEY);
    __builtin_write_PWMSFR(&IOCON3, IOCON_HL_INVALID, &PWMKEY);
}

/*
 * 函数功能：关闭三个上管，打开三个下管，用于自举电容充电
 * 函数输入：无
 * 函数输出：无
 */
static void SYS_SECTION BootCharge(void) {
    __builtin_write_PWMSFR(&IOCON1, IOCON_HINVALID_LPWM, &PWMKEY);
    __builtin_write_PWMSFR(&IOCON2, IOCON_HINVALID_LPWM, &PWMKEY);
    __builtin_write_PWMSFR(&IOCON3, IOCON_HINVALID_LPWM, &PWMKEY);
}

/*
 * 函数功能：六个MOS管以互补PWM波控制
 * 函数输入：无
 * 函数输出：无
 */
static void SYS_SECTION WorkPwmOutput(void) {
    __builtin_write_PWMSFR(&IOCON1, IOCON_HPWM_LPWM, &PWMKEY);
    __builtin_write_PWMSFR(&IOCON2, IOCON_HPWM_LPWM, &PWMKEY);
    __builtin_write_PWMSFR(&IOCON3, IOCON_HPWM_LPWM, &PWMKEY);
}

/*
 * 函数功能：系统运行状态控制
 * 函数输入：无
 * 函数输出：无
 * 在ADC中断中调用，而ADC中断每50us触发
 */
void SYS_SECTION KernelRunStateMachine(void) {
    if (tKernel.DownCounter != 0)
        tKernel.DownCounter--; //每50us递减
    switch (tKernel.State) {
        case KERNEL_STATE_STOP:
            KernelStop();
            break;
        case KERNEL_STATE_READY:
            BootCharge();
            tKernel.DownCounter = 1000; //设置向下计数变量为1000，如果它从1000减到0，那么就表示50ms的时间充电时间
            tKernel.State = KERNEL_STATE_INIT;
            break;
        case KERNEL_STATE_INIT:
            if (tKernel.DownCounter <= 0) {
                //从PWM发出关断信号到mos管真正关断是需要一定时间的
                //如果这里closeAllMos立马根据输出带占空比的pwm波开通mos管，则可能还没有彻底关断就打开了，导致短路   
                CloseAllMos();
                //Delay(); //汇编延时函数 确保mos管彻底关闭
                HallInitialize();//用于确定初始启动时的转子位置角
                WorkPwmOutput();//六个MOS管以互补PWM波控制
                LED0_PIN = LED_ON; //电机运行指示灯
                tKernel.State = KERNEL_STATE_RUN;   
            }
            break;
        case KERNEL_STATE_RUN:            
            GetRotorInfo();      
            if (Motor_Flag.Bits.Direction)
                tUm.Angle = tHall.Eangle_Rotor + EANGLE90;
            else
                tUm.Angle = tHall.Eangle_Rotor - EANGLE90;
            //根据这个角度值查表，查表得到的正弦值，余弦值
            //求解三相相位相差120度的正弦波
            GetUabc(tUm.Angle);
            //正弦波的波形变换后，输出脉冲波。
            SpwmOut();
            break;
        default:
            break;
    }
}