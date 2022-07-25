/* 
 * File:   Error.h
 * Author: GaoLa
 *
 * Created on 2022年7月3日, 下午12:49
 */

#ifndef ERROR_H
#define	ERROR_H
#include "../USER/User.h"

/*
 * 宏定义
 */
#define LED_TICK_TIME 	250				//250ms
#define LED_OFF_TIME 	4				//2 flash time = 4 x 2 x 250ms = 2s

typedef union {
    unsigned int Word;
    struct {
        unsigned Hall : 4;
        unsigned OverVol : 1;
        unsigned LackVol : 1;
        unsigned Unused : 10;
    } Bits;
} UNION_ERRORFLAGS;

extern unsigned int ERROR_RAM Led_Count;
extern UNION_ERRORFLAGS ERROR_RAM Error_Flag;
extern void ERROR_SECTION ErrorModule(void);

#endif	/* ERROR_H */

