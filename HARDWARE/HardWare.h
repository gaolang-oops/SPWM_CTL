/* 
 * File:   HardWare.h
 * Author: GaoLa
 *
 * Created on 2022年6月26日, 下午6:31
 */

#ifndef HARDWARE_H
#define	HARDWARET_H
#include "../USER/User.h"
/********所有外设头文件*********/
#include "Led.h"
#include "Key.h"
#include "Ic.h"
#include "Timer.h"
#include "Pwm.h"
#include "Adc.h"
#include "Spi.h"
/*******************************/

extern void INIT_SECTION McuInitialize(void);

#endif	/* HARDWARE_H */

