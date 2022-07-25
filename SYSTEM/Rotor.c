/*============================================================================*/
//工程描述：方波六步换相控制
//使用MCU：dsPIC33EP128MC506
//文件名：Rotor.c
//文件功能：转子位置获取
//日期：2022年3月25日
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
 * 正反转电角度表
 */
const unsigned int Rotor_Angle_Table_CCW[7] = {0, EANGLE150, EANGLE30, EANGLE90, EANGLE270, EANGLE210, EANGLE330};
const unsigned int Rotor_Angle_Table_CW[7] = {0, EANGLE210, EANGLE90, EANGLE150, EANGLE330, EANGLE270, EANGLE30};
const unsigned int Rotor_Angle_Init_Table[7] = {0, EANGLE180, EANGLE60, EANGLE120, EANGLE300, EANGLE240, EANGLE0};

/*
 * 函数功能：读取霍尔端口值
 * 函数输入：无
 * 函数输出：无
 * ！！！！注意：如果Buf0一直不等于Word的值，程序会进死循环，ADC中断优先级低于IC中断，无法打断这个死循环，
 * ！！！！导致无法运行状态机！！危险。所以需要j
 * ！！！！j=5,则12.8us内会连续读取5*3=18次hall，如果无法采出hall值，会置错误标志，然后break
 */
static void ROTOR_SECTION GetHallValue(void) {
    unsigned char i;
    unsigned char j = 5;
    UNION_WORD Temp;
    do {
        i = 0;
        do {
            Temp.Word = 0; //读取之前清零
            Temp.Bits.B2 = HALLU_Bit;
            Temp.Bits.B1 = HALLV_Bit;
            Temp.Bits.B0 = HALLW_Bit;
            tHall.Hall_Value_Buf[i++] = Temp.Word;
        } while (i < 3);
        if (!(--j)) {
            Error_Flag.Bits.Hall = 1; //hall干扰过大或者损坏
            break;
        }
    } while (tHall.Hall_Value_Buf[0] != Temp.Word);

    tHall.Hall_Value_Cur = Temp.Word;
    if (tHall.Hall_Value_Cur != tHall.Hall_Value_Old) {
        tHall.Hall_Value_Old = tHall.Hall_Value_Cur;
        if ((tHall.Hall_Value_Cur > 0) && (tHall.Hall_Value_Cur < 7)) {
            tHall.Hall_Update = 1; //hall数据正确.更新标志置1
        } else {//电机旋转时hall数据异常（0或7），记录在Error_Flag.Bits.Hall
            Error_Flag.Bits.Hall = 2;
        }
    }
    //霍尔信号长时间不更新，则要报故障
}

/*
 * 霍尔初始化的函数。用于确定初始启动时的转子位置角。
 * 在没有霍尔沿跳变之前，都会按照这个角度去求解θ。
 * ！！！此函数在状态机为初始化状态KERNEL_STATE_INIT时调用。
 * 执行后，预估了一个启动时的转子位置角保存在Rotor_Angle.Words.High
 * ！！！此时电机静止，不能认为hall数据更新了。这里只是初始值。将tHall.Hall_Update置零
 * ！！！这个很重要，如果不置零，在调用GetHallValue();后，tHall.Hall_Update为1。
 * ！！！当状态机进入KERNEL_STATE_RUN后，调用GetRotorAngle函数，
 * ！！！发现tHall.Hall_Update为1（代表hall有值更新），则计算当前转子位置角保存在Rotor_Angle.Words.High
 * ！！！这样就会覆盖启动时预估的转子位置角
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
    //！！状态机为初始化状态KERNEL_STATE_INIT。此时电机静止，不能认为hall数据更新了。这里只是初始值
    tHall.Hall_Update = 0;
}

/*
 * 根据读取到的霍尔值，找到对应的转子位置角。保存到Rotor_Angle.Words.High
 * 转子位置角，归一化之后，使用无符号的Q15表示就是0~65535.这样只需要一个16位的变量来存放即可。
 * 这里Rotor_Angle为什么使用了一个32位的变量呢？其实这里是为了后面跟角度增量累加的时候，让角度精度更高一些准备的。
 */
static void Get_Hall_Edge_Angle(void) {
    unsigned int Temp;
    unsigned int *p;
    //转子往不同的方向转动的时候，读到的霍尔值对应的转子位置是不同的。
    if (Motor_Flag.Bits.Direction) {
        Temp = DSRPAG;
        DSRPAG = __builtin_psvpage(Rotor_Angle_Table_CCW);
        p = (unsigned int *) __builtin_psvoffset(Rotor_Angle_Table_CCW);
        //获取到Hall_Value对应的角度值。也就是沿跳变的时候，对应的角度值
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
    //角度增量清零
    Rotor_Angle.Words.Low = 0;
}

/*
 * 获取转子转动60度电角度需要的平均时间。保存到tHall.Cnt_Time
 * ！！！！！！！！！！！！！！！！！！！！！！！！ 
 * 特别注意：电机停止时，进入启动状态，此时hall没有沿跳变，则IC1IF，IC2IF,IC3IF都是零
 * 故tHall.Cnt_Time等于零，Tmp等于零
 * 如果此时tHall.Cnt_Time作为了内建除法的除数，就会导致mcu复位
 */
static int Get_Angle60_Time(void) {
    /*1 获取hall沿之间消耗的时间*/
    unsigned int Tmp = 0;
    UNION_U32 Temp32;
    if (IFS0bits.IC1IF) {
        Tmp = IC2BUF; //这里的读取是无效的，就是为了把BUF清掉，始终保持在缓冲区的顶端
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
    //第一次的值，如果现在只发生了一次捕捉，那么Hall_Time_Last是0。
    //此时，对应的求解出来的Temp也不是正确的60度的时间。所以，第一次我们需要特殊处理
    if (tHall.Cnt_Time >= tHall.Cnt_Time_Last)
        Tmp = tHall.Cnt_Time - tHall.Cnt_Time_Last;
    else
        Tmp = 65536 - tHall.Cnt_Time_Last + tHall.Cnt_Time;
    tHall.Cnt_Time_Last = tHall.Cnt_Time;

    /*2 获取到了hall沿之间消耗的时间tmp， 放入buf数组为求平均做准备*/
    if (Tmp != 0) { //Tmp如果不为0，就意味着已经有捕捉事件发生了
        tHall.Cnt_Time_Buf[tHall.Cnt_Time_Num] = Tmp;
        if (tHall.Cnt_Time_Num < 6)
            tHall.Cnt_Time_Num++;
        if (tHall.Cnt_Time_Num >= 6) {
            //把Hall_Time_Num 清0，为下一个电周期做准备。
            tHall.Cnt_Time_Num = 0;
            //Hall_Time_Enable这个变量为1，说明已经存储了6个数据了，则我们可以求取平均值了。
            tHall.Cnt_Time_Enable = 1;
        }
        //将60度电角度的正确时间保存到tHall.Cnt_Time
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
        if (tHall.Cnt_Time <= 342) // MAX:4000RPM 如果时间比最高速60度的时间还要短，则当前转子超速了
            tHall.Cnt_Time = 342;
        return 1; //已经有捕捉事件发生了
    } else {
        return 0; //电机停止时，进入启动状态，此时Tmp为零，tHall.Cnt_Time为零
    }
}

/* 
 * 每个PWM周期去得到对应的转子位置角度
 * 根据我们读取到的霍尔值，可以找到对应的转子位置角。
 * Hall_Update为1，说明发生了霍尔沿跳变。那么霍尔沿跳变发生后，就可以确定出该跳变沿的角度。
 * Hall_Update_Count变量，是后续为了做保护用的，也就是霍尔信号长时间不更新，则会在这里Hall_Update_Count++
 * 如果霍尔信号正常更新，那么Hall_Update_Count变量就会清0.如果Hall_Update=0一直不更新，Hall_Update_Count无法清零则状态机报错
 */
static void ROTOR_SECTION GetRotorAngle(void) {
    if (tHall.Hall_Update != 0) { //如果hall值更新了
        tHall.Hall_Update = 0;
        tHall.Hall_Update_Count = 0;
        //根据我们读取到的霍尔值，可以找到对应的转子位置角。保存到Rotor_Angle.Words.High
        Get_Hall_Edge_Angle();
        //获取转子转动60度电角度需要的平均时间。保存到tHall.Cnt_Time
        if (0 != Get_Angle60_Time()) {
            //因为有hall沿跳变，60度电角度时间可以准确得到
            //因为在每个PWM周期去更新转子角度值，60度区间内的角度就是每个PWM周期递增一次。
            //也就是说，我们通过60度的时间，可以计算出每个PWM周期内的平均角度增量。
            //既是：PWM周期50us/Eangle60_Time*60度
            //！！！！！！！！如果除数tHall.Cnt_Time为零，会导致mcu复位
            Rotor_Angle_Inc.Words.High = __builtin_divmodud(ANG_INC_COEF, tHall.Cnt_Time, &Rotor_Angle_Inc.Words.Low);
        }
    } else {//如果hall值没有更新
        if (tHall.Hall_Update_Count < 65535) // 65535 x 50us = 3.276750s
        {
            tHall.Hall_Update_Count++;
            if (Motor_Flag.Bits.Direction)
                Rotor_Angle.U32 += Rotor_Angle_Inc.U32;
            else
                Rotor_Angle.U32 -= Rotor_Angle_Inc.U32;
        } else {
            if (Motor_Flag.Bits.Status)//Motor_Flag.Bits.Status表示电机正在运行
                Error_Flag.Bits.Hall = 3;
            else
                tHall.Hall_Update_Count = 0;
        }
    }
    tHall.Eangle_Rotor = Rotor_Angle.Words.High;
}

/*
 * 函数功能：获取转子信息
 * 函数输入：无
 * 函数输出：无
 */
void ROTOR_SECTION GetRotorInfo(void) {
    GetHallValue();
    GetRotorAngle();
}