#include <REGX52.H>

sbit LCD_RS = P2^6;
sbit LCD_RW = P2^5;
sbit LCD_EN = P2^7;

#define LCD_DATAPROT P0

void LCD_Delay(void)	//@11.0592MHz
{
	unsigned char data i, j;

	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DATAPROT = Command;
	LCD_EN = 1;
	LCD_Delay();
	LCD_EN = 0;
	LCD_Delay();
}

void LCD_WriteData(unsigned char Data)
{
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_DATAPROT = Data;
	LCD_EN = 1;
	LCD_Delay();
	LCD_EN = 0;
	LCD_Delay();
}

void LCD_Init(void)
{
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x0C);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x01);
}

void LCD_ClearScreen(void)
{
	LCD_WriteCommand(0x01);
}

void LCD_SetCursor(unsigned char Line, unsigned char Column)
{
	if(Line == 1 || Line == 2)	
		LCD_WriteCommand(0x80 | (0x40 * (Line - 1) + (Column - 1)));
}

void LCD_ShowChar(unsigned char Line, unsigned char Column, unsigned char Char)
{
	LCD_SetCursor(Line, Column);
	LCD_WriteData(Char);
}

void LCD_ShowString(unsigned char Line, unsigned char Column, unsigned char * Str)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	
	for(i = 0; Str[i]; ++i)
	{
		LCD_WriteData(Str[i]);
	}
}

unsigned int LCD_Pow(unsigned char X, unsigned char Y)
{
	unsigned int Result = 1;
	while(Y--)
	{
		Result*=X;
	}
	return Result;
}

void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Num, unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	
	for(i = Length; i > 0; --i)
	{
		LCD_WriteData(0x30 | (Num / LCD_Pow(10, i - 1) % 10));
	}
}

void LCD_ShowSignedNum(unsigned char Line, unsigned char Column, int Num, unsigned char Length)
{
	unsigned char i;
	unsigned int Number;
	LCD_SetCursor(Line, Column);
	if(Num < 0)
	{
		LCD_WriteData('-');
		Number = -Num;
	}else
	{
		LCD_WriteData('+');
		Number = Num;
	}
	
	for(i = Length; i > 0; --i)
	{
		LCD_WriteData(0x30 | (Number / LCD_Pow(10, i - 1) % 10));
	}
}

void LCD_ShowBinNum(unsigned char Line, unsigned char Column, int Num, unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for(i = Length; i > 0; --i)
	{
		LCD_WriteData(0x30 | (Num / (0x01 << (i - 1)) % 2));
	}
}

void LCD_ShowHexNum(unsigned char Line, unsigned char Column, int Num, unsigned char Length)
{
	unsigned char i, Number, shift;
	LCD_SetCursor(Line, Column);
	for(i = Length; i > 0; --i)
	{
		shift = (i - 1) << 2;
		Number = (Num >> shift) & 0x0F;
		
		if(Number <= 9)
		{
			Number = '0' + Number;
		}else
		{
			Number = 'A' - 10 + Number;
		}
		
		LCD_WriteData(Number);
	}
}
