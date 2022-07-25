/*==================================================
文件描述：启动文件
使用MCU：dsPIC33EP128MC506
文件名：Startup.s
文件功能：startup for c
作者：高朗
==================================================*/
    
/*=================================================*/
 ;（1）汇编头文件的引用声明，头文件中存放了一些寄存器的宏定义
    .include	"../SOC/p33EP128MC506.inc"
 ;（2）代码段定义，表示下面编辑的汇编代码是存放在.section这个段里
    .section	.start_section,code
 ;（3）汇编函数调用的全局声明。当然，这里也可以声明一些全局调用的标识符，不一定是函数
    .global	__reset
    .global	_StartProgram
 ;（4）函数标号，同样的，如果我们不编写函数，这里也可以作为含标识符的编号  
   __reset:;__reset标识符是单片机复位入口地址，是固定的，我们不能够去修改它。
    ;编写的代码在编译的时候，就是凭这个标识符，然后计算相应的地址，以此控制程序的启动运行的。
    ;如果我们使用的是官方的启动文件的话，那么它的启动库文件中，其实也是定义了这样一个复位地址标识符的。
    
    /*=========上电初始化简单的延时，大约50ms============*/
    mov	#3,w1
    clr	w0
    dec	w0,w0
    bra	NZ,$-2 ;结果非零则跳转到dec w0,w0
    dec	w1,w1
    bra	NZ,$-8
    /*=========堆栈的设置==========*/
    mov	    #__SP_init,w15  ;堆栈的开始
    mov	    #__SPLIM_init,w0
    mov	    w0,SPLIM ;堆栈限制寄存器
     
    /*=========PLL+HS 120MHZ时钟初始化==========*/
    mov	    #0x0000,w0  ; PLLPRE(N1)=0B0 0000 2分频 12MHZ(FIN)/2=6MHZ(FPLLI)  [0.8MHZ,8MHZ]
			; PLLPOST(N2)=0B00 2分频 
    mov	    w0,CLKDIV   
    mov	    #0x0026,w0  ; PLLFBD(M)=0X26=38 M=38+2=40 6MHZ(FPLLI)*40=240MHZ(FSYS)   [120MHZ,340MHZ]
			; FOSC=240MHZ(FSYS)/N2=120MHZ    [<120MHZ OR <140MHZ]
    mov	    w0,PLLFBD 
    ;得到系统时钟为120MHz
    
    /*=========PLL+HS 140MHZ时钟初始化==========*/
    ;mov	    #0x0001,w0  ; PLLPRE(N1)=0B0 0001 3分频 12MHZ(FIN)/3=4MHZ(FPLLI)  [0.8MHZ,8MHZ]
			; PLLPOST(N2)=0B00 2分频 
    ;mov	    w0,CLKDIV   
    ;mov	    #0x0044,w0  ; PLLFBD(M)=0X44=68 M=68+2=70 4MHZ(FPLLI)*70=280MHZ(FSYS)   [120MHZ,340MHZ]
			; FOSC=280MHZ(FSYS)/N2=140MHZ    [<120MHZ OR <140MHZ]
    ;mov	    w0,PLLFBD 
    ;得到系统时钟为140MHz
    
     /*========数据RAM的清零 共16KB 0x1000 TO 0x4FFF========*/
     mov	#0x1000,w0
     mov	#0x5000,w1;以字的方式清零的，在w0为#0x4ffe时清零最后一个字，清理完后w0累加，最终值是0x5000
     clr	[w0++]
     ;在每次清零，然后w0累加完成就做判断，判断是否等于0x5000，不等继续清理，相等就结束清理。
     ;异或：相同为0，不同为1.
     xor	w0,w1,w2
     bra	NZ,$-4;$代表PC目前所指的地址，因为每条指令PC指针是加2的，-4后就跳转到了clr位置处。
     /*=========跳转主程序==========*/
     goto	_StartProgram;需要对_StartProgram函数进行声明 .global  _StartProgram，才能找到StartProgram函数
    .end  
    /*=================================================*/
    
