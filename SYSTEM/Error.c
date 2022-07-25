/*============================================================================*/
//工程描述：方波六步换相控制
//使用MCU：dsPIC33EP128MC506
//文件名：Error.c
//文件功能：故障监测
//日期：2022年3月25日
/*============================================================================*/
#include "Error.h"
#include "../HARDWARE/Adc.h"
#include "../HARDWARE/Led.h"
#include "../SYSTEM/Moto.h"
/*
 * 变量定义
 */
UNION_ERRORFLAGS ERROR_RAM Error_Flag;
unsigned char ERROR_RAM Error_Code;
/* 
 * PWM波周期50us，每个50us执行_AD1Interrupt，在_AD1Interrupt中有CntUp_Timer函数
 * 每1ms，CntUp_Timer函数里会递减 Led_Count
 */
unsigned int ERROR_RAM Led_Count;
unsigned int ERROR_RAM Led_Value;
unsigned int ERROR_RAM Led_Value_Buf;
unsigned int ERROR_RAM Led_Time_Tick;

/*
 * 函数功能：电压监测
 * 函数输入：无
 * 函数输出：无
 */
static void ERROR_SECTION VbusVoltageDetect(void) {
    if (tAdc.BusValue < VBUS_LOW_LIMIT) {
        Error_Flag.Bits.LackVol = 1;
        Error_Flag.Bits.OverVol = 0;
    } else if (tAdc.BusValue > VBUS_HIGH_LIMIT) {
        Error_Flag.Bits.LackVol = 0;
        Error_Flag.Bits.OverVol = 1;
    } else {
        Error_Flag.Bits.LackVol = 0;
        Error_Flag.Bits.OverVol = 0;
    }
}

/*函数功能：故障处理并请求停机
 * 函数输入：无
 * 函数输出：无
 * 如果hall异常同时又欠压是无法同时显示的。显示优先级：hall>overvol>lackvol
 */
static void ERROR_SECTION ErrorProcess(void) {
    if (Error_Flag.Word == 0) {//电压正常且hall没有问题
        Led_Value = 0;
    } else {
        if (Motor_Flag.Bits.Status)  //如果电机正在运行
            Motor_Flag.Bits.ReqOff = 1; //请求停机
        if (Error_Flag.Bits.Hall)
            Led_Value = 1;
        else if (Error_Flag.Bits.OverVol)
            Led_Value = 2;
        else if (Error_Flag.Bits.LackVol)
            Led_Value = 3;
        else
            Led_Value = 0;
    }
    Error_Code = Led_Value;
}

/*
 * 函数功能：故障LED显示
 * 函数输入：无
 * 函数输出：无
 */
static void ERROR_SECTION ErrorDisplay(void) {
    unsigned int Flash_Num;
    if (Led_Value != Led_Value_Buf) {
        LED3_PIN = LED_ON;  //当从vbus电压异常状态回到电压正常状态，此灯常亮，表示曾经电压异常 按复位键恢复正常
        Led_Time_Tick = 0;
        Led_Count = 0;
        Led_Value_Buf = Led_Value;
    }
    if (Led_Count == 0) {
        Led_Count = LED_TICK_TIME;
        if (Led_Value_Buf != 0) {
            Led_Time_Tick++;
            Flash_Num = Led_Time_Tick >> 1;
            if (Led_Value_Buf >= Flash_Num) {
                if ((Led_Time_Tick & 0x0001) == 0x0000)
                    LED3_PIN = LED_ON; //on
                else
                    LED3_PIN = LED_OFF; //off
            } else {
                if (Flash_Num == (Led_Value_Buf + LED_OFF_TIME))
                    Led_Time_Tick = 0;  //开始下一轮的闪烁
                LED3_PIN = LED_OFF; //off   保持闪烁中间的熄灭状态
            }
        }
    }
}

/*函数功能：故障模块
 * 函数输入：无
 * 函数输出：无
 */
void ERROR_SECTION ErrorModule(void) {
    VbusVoltageDetect();
    ErrorProcess();
    ErrorDisplay();
}


