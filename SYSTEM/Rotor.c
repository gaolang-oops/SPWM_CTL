/*============================================================================*/
//�������������������������
//ʹ��MCU��dsPIC33EP128MC506
//�ļ�����Rotor.c
//�ļ����ܣ�ת��λ�û�ȡ
//���ڣ�2022��3��25��
/*============================================================================*/
#include "Rotor.h"
#include "Error.h"
#include "Moto.h"
#include "../HARDWARE/Led.h"
tHall_Type ROTOR_RAM tHall;
UNION_U32 ROTORTMP_RAM Rotor_Angle;
UNION_U32 ROTORTMP_RAM Rotor_Angle_Inc;
extern void Delay(void); ////////////////////////
/*
 * ����ת��Ƕȱ�
 */
const unsigned int Rotor_Angle_Table_CCW[7] = {0, EANGLE150, EANGLE30, EANGLE90, EANGLE270, EANGLE210, EANGLE330};
const unsigned int Rotor_Angle_Table_CW[7] = {0, EANGLE210, EANGLE90, EANGLE150, EANGLE330, EANGLE270, EANGLE30};
const unsigned int Rotor_Angle_Init_Table[7] = {0, EANGLE180, EANGLE60, EANGLE120, EANGLE300, EANGLE240, EANGLE0};

/*
 * �������ܣ���ȡ�����˿�ֵ
 * �������룺��
 * �����������
 * ��������ע�⣺���Buf0һֱ������Word��ֵ����������ѭ����ADC�ж����ȼ�����IC�жϣ��޷���������ѭ����
 * �������������޷�����״̬������Σ�ա�������Ҫj
 * ��������j=5,��12.8us�ڻ�������ȡ5*3=18��hall������޷��ɳ�hallֵ�����ô����־��Ȼ��break
 */
static void ROTOR_SECTION GetHallValue(void) {
    unsigned char i;
    unsigned char j = 5;
    UNION_WORD Temp;
    do {
        i = 0;
        do {
            Temp.Word = 0; //��ȡ֮ǰ����
            Temp.Bits.B2 = HALLU_Bit;
            Temp.Bits.B1 = HALLV_Bit;
            Temp.Bits.B0 = HALLW_Bit;
            tHall.Hall_Value_Buf[i++] = Temp.Word;
        } while (i < 3);
        if (!(--j)) {
            Error_Flag.Bits.Hall = 1; //hall���Ź��������
            break;
        }
    } while (tHall.Hall_Value_Buf[0] != Temp.Word);

    tHall.Hall_Value_Cur = Temp.Word;
    if (tHall.Hall_Value_Cur != tHall.Hall_Value_Old) {
        tHall.Hall_Value_Old = tHall.Hall_Value_Cur;
        if ((tHall.Hall_Value_Cur > 0) && (tHall.Hall_Value_Cur < 7)) {
            tHall.Hall_Update = 1; //hall������ȷ.���±�־��1
        } else {//�����תʱhall�����쳣��0��7������¼��Error_Flag.Bits.Hall
            Error_Flag.Bits.Hall = 2;
        }
    }
    //�����źų�ʱ�䲻���£���Ҫ������
}

/*
 * ������ʼ���ĺ���������ȷ����ʼ����ʱ��ת��λ�ýǡ�
 * ��û�л���������֮ǰ�����ᰴ������Ƕ�ȥ���ȡ�
 * �������˺�����״̬��Ϊ��ʼ��״̬KERNEL_STATE_INITʱ���á�
 * ִ�к�Ԥ����һ������ʱ��ת��λ�ýǱ�����Rotor_Angle.Words.High
 * ��������ʱ�����ֹ��������Ϊhall���ݸ����ˡ�����ֻ�ǳ�ʼֵ����tHall.Hall_Update����
 * �������������Ҫ����������㣬�ڵ���GetHallValue();��tHall.Hall_UpdateΪ1��
 * ��������״̬������KERNEL_STATE_RUN�󣬵���GetRotorAngle������
 * ����������tHall.Hall_UpdateΪ1������hall��ֵ���£�������㵱ǰת��λ�ýǱ�����Rotor_Angle.Words.High
 * �����������ͻḲ������ʱԤ����ת��λ�ý�
 */
void ROTOR_SECTION HallInitialize(void) {
    unsigned int Temp;
    unsigned int *p;

    tHall.Cnt_Time = 0;
    tHall.Cnt_Time_Last = 0;
    tHall.Cnt_Time_Num = 0;
    tHall.Cnt_Time_Enable = 0;
    GetHallValue();
    Rotor_Angle_Inc.U32 = 0;
    Temp = DSRPAG;
    DSRPAG = __builtin_psvpage(Rotor_Angle_Init_Table);
    p = (unsigned int *) __builtin_psvoffset(Rotor_Angle_Init_Table);
    p = p + tHall.Hall_Value_Cur;
    Rotor_Angle.Words.High = (unsigned int) (*p);
    DSRPAG = Temp;
    //����״̬��Ϊ��ʼ��״̬KERNEL_STATE_INIT����ʱ�����ֹ��������Ϊhall���ݸ����ˡ�����ֻ�ǳ�ʼֵ
    tHall.Hall_Update = 0;
}

/*
 * ���ݶ�ȡ���Ļ���ֵ���ҵ���Ӧ��ת��λ�ýǡ����浽Rotor_Angle.Words.High
 * ת��λ�ýǣ���һ��֮��ʹ���޷��ŵ�Q15��ʾ����0~65535.����ֻ��Ҫһ��16λ�ı�������ż��ɡ�
 * ����Rotor_AngleΪʲôʹ����һ��32λ�ı����أ���ʵ������Ϊ�˺�����Ƕ������ۼӵ�ʱ���ýǶȾ��ȸ���һЩ׼���ġ�
 */
static void Get_Hall_Edge_Angle(void) {
    unsigned int Temp;
    unsigned int *p;
    //ת������ͬ�ķ���ת����ʱ�򣬶����Ļ���ֵ��Ӧ��ת��λ���ǲ�ͬ�ġ�
    if (Motor_Flag.Bits.Direction) {
        Temp = DSRPAG;
        DSRPAG = __builtin_psvpage(Rotor_Angle_Table_CCW);
        p = (unsigned int *) __builtin_psvoffset(Rotor_Angle_Table_CCW);
        //��ȡ��Hall_Value��Ӧ�ĽǶ�ֵ��Ҳ�����������ʱ�򣬶�Ӧ�ĽǶ�ֵ
        p = p + tHall.Hall_Value_Cur;
        Rotor_Angle.Words.High = (unsigned int) (*p);
        DSRPAG = Temp;
    } else {
        Temp = DSRPAG;
        DSRPAG = __builtin_psvpage(Rotor_Angle_Table_CW);
        p = (unsigned int *) __builtin_psvoffset(Rotor_Angle_Table_CW);
        p = p + tHall.Hall_Value_Cur;
        Rotor_Angle.Words.High = (unsigned int) (*p);
        DSRPAG = Temp;
    }
    //�Ƕ���������
    Rotor_Angle.Words.Low = 0;
}

/*
 * ��ȡת��ת��60�ȵ�Ƕ���Ҫ��ƽ��ʱ�䡣���浽tHall.Cnt_Time
 * ������������������������������������������������ 
 * �ر�ע�⣺���ֹͣʱ����������״̬����ʱhallû�������䣬��IC1IF��IC2IF,IC3IF������
 * ��tHall.Cnt_Time�����㣬Tmp������
 * �����ʱtHall.Cnt_Time��Ϊ���ڽ������ĳ������ͻᵼ��mcu��λ
 */
static int Get_Angle60_Time(void) {
    /*1 ��ȡhall��֮�����ĵ�ʱ��*/
    unsigned int Tmp = 0;
    UNION_U32 Temp32;
    if (IFS0bits.IC1IF) {
        Tmp = IC2BUF; //����Ķ�ȡ����Ч�ģ�����Ϊ�˰�BUF�����ʼ�ձ����ڻ������Ķ���
        Tmp = IC3BUF;
        IFS0bits.IC1IF = 0;
        IFS0bits.IC2IF = 0;
        IFS2bits.IC3IF = 0;
        tHall.Cnt_Time = IC1BUF;
    } else if (IFS0bits.IC2IF) {
        Tmp = IC1BUF;
        Tmp = IC3BUF;
        IFS0bits.IC1IF = 0;
        IFS0bits.IC2IF = 0;
        IFS2bits.IC3IF = 0;
        tHall.Cnt_Time = IC2BUF;
    } else if (IFS2bits.IC3IF) {
        Tmp = IC1BUF;
        Tmp = IC2BUF;
        IFS0bits.IC1IF = 0;
        IFS0bits.IC2IF = 0;
        IFS2bits.IC3IF = 0;
        tHall.Cnt_Time = IC3BUF;
    }
    //��һ�ε�ֵ���������ֻ������һ�β�׽����ôHall_Time_Last��0��
    //��ʱ����Ӧ����������TempҲ������ȷ��60�ȵ�ʱ�䡣���ԣ���һ��������Ҫ���⴦��
    if (tHall.Cnt_Time >= tHall.Cnt_Time_Last)
        Tmp = tHall.Cnt_Time - tHall.Cnt_Time_Last;
    else
        Tmp = 65536 - tHall.Cnt_Time_Last + tHall.Cnt_Time;
    tHall.Cnt_Time_Last = tHall.Cnt_Time;

    /*2 ��ȡ����hall��֮�����ĵ�ʱ��tmp�� ����buf����Ϊ��ƽ����׼��*/
    if (Tmp != 0) { //Tmp�����Ϊ0������ζ���Ѿ��в�׽�¼�������
        tHall.Cnt_Time_Buf[tHall.Cnt_Time_Num] = Tmp;
        if (tHall.Cnt_Time_Num < 6)
            tHall.Cnt_Time_Num++;
        if (tHall.Cnt_Time_Num >= 6) {
            //��Hall_Time_Num ��0��Ϊ��һ����������׼����
            tHall.Cnt_Time_Num = 0;
            //Hall_Time_Enable�������Ϊ1��˵���Ѿ��洢��6�������ˣ������ǿ�����ȡƽ��ֵ�ˡ�
            tHall.Cnt_Time_Enable = 1;
        }
        //��60�ȵ�Ƕȵ���ȷʱ�䱣�浽tHall.Cnt_Time
        if (tHall.Cnt_Time_Enable != 0) {
            Temp32.U32 = (unsigned long int) (tHall.Cnt_Time_Buf[0]);
            Temp32.U32 += (unsigned long int) (tHall.Cnt_Time_Buf[1]);
            Temp32.U32 += (unsigned long int) (tHall.Cnt_Time_Buf[2]);
            Temp32.U32 += (unsigned long int) (tHall.Cnt_Time_Buf[3]);
            Temp32.U32 += (unsigned long int) (tHall.Cnt_Time_Buf[4]);
            Temp32.U32 += (unsigned long int) (tHall.Cnt_Time_Buf[5]);
            tHall.Cnt_Time = __builtin_divud(Temp32.U32, 6);
        } else {
            if (tHall.Cnt_Time_Num == 1)
                tHall.Cnt_Time = 27397; // 50RPM -- 27397
            else
                tHall.Cnt_Time = Tmp;
        }
        if (tHall.Cnt_Time <= 342) // MAX:4000RPM ���ʱ��������60�ȵ�ʱ�仹Ҫ�̣���ǰת�ӳ�����
            tHall.Cnt_Time = 342;
        return 1; //�Ѿ��в�׽�¼�������
    } else {
        return 0; //���ֹͣʱ����������״̬����ʱTmpΪ�㣬tHall.Cnt_TimeΪ��
    }
}

/* 
 * ÿ��PWM����ȥ�õ���Ӧ��ת��λ�ýǶ�
 * �������Ƕ�ȡ���Ļ���ֵ�������ҵ���Ӧ��ת��λ�ýǡ�
 * Hall_UpdateΪ1��˵�������˻��������䡣��ô���������䷢���󣬾Ϳ���ȷ�����������صĽǶȡ�
 * Hall_Update_Count�������Ǻ���Ϊ���������õģ�Ҳ���ǻ����źų�ʱ�䲻���£����������Hall_Update_Count++
 * ��������ź��������£���ôHall_Update_Count�����ͻ���0.���Hall_Update=0һֱ�����£�Hall_Update_Count�޷�������״̬������
 */
static void ROTOR_SECTION GetRotorAngle(void) {
    if (tHall.Hall_Update != 0) { //���hallֵ������
        tHall.Hall_Update = 0;
        tHall.Hall_Update_Count = 0;
        //�������Ƕ�ȡ���Ļ���ֵ�������ҵ���Ӧ��ת��λ�ýǡ����浽Rotor_Angle.Words.High
        Get_Hall_Edge_Angle();
        //��ȡת��ת��60�ȵ�Ƕ���Ҫ��ƽ��ʱ�䡣���浽tHall.Cnt_Time
        if (0 != Get_Angle60_Time()) {
            //��Ϊ��hall�����䣬60�ȵ�Ƕ�ʱ�����׼ȷ�õ�
            //��Ϊ��ÿ��PWM����ȥ����ת�ӽǶ�ֵ��60�������ڵĽǶȾ���ÿ��PWM���ڵ���һ�Ρ�
            //Ҳ����˵������ͨ��60�ȵ�ʱ�䣬���Լ����ÿ��PWM�����ڵ�ƽ���Ƕ�������
            //���ǣ�PWM����50us/Eangle60_Time*60��
            //�����������������������tHall.Cnt_TimeΪ�㣬�ᵼ��mcu��λ
            Rotor_Angle_Inc.Words.High = __builtin_divmodud(ANG_INC_COEF, tHall.Cnt_Time, &Rotor_Angle_Inc.Words.Low);
        }
    } else {//���hallֵû�и���
        if (tHall.Hall_Update_Count < 65535) // 65535 x 50us = 3.276750s
        {
            tHall.Hall_Update_Count++;
            if (Motor_Flag.Bits.Direction)
                Rotor_Angle.U32 += Rotor_Angle_Inc.U32;
            else
                Rotor_Angle.U32 -= Rotor_Angle_Inc.U32;
        } else {
            if (Motor_Flag.Bits.Status)//Motor_Flag.Bits.Status��ʾ�����������
                Error_Flag.Bits.Hall = 3;
            else
                tHall.Hall_Update_Count = 0;
        }
    }
    tHall.Eangle_Rotor = Rotor_Angle.Words.High;
}

/*
 * �������ܣ���ȡת����Ϣ
 * �������룺��
 * �����������
 */
void ROTOR_SECTION GetRotorInfo(void) {
    GetHallValue();
    GetRotorAngle();
}