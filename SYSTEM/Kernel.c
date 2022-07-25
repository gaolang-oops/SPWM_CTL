#include "Kernel.h"
#include "Error.h"
#include "Moto.h"
#include "Rotor.h"
#include "../HARDWARE/Led.h"
#include "../SYSTEM/Math.h"
/*
 * ϵͳʱ������
 */
tSysTick_Type SYSTICK_RAM tSysTick;
tKernel_Type SYS_RAM tKernel;

extern void Delay(void); //�����ʱ���� λ��systemĿ¼��

/*
 * �ú�����adc�жϵ���
 * 20KHz��pwm��ÿ50us����ADCģ��ת������,��ÿ50us tSysTick.Tick50us �Լ�1
 * ����PWM_NUM_1MS��PMW����֤��1msʱ�䵽 tSysTick.TickStartup �Լ�1
 * SysTick.TickStartup �Լ�����֤��1s���ˣ�MCU��ʼ����ʱ����
 */
void SYS_SECTION Sys_CntUp_Timer(void) {
    tSysTick.Tick50us++;
    if (tSysTick.Tick50us >= PWM_NUM_1MS)//20*50us=1ms
    {
        tSysTick.Tick50us = 0;
        //1000ms Sys_CntUp_Timerָʾ����˸һ��
        if (tSysTick.Tick1ms > 1000) {
            LED2_PIN = ~LED2_PIN;
            tSysTick.Tick1ms = 0;
        }
        tSysTick.Tick1ms++;
        if (tSysTick.TickStartup != 0)
            tSysTick.TickStartup--;
        if (Led_Count != 0) {
            Led_Count--;
        }
    }
}

/*
 * �������ܣ�ϵͳ����
 * �������룺��
 * �����������
 */
void SYS_SECTION KernelStartUp(void) {
    tKernel.State = KERNEL_STATE_READY;
}

/*
 * �������ܣ�ϵͳֹͣ
 * �������룺��
 * �����������
 */
void SYS_SECTION KernelStop(void) {
    tKernel.State = KERNEL_STATE_STOP;
    CloseAllMos();
    LED0_PIN = LED_OFF;
}

/*
 * �������ܣ��ر�����MOS��
 * �������룺��
 * �����������
 * ��PWM�����ض��źŵ�mos�������ض�����Ҫһ��ʱ���
 * �������closeAllMos������������ռ�ձȵ�pwm����ͨmos�ܣ�����ܻ�û�г��׹ضϾʹ��ˣ����¶�·
 */
void SYS_SECTION CloseAllMos(void) {
    __builtin_write_PWMSFR(&IOCON1, IOCON_HL_INVALID, &PWMKEY);
    __builtin_write_PWMSFR(&IOCON2, IOCON_HL_INVALID, &PWMKEY);
    __builtin_write_PWMSFR(&IOCON3, IOCON_HL_INVALID, &PWMKEY);
}

/*
 * �������ܣ��ر������Ϲܣ��������¹ܣ������Ծٵ��ݳ��
 * �������룺��
 * �����������
 */
static void SYS_SECTION BootCharge(void) {
    __builtin_write_PWMSFR(&IOCON1, IOCON_HINVALID_LPWM, &PWMKEY);
    __builtin_write_PWMSFR(&IOCON2, IOCON_HINVALID_LPWM, &PWMKEY);
    __builtin_write_PWMSFR(&IOCON3, IOCON_HINVALID_LPWM, &PWMKEY);
}

/*
 * �������ܣ�����MOS���Ի���PWM������
 * �������룺��
 * �����������
 */
static void SYS_SECTION WorkPwmOutput(void) {
    __builtin_write_PWMSFR(&IOCON1, IOCON_HPWM_LPWM, &PWMKEY);
    __builtin_write_PWMSFR(&IOCON2, IOCON_HPWM_LPWM, &PWMKEY);
    __builtin_write_PWMSFR(&IOCON3, IOCON_HPWM_LPWM, &PWMKEY);
}

/*
 * �������ܣ�ϵͳ����״̬����
 * �������룺��
 * �����������
 * ��ADC�ж��е��ã���ADC�ж�ÿ50us����
 */
void SYS_SECTION KernelRunStateMachine(void) {
    if (tKernel.DownCounter != 0)
        tKernel.DownCounter--; //ÿ50us�ݼ�
    switch (tKernel.State) {
        case KERNEL_STATE_STOP:
            KernelStop();
            break;
        case KERNEL_STATE_READY:
            BootCharge();
            tKernel.DownCounter = 1000; //�������¼�������Ϊ1000���������1000����0����ô�ͱ�ʾ50ms��ʱ����ʱ��
            tKernel.State = KERNEL_STATE_INIT;
            break;
        case KERNEL_STATE_INIT:
            if (tKernel.DownCounter <= 0) {
                //��PWM�����ض��źŵ�mos�������ض�����Ҫһ��ʱ���
                //�������closeAllMos������������ռ�ձȵ�pwm����ͨmos�ܣ�����ܻ�û�г��׹ضϾʹ��ˣ����¶�·   
                CloseAllMos();
                //Delay(); //�����ʱ���� ȷ��mos�ܳ��׹ر�
                HallInitialize();//����ȷ����ʼ����ʱ��ת��λ�ý�
                WorkPwmOutput();//����MOS���Ի���PWM������
                LED0_PIN = LED_ON; //�������ָʾ��
                tKernel.State = KERNEL_STATE_RUN;   
            }
            break;
        case KERNEL_STATE_RUN:            
            GetRotorInfo();      
            if (Motor_Flag.Bits.Direction)
                tUm.Angle = tHall.Eangle_Rotor + EANGLE90;
            else
                tUm.Angle = tHall.Eangle_Rotor - EANGLE90;
            //��������Ƕ�ֵ������õ�������ֵ������ֵ
            //���������λ���120�ȵ����Ҳ�
            GetUabc(tUm.Angle);
            //���Ҳ��Ĳ��α任��������岨��
            SpwmOut();
            break;
        default:
            break;
    }
}