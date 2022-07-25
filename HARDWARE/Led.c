/*==================================================
文件描述：Led文件
使用MCU：dsPIC33EP128MC506
文件名：Led.c
文件功能：Led驱动
作者：高朗
==================================================*/
#include "Led.h"

void LED_SECTION Led_All_On(void) {
    LED0_PIN = LED1_PIN = LED2_PIN = LED3_PIN = LED_ON; //利用LAT寄存器写入值
}

void LED_SECTION Led_All_Off(void) {
    LED0_PIN = LED1_PIN = LED2_PIN = LED3_PIN = LED_OFF; //利用LAT寄存器写入值
}

