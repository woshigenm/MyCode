#ifndef __UART__H_
#define __UART__H_
	void UART_Init_Send(void);	//4800bps@11.0592MHz
	void UART_Init_Revice(void);
	void UART_SendByte(unsigned char Byte);
#endif