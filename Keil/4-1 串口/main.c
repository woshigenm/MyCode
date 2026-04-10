#include <REGX52.H>
#include "UART.h"
#include "Delay.h"

unsigned int sec;

void main()
{
	//UART_Init_REVICE();
	UART_SendByte(0x11);
	while (1) {

	}
}

void UART_Rountine(void)	interrupt 4
{
	if (RI) {
		P2 = ~SBUF;
		RI = 0;
	}
}