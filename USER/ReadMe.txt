调试记录
/****************************/
Rotor_Angle_Inc.Words.High = __builtin_divmodud(ANG_INC_COEF, tHall.Cnt_Time, &Rotor_Angle_Inc.Words.Low);
 如果除数tHall.Cnt_Time为零，会导致mcu复位
/****************************/
hall标志：(在error.c里面请求停机）
Error_Flag.Bits.Hall = 1;//hall干扰过大或者损坏，需要停机  
Error_Flag.Bits.Hall = 2;//电机旋转时hall数据异常（0或7），需要停机  
Error_Flag.Bits.Hall = 3;//电机转时hall数据没有更新，hall故障或堵转，需要停机          
/****************************/
vbus刷新问题
3.2ms才能有新数据，现在是在main中随机读取
上电中断开启后，小于64次时avenge为零，所以开机延时1s等待Vbus电压和旋钮电压稳定
/****************************/
void SYS_SECTION CloseAllMos(void) {
    __builtin_write_PWMSFR(&IOCON1, IOCON_HL_INVALID, &PWMKEY);
    __builtin_write_PWMSFR(&IOCON2, IOCON_HL_INVALID, &PWMKEY);
    __builtin_write_PWMSFR(&IOCON3, IOCON_HL_INVALID, &PWMKEY);
    Delay(); //这里插入Delay()汇编的会有bug，会影响ADC中断的时基，
//时基会变的很大，原因未知，猜测可能是内建函数后面不能接着写汇编
}
/****************************/
两套汇编正弦函数都可以使用。如果使用“核心寄存器不压栈的汇编函数”，注意要替换_tKernel


#ifndef DEFINE_H
#define DEFINE_H
#include "../SOC/p33EP128MC506.h"

#define UART_SECTION     __attribute__((section(".uart_section")))

#define UART_RAM    __attribute__((section(".uart_ram")))
#define tUART_RAM    __attribute__((section(".t_uart_ram")))

//Uart结构体定义

typedef struct {
    unsigned TxStart : 1; //该标志位等于1表示需要开始发送一包数据
    unsigned SendReq : 1; //数据发送请求。该标志位等于1表示数据已准备好，需要发送。等于0表示需要准备新的数据
    unsigned ReceReq : 1; //接收数据请求。该标志位等于1表示有数据接收了还没有处理。等于0表示空闲，没有数据在处理
    unsigned RxStart : 1; //开始接收一包数据的标志位。该标志位等于1表示有数据需要接收。等于0表示空闲
    unsigned Unusual : 1; //异常标志。该位置1为帧尾异常或者接收的数据无效
} STRUCT_UART_FLAG;

typedef struct {
    STRUCT_UART_FLAG Flag;
    unsigned int TxNum; //需发送的一个数据包里面的数据累计值 
    unsigned int TxNo; //需要发送的数据的包数计数
    unsigned int TxData; //需要发送的数据
    unsigned int TxSum; //存放发送数据的求和值
    unsigned int RxSum; //存放发送数据的求和值
    unsigned int RxNum; //接收到的一个数据包里面的数据累计值
    unsigned int RDBUFF[3]; //数组用于存放接收到的数据
} tUart_type;

#endif

#if 0
/*=============UART2串口模块初始化====================*/
static void INIT_SECTION McuUart2Initialize(void) {
    U2BRG = U2BRG_INIT;
    U2MODE = U2MODE_INIT;
    U2STA = U2STA_INIT;
}
#endif


/*--------------UART2串口模块控制寄存器初始值宏定义--------------------*/
//U2BRG =(Fcy/(16*波特率))-1=(60 000 000/(16*19200))-1=194.3125
//U2MODE 8位数据 无奇偶校验 1停止位
#define U2BRG_INIT      194
#define U2MODE_INIT     0x8000
#define U2STA_INIT      0x0400

