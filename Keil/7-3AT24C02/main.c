#include <REGX52.H>
#include "LCD1602.H"
#include "Key.h"
#include "Delay.h"
#include "AT24C02.H"

unsigned char KeyNum;
unsigned int Num;

void main()
{
	LCD_Init();

	LCD_ShowNum(1, 1, Num, 5);
	while (1) {
		KeyNum = Key();

		if (KeyNum)	LCD_ShowNum(1, 10, KeyNum, 1);
		switch (KeyNum) {
			case 1:
				--Num;
				LCD_ShowNum(1, 1, Num, 5);
				break;
			case 2:
				++Num;
				LCD_ShowNum(1, 1, Num, 5);
				break;
			case 3:
				AT24C02_WriteByte(1, Num / 256);
				Delay(6);
				AT24C02_WriteByte(0, Num % 256);
				Delay(6);

				LCD_ShowString(1, 15, "WT");
				Delay(1000);
				LCD_ShowString(1, 15, "  ");
				break;
			case 4:
				Num = AT24C02_ReadByte(0);
				Num |= AT24C02_ReadByte(1) << 8;
				LCD_ShowNum(1, 1, Num, 5);

				LCD_ShowString(1, 15, "RD");
				Delay(1000);
				LCD_ShowString(1, 15, "  ");
				break;
		}
	}
}