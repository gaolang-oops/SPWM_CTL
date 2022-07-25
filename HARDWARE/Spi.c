/*************************************************************************
;MCU:       dsPIC33EP128MC506
;Date:      2020.03.25
;File:      Spi.c
;Function:  SpiC文件
 ***************************************************************************/
#include "Spi.h"
#include "Adc.h"
#include "../SYSTEM/Math.h"
/*--------------------------------------------------------------*/
//SPI结构体定义
tSpi_Type SPI_RAM tSpi;

/*-------------------------SPI初始化------------------------*/
void INIT_SECTION McuSpi1Initialize(void) {
    SPI1STATbits.SPIEN = 0; //禁止SPI1模块(SPI1STAT<15>=0）
    SPI1STAT = SPI1STAT_INIT;
    SPI1CON1 = SPI1CON1_INIT;
    SPI1CON2 = SPI1CON2_INIT;
    SPI1STATbits.SPIEN = 1;
}

/*------------------------------------------------------------------------*/
//Spi设备初始化

void INIT_SECTION Spi_Data_Initialize(void) {
    SPI1BUF = 0x3000;
    //判断Index是否大于3，如果大于3则把Index清0.数组中有4个数据，Index大于3，
    //就说明数组中的最后一个数据已经发送了，下一次再发送的话，就循环到数组的第一个数据了。
    tSpi.Index &= 0x0003;
}
/*
 * Spi数据更新
 * AN0-Ia       AN1-Ib          AN2-Ic
 * AN3-Vbus     AN4-旋钮电压    AN6-Ibus
 */
//static void SPI_SECTION ADC_Data_Update(void) {
//    //        tSpi.DataOut1A = tAdc.An0.ValueInstant << 2;//ADC配置为10位模式，所以这里送到DAC通道，需要左移两位变为12位结果
//    //        tSpi.DataOut1B = tAdc.An1.ValueInstant << 2;//ADC配置为10位模式，所以这里送到DAC通道，需要左移两位变为12位结果
//    //        tSpi.DataOut2A = tAdc.An2.ValueInstant << 2;//ADC配置为10位模式，所以这里送到DAC通道，需要左移两位变为12位结果
//    //        tSpi.DataOut2B = tAdc.An3.ValueInstant << 2;//ADC配置为10位模式，所以这里送到DAC通道，需要左移两位变为12位结果
//    tSpi.DataOut1A = tAdc.An4.ValueInstant << 2; //ADC配置为10位模式，所以这里送到DAC通道，需要左移两位变为12位结果
//    tSpi.DataOut1B = tAdc.An6.ValueInstant << 2; //ADC配置为10位模式，所以这里送到DAC通道，需要左移两位变为12位结果
//    tSpi.DataOut2A = tAdc.An2.ValueInstant << 2; //ADC配置为10位模式，所以这里送到DAC通道，需要左移两位变为12位结果
//    tSpi.DataOut2B = tAdc.An3.ValueInstant << 2; //ADC配置为10位模式，所以这里送到DAC通道，需要左移两位变为12位结果
//
//    tSpi.ReadyData[0] = tSpi.DataOut1A;
//    tSpi.ReadyData[1] = tSpi.DataOut1B;
//    tSpi.ReadyData[2] = tSpi.DataOut2A;
//    tSpi.ReadyData[3] = tSpi.DataOut2B;
//}

/*
 * 测试正弦表里面的数据
 * 在adc中断里每50us通过spi将正弦表里面的数据发送到DAC芯片
 * DAC芯片将数字正弦波转换为模拟正弦波，可以通过示波器查看
 * 此函数功能是准备需要发送的正弦波数据
 */
//static void SPI_SECTION SinCos_Update(void) {
//    tSpi.DataOut1A = (unsigned int) (tCal.sSinValue + 0x8000); //tCal.sSinValue=-32768~32767 + 0x8000 = 0~65535
//    tSpi.DataOut1B = (unsigned int) (tCal.sCosValue + 0x8000);
//    tSpi.DataOut2A = (unsigned int) (tCal.sSinValue + 0x8000);
//    tSpi.DataOut2B = (unsigned int) (tCal.sCosValue + 0x8000);
//
//    tSpi.ReadyData[0] = tSpi.DataOut1A >> 4; //16位正弦表数据缩小到12位（DAC芯片最大支持12位数据）
//    tSpi.ReadyData[1] = tSpi.DataOut1B >> 4;
//    tSpi.ReadyData[2] = tSpi.DataOut2A >> 4;
//    tSpi.ReadyData[3] = tSpi.DataOut2B >> 4;
//}


/*
 * 测试三相正弦
 * 在adc中断里每50us通过spi将数据发送到DAC芯片
 * DAC芯片将数字正弦波转换为模拟正弦波，可以通过示波器查看
 * 此函数功能是准备需要发送的正弦波数据
 */
static void SPI_SECTION ThreeSins_Update(void) {
    tSpi.DataOut1A = (unsigned int) (tUm.Ua + 0x8000); //tUm.Ua=-32768~32767 + 0x8000 = 0~65535
    tSpi.DataOut1B = (unsigned int) (tUm.Ub + 0x8000);
    tSpi.DataOut2A = (unsigned int) (tUm.Uc + 0x8000);
    tSpi.DataOut2B = (unsigned int) (tUm.Ua + 0x8000); 

    tSpi.ReadyData[0] = tSpi.DataOut1A >> 4; //16位数据缩小到12位（DAC芯片最大支持12位数据）
    tSpi.ReadyData[1] = tSpi.DataOut1B >> 4;
    tSpi.ReadyData[2] = tSpi.DataOut2A >> 4;
    tSpi.ReadyData[3] = tSpi.DataOut2B >> 4;
}
/*------------------------------------------------------------------------*/
//SPI数据发送

void SPI_SECTION SpiTransmit(void) {
    unsigned int Temp;
    if (!SPI1STATbits.SPITBF) {
        ThreeSins_Update();
        Temp = tSpi.ReadyData[tSpi.Index];
        Temp &= 0x0fff;
        Temp |= 0x3000;
        switch (tSpi.Index) {
            case 0: //OUT1A
                SPI1_CS2 = 1;
                SPI1_CS1 = 0;
                DELAY100NS();
                break;
            case 1: //OUT1B
                SPI1_CS1 = 1;
                DELAY100NS();
                SPI1_CS1 = 0;
                //bit15变为1，就是实现数据传输到B通道。
                //它的另一个功能，是实现延时等待。也就是代替之前的100ns的等待。
                Temp |= 0x8000;
                break;
            case 2: //OUT2A
                SPI1_CS1 = 1;
                SPI1_CS2 = 0;
                DELAY100NS();
                break;
            case 3: //OUT2B
                SPI1_CS2 = 1;
                DELAY100NS();
                SPI1_CS2 = 0;
                Temp |= 0x8000;
                break;
        }
        SPI1BUF = Temp;
        tSpi.Index++;
        //判断Index是否大于3，如果大于3则把Index清0.数组中有4个数据，Index大于3，
        //就说明数组中的最后一个数据已经发送了，下一次再发送的话，就循环到数组的第一个数据了。
        tSpi.Index &= 0x0003;
    }
}
/*------------------------------------------------------------------------*/
