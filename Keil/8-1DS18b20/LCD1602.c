#include <REGX52.H>
#include <INTRINS.H>
#include "LCD1602.H"

sbit LCD1602_RS = P2 ^ 6; //数据/指令选择，1为数据，0为指令
sbit LCD1602_RW = P2 ^ 5; //读/写选择，1为读，0为写
sbit LCD1602_EN = P2 ^ 7; //使能，1为数据有效，下降沿执行命令

void Delay1ms(void)	//@11.0592MHz
{
	unsigned char data i, j;

	_nop_();
	i = 2;
	j = 199;
	do {
		while (--j);
	} while (--i);
}

void LCD_Init(void)
{
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x0C);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x01);
}

void LCD_WriteCommand(unsigned char Command)
{
	LCD1602_RS = 0;
	LCD1602_RW = 0;

	P0 = Command;

	LCD1602_EN = 1;
	Delay1ms();
	LCD1602_EN = 0;
	Delay1ms();
}

void LCD_WriteData(unsigned char Data)
{
	LCD1602_RS = 1;
	LCD1602_RW = 0;

	P0 = Data;

	LCD1602_EN = 1;
	Delay1ms();
	LCD1602_EN = 0;
	Delay1ms();
}

void LCD_SetCursor(unsigned char Line, unsigned char Column)
{
	if (Line == 1) {
		LCD_WriteCommand(0x80 | (Column - 1));
	} else {
		LCD_WriteCommand(0x80 | (Column - 1) +0x40);
	}
}

void LCD_ShowChar(unsigned char Line, unsigned char Column, unsigned char Char)
{
	LCD_SetCursor(Line, Column);
	LCD_WriteData(Char);
}

void LCD_ShowString(unsigned char Line, unsigned char Column, unsigned char * String)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);

	for (i = 0; String[i]; ++i) {
		LCD_WriteData(String[i]);
	}
}
int LCD_Pow(int X, int Y)
{
	unsigned char i;
	int Result = 1;
	for (i = 0; i < Y; i++) {
		Result *= X;
	}
	return Result;
}

void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned char Num, unsigned char Length)
{
	unsigned char i;// 110
	LCD_SetCursor(Line, Column);

	for (i = Length; i > 0; --i) {
		LCD_WriteData('0'  + (Num / LCD_Pow(10, i - 1) % 10));
	}
}