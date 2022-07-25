/* 
 * File:   Math.h
 * Author: GaoLa
 *
 * Created on 2022年7月5日, 下午2:30
 */
#ifndef MATH_H
#define	MATH_H
#include "../USER/User.h"

#define    SQRT3DIV2    56756

/*
 * 系统控制结构体类型定义
 */
typedef struct
{
    signed int sSinValue;
    signed int sCosValue;
}tCal_Type;

typedef struct
{
    unsigned int Angle;
    signed int Ua;
    signed int Ub;
    signed int Uc;
}tUm_Type;

extern tCal_Type MATH_RAM tCal;
extern tUm_Type MATH_RAM tUm;

extern void MATH_SECTION GetUabc(unsigned int Angle);
extern void MATH_SECTION SpwmOut(void);
#endif	/* MATH_H */





