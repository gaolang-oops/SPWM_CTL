/*============================================================================*/
//ʹ��MCU��dsPIC33EP128MC506
//�ļ�����Motor.c
//�ļ����ܣ�������п���
//���ڣ�2022��3��25��
/*============================================================================*/
#include "Moto.h"
#include "Error.h"
#include "../HARDWARE/Key.h"
#include "../HARDWARE/Adc.h"
#include "../HARDWARE/Led.h"
#include "Kernel.h"

UNION_MOTORFLAGS MOTO_RAM Motor_Flag;
tMotor_Type MOTO_RAM tMotor;

/*
 * �������ܣ����ģ���ʼ��
 * �������룺�������
 * �����������
 * ���õ����ת���� 
 * ����״̬��Ϊֹ̬ͣ ȷ��ADC�ж���״̬������ѭ��
 * ���õ����־Ϊͣ ȷ�������󽫵��š��Ҳ���ᴥ������
 */
void MOTO_SECTION MotorInitialize(unsigned char direction) {
    Motor_Flag.Bits.Direction = direction;
    tKernel.State = KERNEL_STATE_STOP;
    Motor_Flag.Bits.Status = 0;
}

/*
 * �������ܣ������ͣ����
 * �������룺��
 * �����������
 */
static void MOTO_SECTION MotorRunStopControl(void) {
    if (Motor_Flag.Bits.Status == 0) {
        //���쳣����ռ�ձȣ����������� ����������������
        if ((Error_Flag.Word == 0) && (tAdc.PotValue > 0) && (tKey.FLAG.BITS.Pressed == 1)) {
        //if (tAdc.PotValue > 0) {
            Motor_Flag.Bits.Status = 1; 
            tKey.FLAG.BITS.Pressed = 0;
            KernelStartUp();

        }
    } else if ((Motor_Flag.Bits.ReqOff == 1) || (tAdc.PotValue == 0)) {
    //else if (tAdc.PotValue == 0) {
        Motor_Flag.Bits.Status = 0; //Status��Ϊ0��˵���������ֹͣ״̬
        Motor_Flag.Bits.ReqOff = 0; //���㣬Ϊ������������ͣ����׼����
        KernelStop(); //״̬����״̬�޸�Ϊֹͣ״̬
    }
}

/*
 * �������ܣ��������ģ��
 * �������룺��
 * �����������
 */
void MOTO_SECTION MotorModule(void) {
    KeyScan(); //����Ƿ���������
    MotorRunStopControl();
}







