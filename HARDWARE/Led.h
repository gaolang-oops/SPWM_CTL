/* 
 * File:   Led.h
 * Author: GaoLa
 *
 * Created on 2022年6月26日, 下午5:01
 */
#ifndef LED_H
#define	LED_H
#include "../USER/User.h"

/*---------------LED宏定义----------------------*/
/* 
 * LATx 寄存器:
 * 专用于引脚被配置为数字输出功能的时候，往引脚输出高电平或者低电平的。
 * 相应的位中，写0就是对应引脚输出低电平，写1就是引脚输出高电平。
 */
#define LED0_PIN        LATEbits.LATE12
#define LED1_PIN        LATEbits.LATE13
#define LED2_PIN        LATEbits.LATE14
#define LED3_PIN        LATEbits.LATE15

#define LED_ON          0
#define LED_OFF         1

/* 
 * PWM波周期50us，每个50us LedCount会在_AD1Interrupt的Adc_CntUp_Timer函数里递减
 * LEDFLICK_TIME为20， 则LEDFLICK_TIME递减到零为1ms 
 */

extern void LED_SECTION Led_All_On(void);
extern void LED_SECTION Led_All_Off(void);
#endif	/* LED_H */