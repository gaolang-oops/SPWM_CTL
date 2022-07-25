/* 
 * File:   Key.h
 * Author: GaoLa
 *
 * Created on 2022年6月26日, 下午7:27
 */

#ifndef KEY_H
#define	KEY_H
#include "../USER/User.h"

//按键宏定义
/*
 * PORTx 寄存器:
 * 通过PORTx寄存器访问I/O引脚上的数据。它用于在引脚配置为输入的时候，
 * 读PORTx寄存器是读取I/O引脚上的值（读取引脚上的电平状态）
 */
#define KEY1_PIN        PORTCbits.RC1
#define KEY2_PIN        PORTCbits.RC2
#define KEY3_PIN        PORTCbits.RC11

#define KEY_DOWN        0
#define KEY_UP          1

/*----------------------------------------------------------------------------*/
typedef union
{
    unsigned int word;
    struct{
        unsigned Pressed:1;
        unsigned unused :15;
    }BITS;
}UNION_KEY_FLAG;

typedef struct
{
    UNION_KEY_FLAG FLAG;
}tKey_Type;
/*----------------------------------------------------------------------------*/
extern tKey_Type KEY_RAM tKey;
extern void KEY_SECTION KeyScan(void);
#endif	/* KEY_H */

