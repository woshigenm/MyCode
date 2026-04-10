#include <REGX52.H>
#include "MatrixLed.h"
#include "Delay.h"

void _74HC595_Write(unsigned char Num);

sbit RCK = P3 ^ 5; //存储寄存器时钟输入引脚
sbit SCK = P3 ^ 6; //移位寄存器时钟引脚
sbit SER = P3 ^ 4; //数据入口存储器引脚

void MatrixLed_Init()
{
	SCK = 0;
	RCK = 0;
}

void MatrixLed_Show(unsigned char Col, unsigned char Data)
{
	_74HC595_Write(Data);

	P0 = ~(0x80 >> Col);

	Delay(1);
	P0 = 0xFF;
}

void _74HC595_Write(unsigned char Num)
{
	unsigned char i;
	for (i = 0; i < 8; ++i) {
		SER = Num & (0x80 >> i);
		SCK = 0;
		SCK = 1;
	}

	RCK = 1;
	RCK = 0;
}

