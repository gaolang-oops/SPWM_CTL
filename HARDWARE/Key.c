/*==================================================
文件描述：Key文件
使用MCU：dsPIC33EP128MC506
文件名：Key.c
文件功能：Key驱动
作者：高朗
==================================================*/
#include "Key.h"
/*------------------------------------------------------------------------*/
extern void Delay(void); //汇编延时函数 位于system目录内

tKey_Type KEY_RAM tKey;

void KEY_SECTION KeyScan(void) {
    static unsigned char key_down_flag = 0;
    if (KEY1_PIN == KEY_DOWN) {
        Delay();
        if (KEY1_PIN == KEY_DOWN)
            key_down_flag = 1;
    } else {
        if (key_down_flag == 1) { //之前按下key1，现在松开为一次。记录到Pressed
            key_down_flag = 0;
            tKey.FLAG.BITS.Pressed = 1;
        }
    }
}
/*------------------------------------------------------------------------*/ 