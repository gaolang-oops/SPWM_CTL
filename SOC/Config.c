/*============================================================================
文件描述：MCU配置文件
使用MCU：dsPIC33EP128MC506
文件名：Config.c
文件功能：设置MCU配置位 HS+PLL  时钟具体分频方式在启动文件内配置
作者：高朗
============================================================================*/

/*============================================================================*/
//配置位配置
/*============================================================================*/
// FGS
//仿真调试时：通用段不进行代码保护和写保护
#pragma config GWRP = OFF            
#pragma config GCP = OFF   
//量产后：通用段进行代码保护和写保护
//#pragma config GWRP = ON                // General Segment Write-Protect bit (General Segment is write protected)
//#pragma config GCP = ON                 // General Segment Code-Protect bit (General Segment Code protection Enabled)

// FOSCSEL
//选择带PLL模块的主振荡器，PWM锁定，双速振荡器不使能
#pragma config FNOSC = PRIPLL           // Primary Oscillator with PLL module (XT + PLL, HS + PLL, EC + PLL)
#pragma config PWMLOCK = ON             // Certain PWM registers may only be written after key sequence
#pragma config IESO = OFF               // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)

// FOSC
//选择的是HS晶振模式
#pragma config POSCMD = HS               // HS Crystal Oscillator Mode
//OSC2 引脚功能位 （XT 和 HS 模式除外，不具备功能）这里使用的是外部无源晶振，OSC2引脚要作为晶振振荡器信号输入     
#pragma config OSCIOFNC = OFF            // OSC2 is clock output
//外设选择寄存器允许多次配置       
#pragma config IOL1WAY = OFF            // Peripheral pin select configuration (Allow multiple reconfigurations)
//时钟切换和时钟监视被禁止
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)

// FWDT 关闭看门狗
//看门狗后分频为32768分频
#pragma config WDTPOST = PS32768          // Watchdog Timer Postscaler bits (1:32768)
//看门狗定时器分频为128分频
#pragma config WDTPRE = PR128            // Watchdog Timer Prescaler bit (1:128)
//设置PLL锁定使能。没有时钟切换的话，这个锁定配置了也无效。这里配置起来，方便以后用时钟切换。
#pragma config PLLKEN = ON              // PLL Lock Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
//看门狗定时器的窗口模式失能
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
//看门狗定时器禁止
#pragma config FWDTEN = OFF              // Watchdog Timer Enable bit (Watchdog timer always disabled)

// FPOR
//I2C引脚映射到SDA1/SCL1 SDA2/SCL2
#pragma config ALTI2C1 = OFF            // Alternate I2C1 pins (I2C1 mapped to SDA1/SCL1 pins)
#pragma config ALTI2C2 = OFF            // Alternate I2C2 pins (I2C2 mapped to SDA2/SCL2 pins)
//看门狗窗口为看门狗定时器周期的25%，因为我们没有使用看门狗。这里虽然选择了25%，但是看门狗禁止了，这里配置也是无效的。
#pragma config WDTWIN = WIN25           // Watchdog Window Select bits (WDT Window is 25% of WDT period)

// FICD
//通过PGEC2和PGED2进行通讯
#pragma config ICS = PGD2               // ICD Communication Channel Select bits (Communicate on PGEC2 and PGED2)
//JTAG失能
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

/*======================================================*/
