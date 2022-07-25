/*==============================================================================
����    : SPWM���Ҳ�����������������
����    : SpwmTest
��Ƭ��  : dsPIC33EP128MC506
����    : 2021.12.02
�ļ�    : Voltage.c
����    : ���Ҳ�����
==============================================================================*/
#include "Math.h"
#include "../HARDWARE/Adc.h"

extern void CalSinCos(unsigned int);

tCal_Type MATH_RAM tCal;
tUm_Type MATH_RAM tUm;

/*
 * ����Ƕȣ�������Ӧ�Ƕȵ���������
 * ������λ���120�����Ҳ�����
 * Ua = Cos���ȣ�
 * Ub = Cos���� - 120��= -1/2 Cos�� + sqrt(3)/2 Sin��
 * Uc = Cos���� + 120��= -1/2 Cos�� - sqrt(3)/2 Sin��
 */
void MATH_SECTION GetUabc(unsigned int Angle) {
    CalSinCos(Angle);
    //tCal.sSinValueΪ�з�������SQRT3DIV2Ϊ�޷�����
    UNION_S32 Temp32;
    tUm.Ua = tCal.sCosValue;
    Temp32.S32 = __builtin_mulus(SQRT3DIV2, tCal.sSinValue);
    tUm.Ub = -(tCal.sCosValue >> 1) + Temp32.Words.High;
    tUm.Uc = -(tCal.sCosValue >> 1) - Temp32.Words.High;
}

/*
 * ������������
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
    //������Сռ�ձ�
    if (PDC1Temp < ALIGN_CENTER_DEAD_TIME)
        PDC1Temp = ALIGN_CENTER_DEAD_TIME;
    if (PDC2Temp < ALIGN_CENTER_DEAD_TIME)
        PDC2Temp = ALIGN_CENTER_DEAD_TIME;
    if (PDC3Temp < ALIGN_CENTER_DEAD_TIME)
        PDC3Temp = ALIGN_CENTER_DEAD_TIME;
    //�������ռ�ձ�
    PDCMax = PWM_PERIOD_VALUE - ALIGN_CENTER_DEAD_TIME;
    if (PDC1Temp > PDCMax)
        PDC1Temp = PDCMax;
    if (PDC2Temp > PDCMax)
        PDC2Temp = PDCMax;
    if (PDC3Temp > PDCMax)
        PDC3Temp = PDCMax;
    //����ռ�ձȸ���
    PDC1 = PDC1Temp;
    PDC2 = PDC2Temp;
    PDC3 = PDC3Temp;
}
