#include "User.h"
#include "../HARDWARE/HardWare.h"
#include "../SYSTEM/Kernel.h"
#include "../SYSTEM/Error.h"
#include "../SYSTEM/Moto.h"
#include "../SYSTEM/Math.h"

/*=============应用层初始化====================*/
static void INIT_SECTION AppInitialize(void) {
    MotorInitialize(CCW);
    Spi_Data_Initialize();
}

int MAIN_SECTION StartProgram() {
    DISIE();
    McuInitialize();
    LED1_PIN = LED_ON; //MCU初始化结束
    AppInitialize();
    tSysTick.TickStartup = 1000; //上电初始化完成后，延时1000ms等待硬件稳定
    ENIE();
    while (tSysTick.TickStartup); //这1s内主要等待Vbus电压和旋钮电压稳定
    //电机停止，IC中断不会发生，ADC中断一直发生（但是状态机不会运行）
    LED1_PIN = LED_OFF; //延时结束

    while (1) {
        AdcModule(); //随时获取Vbus电压和旋钮电压
        MotorModule(); //随时检测是否启动电机或停止电机
        ErrorModule(); //随时检测是否有异常 定时闪烁错误指示灯
    }
    return 0;
}





