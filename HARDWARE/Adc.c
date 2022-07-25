/*============================================================================*/
//使用MCU：dsPIC33EP128MC506
//文件名：Adc.c
//文件功能：模数转换模块数据读取及其处理
//日期：2022年3月25日
/*============================================================================*/

//头文件声明
#include "Adc.h"
#include "Led.h"
#include "../SYSTEM/Kernel.h"
#include "../SYSTEM/Math.h"
#include "Spi.h"

tAdc_Type ADC_RAM tAdc;

/*
 * 1.65V参考电压输出功能 - 寄存器初始化
 * 1.65V参考电压主要作用是供给芯片内部比较器使用
 * 1.65V参考电压输出功能是为了满足用户需要。这里我们输出到引脚RB8
 */
void INIT_SECTION McuCompInitialize(void) {
    CVRCON = CVRCON_INIT;
}

/*
 * ADC模块 - 寄存器初始化
 */
void INIT_SECTION McuAdcInitialize(void) {
    AD1CON1bits.ADON = 0; //禁止ADC模块
    AD1CON1 = AD1CON1_INIT;
    AD1CON2 = AD1CON2_INIT;
    AD1CON3 = AD1CON3_INIT;
    AD1CON4 = AD1CON4_INIT;
    AD1CHS123 = AD1CHS123_INIT;
    AD1CHS0 = AD1CHS0_INIT;
    AD1CSSH = AD1CSSH_INIT;
    AD1CSSL = AD1CSSL_INIT;
    AD1CON1bits.ADON = 1; //使能ADC模块
}

/*
 * ADC转换数据中断初始化
 */
void INIT_SECTION AdcIntInitialize(unsigned int IPC) {
    //清除ADC转换数据中断标志位
    IFS0bits.AD1IF = 0;
    //设置ADC转换数据中断优先级位为6 用户中断里，优先级7为最高
    IPC3bits.AD1IP = IPC;
    //使能ADC转换数据中断允许位
    IEC0bits.AD1IE = 1;
}

/*
 * 函数功能：Vbus转换数据滤波
 * 函数输入：无
 * 函数输出：无
 */
static void ADC_SECTION Vbus_Value_Filter(void) {
    //Vbus电压 64次平均滤波处理
    tAdc.An3.ValueSum += tAdc.An3.ValueInstant;
    tAdc.An3.ValueNum++;
    if (tAdc.An3.ValueNum >= ANU_SAMPLE_NUM) {
        tAdc.An3.ValueAverage = tAdc.An3.ValueSum >> 6;
        tAdc.An3.ValueSum = 0;
        tAdc.An3.ValueNum = 0;
    }
}

/*
 * 函数功能：旋钮电压转换数据滤波
 * 函数输入：无函数输出：无
 */
static void ADC_SECTION Pot_Volt_Filter(void) {
    //旋钮电压 8次平均滤波处理            
    tAdc.An4.ValueSum += tAdc.An4.ValueInstant;
    tAdc.An4.ValueNum++;
    if (tAdc.An4.ValueNum >= ANP_SAMPLE_NUM) {
        tAdc.An4.ValueAverage = tAdc.An4.ValueSum >> 3;
        tAdc.An4.ValueSum = 0;
        tAdc.An4.ValueNum = 0;
    }
}

/*
 * 函数功能：转换数据读取
 * 函数输入：无
 * 函数输出：无
 */
static void ADC_SECTION GetAdcValue(void) {
    switch (tAdc.Index) {
        case(3):
            tAdc.An3.ValueInstant = ADC1BUF0;
            tAdc.An0.ValueInstant = ADC1BUF1;
            tAdc.An1.ValueInstant = ADC1BUF2;
            tAdc.An2.ValueInstant = ADC1BUF3;
            Vbus_Value_Filter();
            AD1CHS0 = 0x0404;
            tAdc.Index = 4;
            break;

        case(4):
            tAdc.An4.ValueInstant = ADC1BUF0;
            tAdc.An0.ValueInstant = ADC1BUF1;
            tAdc.An1.ValueInstant = ADC1BUF2;
            tAdc.An2.ValueInstant = ADC1BUF3;
            Pot_Volt_Filter();
            AD1CHS0 = 0x0606;
            tAdc.Index = 6;
            break;

        case(6):
            tAdc.An6.ValueInstant = ADC1BUF0;
            tAdc.An0.ValueInstant = ADC1BUF1;
            tAdc.An1.ValueInstant = ADC1BUF2;
            tAdc.An2.ValueInstant = ADC1BUF3;
            AD1CHS0 = 0x0303;
            tAdc.Index = 3;
            break;

        default:
            tAdc.An3.ValueInstant = ADC1BUF0;
            tAdc.An0.ValueInstant = ADC1BUF1;
            tAdc.An1.ValueInstant = ADC1BUF2;
            tAdc.An2.ValueInstant = ADC1BUF3;
            AD1CHS0 = 0x0404;
            tAdc.Index = 4;
    }
}

/*
 * 函数功能：Vbus电压刷新
 * Vbus电压 每一个pwm周期50us取得一次值，64次平均后写入tAdc.An3.ValueAverage
 * 故，每3.2ms（50us*64)才能刷新出新的Vbus电压值
 * 上电中断开启后，小于64次时avenge为零，所以开机延时1s等待Vbus电压和旋钮电压稳定
 * VBUS=3.3/1023*tAdc.An3.ValueAverage/2k*32k=tAdc.An3.ValueAverage*53/1023
 * tAdc.An3.ValueAverage*53 >> 10
 */
static void ADC_SECTION VbusVolt_Refresh(void) {
    UNION_U32 unTemp32;
    unTemp32.U32 = __builtin_muluu(VBUS_FACTOR, tAdc.An3.ValueAverage);
    unTemp32.U32 >>= 10;
    tAdc.BusValue = unTemp32.Words.Low;
}

/*
 * 函数功能：调速旋钮结果处理
 * 函数输入：无
 * 函数输出：无
 */
static void ADC_SECTION AdcPotProcess(void) {
    unsigned int Temp;
    UNION_U32 Temp32;
    //最大电压值3.3v对应10位，则为0x3FF， << 6归一化后为65472，对应小数0.999
    Temp = tAdc.An4.ValueAverage << 6; //先归一化为无符号整数  
    //归一化结果转换到占空比值 65472*3000 然后右移16位，得2997
    Temp32.U32 = __builtin_muluu(Temp, PWM_PERIOD_VALUE);
    Temp = Temp32.Words.High;
    if (Temp < MINDUTY)
        tAdc.PotValue = 0;
    else
        tAdc.PotValue = Limit_Max(Temp, MAXDUTY);
}

/*
 * 函数功能：ADC模块处理
 * 函数输入：无
 * 函数输出：无
 */
void ADC_SECTION AdcModule(void) {
    AdcPotProcess();
    VbusVolt_Refresh();
}

/*
 * 函数功能：AD转换完成中断服务函数 
 * 20KHz的pwm波每50us触发ADC模块转换数据
 * 函数输入：无
 * 函数输出：无
 * 测试得中断内函数执行时间39us
 * ADC中断使用了shadow属性，其他中断无法使用shadow了
 */
void __attribute__((section(".adc_section"), interrupt, shadow, no_auto_psv)) _AD1Interrupt(void) {
    //LED1_PIN = LED_ON;
    IFS0bits.AD1IF = 0; //清除ADC转换完成标志位
    SpiTransmit();
    GetAdcValue(); //获取ADC转换结果+vbus和旋钮电压滤波
    KernelRunStateMachine(); //状态机基于这个50us中断进行监控
    Sys_CntUp_Timer(); //计数器
    //LED1_PIN = LED_OFF; //通过测试led的引脚高电平持续时间。可以验证中断执行时间和多久进入中断
}



