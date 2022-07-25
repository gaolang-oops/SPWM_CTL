/* 
 * File:   Adc.h
 * Author: GaoLa
 *
 * Created on 2022年7月1日, 上午9:26
 */
#ifndef ADC_H
#define	ADC_H
#include "../USER/User.h"
/*==================================================*/
/* 1.65V模拟电压输出VREFIO - 输出寄存器初始值宏定义 */
#define CVRCON_INIT 0x00c8
/*==================================================*/

/*==================================================*/
/* ADC模块 - 寄存器初始值宏定义
 * 4通道自动同时采样及PWM1触发转换配置
 * 通道0的同相输入初始选择为AN3   
 * 采样多路开关MUXA的通道1、2和3的同相输入选择为AN0/1/2 (CH123SA = 0)
 * AN0-Ia       AN1-Ib          AN2-Ic
 * AN3-Vbus     AN4-旋钮电压    AN6-Ibus
 */
#define AD1CON1_INIT    0x001c  //选择10位4通道采样 数据输出格式为无符号整数 PWM发生器1主触发结束采样并开始转换 自动采样
#define AD1CON2_INIT    0x0200  //转换器参考电压为 VREFH AVDD VREFL AVSS 转换通道选择CH0/1/2/3 使用MUXA选择的输入通道
#define AD1CON3_INIT    0x0004  //ADC转换的时钟源选择系统时钟 自动采样时间为0TAD ADC转换时钟TAD = 5Tp = 5*16.6ns = 83.3ns
#define AD1CON4_INIT    0x0000  //不使用DMA
#define AD1CHS123_INIT  0x0000  //CH1-CH3 MUXA/B 反向输入端选择VREFL 同向输入端选择AN0/AN1/AN2
#define AD1CHS0_INIT    0x0303  //CH0 MUXA/B 反向输入端选择VREFL 同向输入端选择AN3
#define AD1CSSH_INIT    0x0000  //没有使用通道扫描
#define AD1CSSL_INIT    0x0000  //没有使用通道扫描
/*==================================================*/
//adc滤波次数  注意，tanx中ValueSum最大是65535，ADC采样结果是10位数（max 1023），那么如果求和次数大于64，ValueSum会溢出
#define    ANU_SAMPLE_NUM    64 
#define    ANP_SAMPLE_NUM    8      //adc滤波次数

/*==============================================================================
 ADC模块结构体类型定义
==============================================================================*/
typedef struct {
    unsigned int ValueInstant;
    unsigned int ValueAverage;
    unsigned int ValueSum;
    unsigned int ValueNum;
    unsigned int ValueFilter;
} tAnx_Type;

/*==================================================*/
typedef struct {
    tAnx_Type An0, An1, An2, An3, An4, An6;
    //AN0-Ia    AN1-Ib   AN2-Ic     AN3-Vbus    AN4-旋钮电压    AN6-Ibus
    unsigned int Index;
    unsigned int PotValue; //滤波后的旋钮电压值
    unsigned int BusValue; //滤波后的Vbus电压值
} tAdc_Type;

/*==================================================*/
extern tAdc_Type ADC_RAM tAdc;
extern void ADC_SECTION AdcModule(void);
extern void INIT_SECTION McuCompInitialize(void);
extern void INIT_SECTION McuAdcInitialize(void);
extern void INIT_SECTION AdcIntInitialize(unsigned int IPC);
/*==================================================*/
#endif	/* ADC_H */

