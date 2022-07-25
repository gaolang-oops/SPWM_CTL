/*==============================================================================
描述    : SPWM正弦波产生函数测试例程
工程    : SpwmTest
单片机  : dsPIC33EP128MC506
日期    : 2021.12.02
文件    : Voltage.c
功能    : 正弦波产生
==============================================================================*/
#include "Math.h"
#include "../HARDWARE/Adc.h"

extern void CalSinCos(unsigned int);

tCal_Type MATH_RAM tCal;
tUm_Type MATH_RAM tUm;

/*
 * 输入角度，产生对应角度的三相正弦
 * 三相相位相差120度正弦波产生
 * Ua = Cos（θ）
 * Ub = Cos（θ - 120）= -1/2 Cosθ + sqrt(3)/2 Sinθ
 * Uc = Cos（θ + 120）= -1/2 Cosθ - sqrt(3)/2 Sinθ
 */
void MATH_SECTION GetUabc(unsigned int Angle) {
    CalSinCos(Angle);
    //tCal.sSinValue为有符号数，SQRT3DIV2为无符号数
    UNION_S32 Temp32;
    tUm.Ua = tCal.sCosValue;
    Temp32.S32 = __builtin_mulus(SQRT3DIV2, tCal.sSinValue);
    tUm.Ub = -(tCal.sCosValue >> 1) + Temp32.Words.High;
    tUm.Uc = -(tCal.sCosValue >> 1) - Temp32.Words.High;
}

/*
 * 产生正弦脉宽波
 */
void MATH_SECTION SpwmOut(void) {
    UNION_S32 sTemp32a, sTemp32b, sTemp32c;
    unsigned int PDC1Temp;
    unsigned int PDC2Temp;
    unsigned int PDC3Temp;
    unsigned int PDCMax;
    sTemp32a.S32 = __builtin_mulus(tAdc.PotValue, tUm.Ua);
    sTemp32b.S32 = __builtin_mulus(tAdc.PotValue, tUm.Ub);
    sTemp32c.S32 = __builtin_mulus(tAdc.PotValue, tUm.Uc);
    PDC1Temp = 1750 + sTemp32a.Words.High;
    PDC2Temp = 1750 + sTemp32b.Words.High;
    PDC3Temp = 1750 + sTemp32c.Words.High;
    //限制最小占空比
    if (PDC1Temp < ALIGN_CENTER_DEAD_TIME)
        PDC1Temp = ALIGN_CENTER_DEAD_TIME;
    if (PDC2Temp < ALIGN_CENTER_DEAD_TIME)
        PDC2Temp = ALIGN_CENTER_DEAD_TIME;
    if (PDC3Temp < ALIGN_CENTER_DEAD_TIME)
        PDC3Temp = ALIGN_CENTER_DEAD_TIME;
    //限制最大占空比
    PDCMax = PWM_PERIOD_VALUE - ALIGN_CENTER_DEAD_TIME;
    if (PDC1Temp > PDCMax)
        PDC1Temp = PDCMax;
    if (PDC2Temp > PDCMax)
        PDC2Temp = PDCMax;
    if (PDC3Temp > PDCMax)
        PDC3Temp = PDCMax;
    //最终占空比给定
    PDC1 = PDC1Temp;
    PDC2 = PDC2Temp;
    PDC3 = PDC3Temp;
}
