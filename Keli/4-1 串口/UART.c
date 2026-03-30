#include <REGX52.H>

void UART_Init(void)
{
	PCON &= 0x3F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFA;			//设置定时初始值
	TH1 = 0xFA;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
}

void UART_Init_REVICE(void)
{
	UART_Init();
	ES = 1;
	EA = 1;
}

void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(!TI); // 当数据从发送缓冲区 SBUF 全部发送完成后，硬件会自动将 TI 置为 1
	TI = 0;
}

/*
void UART_Rountine(void)	interrupt 4
{
	if(RI)
	{
		P2 = ~SBUF;
		RI = 0;
	}
}	
*/