/* 
 * File:   Sfr_Init.h
 * Author: GaoLa
 *
 * Created on 2022年6月26日, 下午6:31
 */
/*==================================================
文件描述：特殊功能寄存器头文件
使用MCU：dsPIC33EP128MC506
文件功能：放置特殊功能寄存器初始值
==================================================*/

#ifndef SFR_INIT_H
#define	SFR_INIT_H

//寄存器初始值宏定义
/*---------------PORTA----------------------*/
//F:    RA0-IA(AN0)(I)  RA1-IB(AN1)(I)  RA2(-)      RA3(-)
//E:    RA4-SDO(O)      RA5(-)          RA6(-)      RA7-NC(I) 
//D:    RA8-RX(I)       RA9-CS1(O)      RA10--NC(I) RA11-NC(I) 
//F:    RA12-NC(I)      RA13-15(-)
#define TRISA_INIT      0xFDEF   //TRISx 寄存器控制位决定与I/O 端口相关的各个引脚是输入引脚还是输出引脚。
//如果某个I/O 引脚的TRIS 位为1，则该引脚是输入引脚。如果某个I/O 引脚的TRIS 位为0，则该引脚被配置为输出引脚。
//这很好记，因为1 很像I （Input，输入）， 0 很像O （Output，输出）。复位后，所有端口引脚均定义为输入。
#define PORTA_INIT      0x0000   //通过PORTx寄存器访问I/O引脚上的数据。读PORTx寄存器是读取I/O引脚上的值，
//而写PORTx寄存器是将值写入端口数据锁存器。读- 修改- 写指令时（既输出功能）不用这个寄存器，使用LAIx
#define LATA_INIT      0x0000 //与I/O 引脚相关的LATx 寄存器消除了可能在执行读- 修改- 写指令时发生的问题。
//读LATx 寄存器将返回保存在端口输出锁存器中的值，而不是I/O 引脚上的值。
//对与某个I/O 端口相关的LAT寄存器进行读- 修改- 写操作，避免了将输入引脚值写入端口锁存器的可能性。
//写LATx 寄存器与写PORTx 寄存器的效果相同。
#define ODCA_INIT      0x0000 //不使用开漏输出，配置为零
#define CNENA_INIT      0x0000 //CNENx：输入电平变化通知中断允许寄存器。比如把相应位配置成1，
//那如果相应的引脚上电平发生变化，它就可以产生中断。
#define CNPUA_INIT      0x0000 //CNPUx：输入电平变化通知上拉使能寄存器
#define CNPDA_INIT      0x0000 // CNPDx：输入电平变化通知下拉使能寄存器
#define ANSELA_INIT      0x0003 // ANSELx：模拟选择控制寄存器，如果不想使用模拟功能，需要把引脚作为数字IO脚，
//就把相应的位配置成0就可以了。注意，如果端口是带模拟通道的话，上电复位的时候，它里面的这些位都是被配置为1的。

/*---------------PORTB----------------------*/
//F:    RB0-Ic(AN2)(I)          RB1-Voltage(AN3)(I)     RB2-ACCELE(AN4)(I)      RB3-NC(I)
//6:    RB4-TX(O)               RB5-PGD(I)              RB6-PGC(I)              RB7-CAN_TX(O) 
//3:    RB8-CVREFIO(模拟)(I)    RB9-NC(I)               RB10-PWM3H(O)           RB11-PWM3L(O)
//0:    RB12-PWM2H(O)           RB13-PWM2L(O)           RB14-PWM1H(O)           RB15-PWM1L(O)
#define TRISB_INIT      0x036F
#define PORTB_INIT      0x0000
#define LATB_INIT       0x0000
#define ODCB_INIT       0x0000
#define CNENB_INIT      0x0000
#define CNPUB_INIT      0x0000
#define CNPDB_INIT      0x0000
#define ANSELB_INIT     0x0107

/*---------------PORTC----------------------*/
//7:    RC0-IBUS(AN6)(I)    RC1-KEY1(I)     RC2-KEY2(I)         RC3-SPI1_SCK(O)
//3:    RC4-FLT 保护(I)     RC5-NC(I)       RC6-SPI2_SDO(O)     RC7-SPI2_CS扩展接口(O) 
//C:    RC8-SPI2_SCK(O)     RC9-OC1(O)      RC10-CAN_RX(I)      RC11-KEY3(I)
//7:    RC12-OSC1(I)        RC13-NC(I)      RC14(-)             RC15-OSC2(O)
#define TRISC_INIT      0x7C37   //TRISx 寄存器控制位决定与I/O 端口相关的各个引脚是输入引脚还是输出引脚。
//如果某个I/O 引脚的TRIS 位为1，则该引脚是输入引脚。如果某个I/O 引脚的TRIS 位为0，则该引脚被配置为输出引脚。
//这很好记，因为1 很像I （Input，输入）， 0 很像O （Output，输出）。复位后，所有端口引脚均定义为输入。
#define PORTC_INIT      0x0000   //通过PORTx寄存器访问I/O引脚上的数据。读PORTx寄存器是读取I/O引脚上的值，
//而写PORTx寄存器是将值写入端口数据锁存器。读- 修改- 写指令时（既输出功能）不用这个寄存器，使用LAIx
#define LATC_INIT       0x0000 //与I/O 引脚相关的LATx 寄存器消除了可能在执行读- 修改- 写指令时发生的问题。
//读LATx 寄存器将返回保存在端口输出锁存器中的值，而不是I/O 引脚上的值。
//对与某个I/O 端口相关的LAT寄存器进行读- 修改- 写操作，避免了将输入引脚值写入端口锁存器的可能性。
//写LATx 寄存器与写PORTx 寄存器的效果相同。
#define ODCC_INIT       0x0000 //不使用开漏输出，配置为零
#define CNENC_INIT      0x0000 //CNENx：输入电平变化通知中断允许寄存器。比如把相应位配置成1，
//那如果相应的引脚上电平发生变化，它就可以产生中断。
#define CNPUC_INIT      0x0000 //CNPUx：输入电平变化通知上拉使能寄存器
#define CNPDC_INIT      0x0000 // CNPDx：输入电平变化通知下拉使能寄存器
#define ANSELC_INIT     0x0001 // ANSELx：模拟选择控制寄存器，如果不想使用模拟功能，需要把引脚作为数字IO脚，
//就把相应的位配置成0就可以了。注意，如果端口是带模拟通道的话，上电复位的时候，它里面的这些位都是被配置为1的。

/*---------------PORTD----------------------*/
//F:    RD0-3(-)(I)
//F:    RD4(-)(I)       RD5-NC(I)     RD6-NC(I)     RD7(-)(I)
//E:    RD8-CS2(O)      RD9-11(-)(I)
//F:    RD12-15(-)(I)        
#define TRISD_INIT      0xFEFF
#define PORTD_INIT      0x0000
#define LATD_INIT      0x0000
#define ODCD_INIT      0x0000
#define CNEND_INIT      0x0000
#define CNPUD_INIT      0x0000
#define CNPDD_INIT      0x0000

/*---------------PORTE----------------------*/
//F:    RE0-3(-)
//F:    RE4-7(-)
//F:    RE8-11(-) 
//0:    RE12-LED0(O)    RE13-LED1(O)    RE14-LED2(O)    RE15-LED3(O) 因为LED为共阴极接法，配置为1则不亮
#define TRISE_INIT      0x0FFF
#define PORTE_INIT      0xF000
#define LATE_INIT       0xF000
#define ODCE_INIT       0x0000
#define CNENE_INIT      0x0000
#define CNPUE_INIT      0x0000
#define CNPDE_INIT      0x0000
#define ANSELE_INIT     0x0000

/*---------------PORTG----------------------*/
//F:    RG0-3(-)
//F:    RG4-5(-)        RG6-HALL_W(I)       RG7-HALL_V(I) 
//F:    RG8-HALL_U(I)   RG9-NC(I)           RG10-RG11(-)
//F:    RG12-15(-)       
#define TRISG_INIT      0xFFFF
#define PORTG_INIT      0x0000
#define LATG_INIT       0x0000
#define ODCG_INIT       0x0000
#define CNENG_INIT      0x0000
#define CNPUG_INIT      0x0000
#define CNPDG_INIT      0x0000


/*--------------外设引脚选择配置寄存器初始值宏定义--------------------*/
//输入寄存器
//（请参见表11-2 了解输入引脚选择编号）
//HALL_U RP120      HALL_V RP119-IC1   HALL_W RP118
#define RPINR0_INIT      0x0000 //未使用 bit 14-8 INT1R<6:0>：将外部中断1 （INT1）分配给对应RPn 引脚的位。
#define RPINR1_INIT      0x0000 //未使用 bit 6-0 INT2R<6:0>：将外部中断2 （INT2）分配给对应RPn 引脚的位
#define RPINR3_INIT      0x0000 //未使用 bit 6-0 T2CKR<6:0>：将Timer2 外部时钟（T2CK）分配给对应RPn 引脚的位
#define RPINR7_INIT      0x7778 //使用   bit 14-8 IC2R<6 :0>：将输入捕捉2 （IC2）分配给对应RPI119引脚的位 111 0111
//bit 6-0 IC1R<6:0>：将输入捕捉1 （IC1）分配给对应RP120引脚的位 111 1000
#define RPINR8_INIT      0x0076 //使用   bit 14-8 IC4R<6:0>：将输入捕捉4 （IC4）分配给对应RPn 引脚的位
//bit 6-0 IC3R<6:0>：将输入捕捉3 （IC3）分配给对应RP118引脚的位 111 0110
#define RPINR11_INIT     0x0000 //未使用 bit 6-0 OCFAR<6:0>：将输出比较故障A （OCFA）分配给对应RPn 引脚的位
#define RPINR12_INIT     0x0000 //未使用 bit 14-8 FLT2R<6:0>：将PWM 故障2 （FLT2）分配给对应RPn 引脚的位

#define RPINR14_INIT     0x0000 //未使用 bit 14-8 QEB1R<6:0>：将B 相输入（QEB）分配给对应RPn 引脚的位

#define RPINR15_INIT     0x0000 //未使用 bit 14-8 HOME1R<6:0>：将QEI1 HOME1 （HOME1）分配给对应RPn 引脚的位

#define RPINR18_INIT     0x0000 //未使用 bit 6-0 U1RXR<6:0>：将UART1 接收（U1RX）分配给对应RPn 引脚的位
#define RPINR19_INIT     0x0018 //使用   bit 6-0 U2RXR<6:0>：将UART2 接收（U2RX）分配给对应RPI24 引脚的位 001 1000
#define RPINR22_INIT     0x0000 //未使用 bit 14-8 SCK2INR<6:0>: 将SPI2 时钟输入（SCK2）分配给对应RPn 引脚的位

#define RPINR23_INIT     0x0000 //未使用 bit 6-0 SS2R<6:0>: 将SPI2 从选择（SS2）分配给对应RPn 引脚的位
#define RPINR26_INIT     0x0000 //未使用 bit 6-0 C1RXR<6:0>：将CAN1 接收输入（CRX1）分配给对应RPn 引脚的位
#define RPINR37_INIT     0x0000 //未使用 bit 14-8 SYNCI1R<6:0>：将PWM 同步输入1 分配给对应RPn 引脚的位
#define RPINR38_INIT     0x0000 //未使用 bit 14-8 DTCMP1R<6:0>：将PWM 死区补偿输入1 分配给对应RPn 引脚的位
#define RPINR39_INIT     0x0000 //未使用 bit 14-8 DTCMP3R<6:0>：将PWM 死区补偿输入3 分配给对应RPn 引脚的位
//bit 6-0 DTCMP2R<6:0>：将PWM 死区补偿输入2 分配给对应RPn 引脚的位

//输出寄存器
#define RPOR0_INIT       0x0000 //未使用 bit 13-8 RP35R<5:0>：将外设输出功能分配给RP35 输出引脚的位

#define RPOR1_INIT       0x0003 //使用 bit 13-8 RP37R<5:0>：将外设输出功能分配给RP37 输出引脚的位
//bit 5-0 RP36R<5:0>：将外设输出功能U2TX分配给RP36 输出引脚的位 
#define RPOR2_INIT       0x0000 //未使用 bit 13-8 RP39R<5:0>：将外设输出功能分配给RP39 输出引脚的位

#define RPOR3_INIT       0x0000 //未使用 bit 13-8 RP41R<5:0>：将外设输出功能分配给RP41 输出引脚的位

#define RPOR4_INIT       0x0000 //未使用 bit 13-8 RP43R<5:0>：将外设输出功能分配给RP43 输出引脚的位

#define RPOR5_INIT       0x0000 //未使用 bit 13-8 RP55R<5:0>：将外设输出功能分配给RP55 输出引脚的位

#define RPOR6_INIT       0x0000 //未使用 bit 13-8 RP57R<5:0>：将外设输出功能分配给RP57 输出引脚的位

#define RPOR7_INIT       0x0000 //未使用 bit 13-8 RP97R<5:0>：将外设输出功能分配给RP97 输出引脚的位

#define RPOR8_INIT       0x0000 //未使用 bit 13-8 RP118R<5:0>：将外设输出功能分配给RP118 输出引脚的位

#define RPOR9_INIT       0x0000 //未使用 bit 5-0 RP120R<5:0>：将外设输出功能分配给RP120 输出引脚的位


#endif	/* SFR_INIT_H */
