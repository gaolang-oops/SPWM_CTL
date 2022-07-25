/* 
 * File:   Timer.h
 * Author: GaoLa
 *
 * Created on 2022��6��26��, ����9:57
 */

#ifndef TIMER_H
#define	TIMER_H
#include "../USER/User.h"
/*--------------Timer3�Ĵ�����ʼֵ�궨��--------------------*/
//�ڿ���ģʽ��ģ�����������ʱ��Դѡ���ڲ�ʱ�ӣ�FP��������ʱ��Ԥ��Ƶ��1:256 60MHZ
//�����60MHz,  60/256=0.2344MHz 1/0.2344MHz=4.2662us,  4.2662*66536/1000=283.8559ms
#define T3CON_INIT      0x0030 
//��������ʼֵ����Ϊ��
#define TMR3_INIT       0x0000 
//�趨���ڼĴ���ֵΪ234(0x00EA)�������Ҫһ�����ڼ�Ϊ1ms��1000us/4.27=234 
#define PR3_INIT        0x00EA 

extern void INIT_SECTION McuTimer3Initialize(void);

#endif	/* TIMER_H */

