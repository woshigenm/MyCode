#include <REGX52.H>
#include "MatrixLed.h"
#include "Delay.h"

#define MATRIX_LED_PORT		P0

sbit _74HC595_RCLK = P3 ^ 5; //存储寄存器时钟输入引脚
sbit _74HC595_SER  = P3 ^ 4; //串行数据输入引脚
sbit _74HC595_SRCLK = P3 ^ 6; //移位寄存器时钟引脚

void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for (i = 0; i < 8; ++i) {
		_74HC595_SER = Byte & (0x80 >> i);
		_74HC595_SRCLK = 0;
		_74HC595_SRCLK = 1;
	}

	_74HC595_RCLK = 0;
	_74HC595_RCLK = 1;
}

void MatrixLED(unsigned char Column, unsigned char Data)
{
	_74HC595_WriteByte(Data);
	MATRIX_LED_PORT = ~(0x80 >> Column); //共阳极
	Delay(1);
	MATRIX_LED_PORT = 0xFF;
}