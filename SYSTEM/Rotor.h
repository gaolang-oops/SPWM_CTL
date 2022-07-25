/* 
 * File:   Rotor.h
 * Author: GaoLa
 *
 * Created on 2022年7月3日, 下午9:37
 */

#ifndef ROTOR_H
#define	ROTOR_H
#include "../USER/User.h"

//hall信号输入宏定义
#define HALLU_Bit       PORTGbits.RG8
#define HALLV_Bit       PORTGbits.RG7
#define HALLW_Bit       PORTGbits.RG6

/*
 * hall 1~5组合值对应的，正反转需要使用的电角度
 */
#define     EANGLE0     0
#define     EANGLE30    5461
#define     EANGLE60    10922
#define     EANGLE90    16384
#define     EANGLE120   21845
#define     EANGLE150   27306
#define     EANGLE180   32768
#define     EANGLE210   38229
#define     EANGLE240   43690
#define     EANGLE270   49151
#define     EANGLE300   54613
#define     EANGLE330   60074
#define     EANGLE360   65535
#define ANG_INC_COEF   128000  //ANG_INC_COEF = 60 / 360 * 65536 * 50us * 60MHz /256分频
//#define ANG_INC_COEF   149333  //ANG_INC_COEF = 60 / 360 * 65536 * 50us * 70MHz /256分频
/*
 * hall结构体类型定义
 */
typedef struct {
    unsigned int Hall_Value_Buf[3];
    unsigned int Hall_Value_Old;
    unsigned int Hall_Value_Cur;
    unsigned int Hall_Update;
    unsigned int Hall_Update_Count;
    unsigned int Cnt_Time;
    unsigned int Cnt_Time_Last;
    unsigned int Cnt_Time_Buf[6];
    unsigned int Cnt_Time_Num;
    unsigned int Cnt_Time_Enable;
    unsigned int Eangle_Rotor;
} tHall_Type;

extern tHall_Type ROTOR_RAM tHall;
extern void ROTOR_SECTION GetRotorInfo(void);
extern void ROTOR_SECTION HallInitialize(void);
#endif	/* ROTOR_H */


