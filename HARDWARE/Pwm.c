#include "Pwm.h"

/*
 * PWM模块初始化
 * 一个模块两个PWM引脚
 * IOCON1寄存器控制PWM1H跟PWM1L引脚??U
 * IOCON3寄存器控制PWM3H跟PWM3L引脚??W
 */
void INIT_SECTION McuPwmInitialize(void) {
    PTCONbits.PTEN = 0; //禁止PWM模块
    PTCON = PTCON_INIT;
    PTCON2 = PTCON2_INIT;

    // PWM发生器1的寄存器初始化
    PWMCON1 = PWMCON1_INIT;
    __builtin_write_PWMSFR(&IOCON1, IOCON1_INIT, &PWMKEY);
    __builtin_write_PWMSFR(&FCLCON1, FCLCON1_INIT, &PWMKEY);
    PHASE1 = PHASE1_INIT;
    PDC1 = PDC1_INIT;
    DTR1 = DTR1_INIT;
    ALTDTR1 = ALTDTR1_INIT;
    TRGCON1 = TRGCON1_INIT;
    TRIG1 = TRIG1_INIT;

    // PWM发生器2的寄存器初始化
    PWMCON2 = PWMCON2_INIT;
    __builtin_write_PWMSFR(&IOCON2, IOCON2_INIT, &PWMKEY);
    __builtin_write_PWMSFR(&FCLCON2, FCLCON2_INIT, &PWMKEY);
    PHASE2 = PHASE2_INIT;
    PDC2 = PDC2_INIT;
    DTR2 = DTR2_INIT;
    ALTDTR2 = ALTDTR2_INIT;

    // PWM发生器3的寄存器初始化
    PWMCON3 = PWMCON3_INIT;
    __builtin_write_PWMSFR(&IOCON3, IOCON3_INIT, &PWMKEY);
    __builtin_write_PWMSFR(&FCLCON3, FCLCON3_INIT, &PWMKEY);
    PHASE3 = PHASE3_INIT;
    PDC3 = PDC3_INIT;
    DTR3 = DTR3_INIT;
    ALTDTR3 = ALTDTR3_INIT;
    PTCONbits.PTEN = 1; //使能PWM模块
}

/*占空比输入：PwmDuty% [0,100] */
void PWM_SECTION PwmDutySet(unsigned int PwmDuty1, unsigned int PwmDuty2, unsigned int PwmDuty3) {
    PwmDuty1 = Limit_Val(PwmDuty1, 10, 90);
    PwmDuty2 = Limit_Val(PwmDuty2, 10, 90);
    PwmDuty3 = Limit_Val(PwmDuty3, 10, 90);
    PDC1 = PWM_PERIOD_VALUE / 100 * PwmDuty1; //PWM_PERIOD_VALUE值等于一个周期时基计数次数
    PDC2 = PWM_PERIOD_VALUE / 100 * PwmDuty2;
    PDC3 = PWM_PERIOD_VALUE / 100 * PwmDuty3;
    
}