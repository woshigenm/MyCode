#include <REGX52.H>
#include "LCD1602.H"
#include "DS1302.H"
#include "Delay.H"

unsigned char SetTime[] = {30, 30, 10, 20, 8, 3, 25};

void main()
{
	LCD_Init();
	//DS1302_Init();
	
	LCD_ShowString(1, 1, "    -  -  ");
	LCD_ShowString(2, 1, "  :  :  ");
	while(1)
	{
		//year
		LCD_ShowNum(1, 1, 20, 2);
		LCD_ShowNum(1, 3, BcdToDec(DS1302_ReadByte(0x8D)), 2);
		
		//month
		LCD_ShowNum(1, 6, BcdToDec(DS1302_ReadByte(0x89)), 2);
		
		//date
		LCD_ShowNum(1, 9, BcdToDec(DS1302_ReadByte(0x87)), 2);
		
		//hour
		LCD_ShowNum(2, 1, BcdToDec(DS1302_ReadByte(0x85)), 2);
		
		//minute
		LCD_ShowNum(2, 4, BcdToDec(DS1302_ReadByte(0x83)), 2);
		
		//second
		LCD_ShowNum(2, 7, BcdToDec(DS1302_ReadByte(0x81)), 2);
	}
}