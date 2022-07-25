/*============================================================================*/
//使用MCU：dsPIC33EP128MC506
//文件名：Motor.c
//文件功能：电机运行控制
//日期：2022年3月25日
/*============================================================================*/
#include "Moto.h"
#include "Error.h"
#include "../HARDWARE/Key.h"
#include "../HARDWARE/Adc.h"
#include "../HARDWARE/Led.h"
#include "Kernel.h"

UNION_MOTORFLAGS MOTO_RAM Motor_Flag;
tMotor_Type MOTO_RAM tMotor;

/*
 * 函数功能：电机模块初始化
 * 函数输入：电机方向
 * 函数输出：无
 * 设置电机旋转方向 
 * 设置状态机为停止态 确保ADC中断里状态机不会循环
 * 设置电机标志为停 确保外力误将电机拧动也不会触发换相
 */
void MOTO_SECTION MotorInitialize(unsigned char direction) {
    Motor_Flag.Bits.Direction = direction;
    tKernel.State = KERNEL_STATE_STOP;
    Motor_Flag.Bits.Status = 0;
}

/*
 * 函数功能：电机启停控制
 * 函数输入：无
 * 函数输出：无
 */
static void MOTO_SECTION MotorRunStopControl(void) {
    if (Motor_Flag.Bits.Status == 0) {
        //无异常，有占空比，启动键按下 均满足电机才能启动
        if ((Error_Flag.Word == 0) && (tAdc.PotValue > 0) && (tKey.FLAG.BITS.Pressed == 1)) {
        //if (tAdc.PotValue > 0) {
            Motor_Flag.Bits.Status = 1; 
            tKey.FLAG.BITS.Pressed = 0;
            KernelStartUp();

        }
    } else if ((Motor_Flag.Bits.ReqOff == 1) || (tAdc.PotValue == 0)) {
    //else if (tAdc.PotValue == 0) {
        Motor_Flag.Bits.Status = 0; //Status置为0，说明电机处于停止状态
        Motor_Flag.Bits.ReqOff = 0; //清零，为后续故障请求停机做准备。
        KernelStop(); //状态机的状态修改为停止状态
    }
}

/*
 * 函数功能：电机驱动模块
 * 函数输入：无
 * 函数输出：无
 */
void MOTO_SECTION MotorModule(void) {
    KeyScan(); //检测是否按下启动键
    MotorRunStopControl();
}







