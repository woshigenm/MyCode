#include <REGX52.H>

void UART_Init_Send(void)	//4800bps@11.0592MHz
{
	PCON &= 0x3F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFA;			//设置定时初始值
	TH1 = 0xFA;			//设置定时重载值
	ET1 = 0;			//禁止定时器1中断
	TR1 = 1;			//定时器1开始计时
}

void UART_Init_Revice(void)	//4800bps@11.0592MHz
{
	UART_Init_Send();
	ES = 1;
	EA = 1;
}

void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}

/*
void UART_Routine(void)	interrupt 4
{

}
*/