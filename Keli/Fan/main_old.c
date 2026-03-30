#include <REGX52.H>
#include "LCD1602.h"
#include "MatrixKey.h"
#include "DS1302.h"
#include "Delay.h"
#include "Key.h"
#include "Timer0.h"

unsigned char KeyNumber = 0;
unsigned char Index = 0;
bit FlashFlag = 0;
bit MODE = 0;

void ShowTime(void);
void Modify_Time(void);

void main()
{
	LCD_Init();
	DS1302_Init();
	Timer0_Init();
	
	LCD_ShowString(1,1,"  -  -");
	LCD_ShowString(2,1,"  :  :");
	while(1)
	{
		KeyNumber = Key();
		if(KeyNumber == 1)
		{
			if(MODE) // 修改模式
			{
				DS1302_SetTime();

			}else // 显示模式
			{
				Index = 0;
			}
			
			MODE = !MODE;
		}
		
		if(MODE)
		{
			Modify_Time();
		}else
		{
			ShowTime();
		}
	}
}

void ShowTime(void)
{
	DS1302_GetTime();
	LCD_ShowNum(1,1,Time[YEAR], 2);
	LCD_ShowNum(1,4,Time[MONTH], 2);
	LCD_ShowNum(1,7,Time[DATE], 2);
	LCD_ShowNum(2,1,Time[HOUR], 2);
	LCD_ShowNum(2,4,Time[MINUTE], 2);
	LCD_ShowNum(2,7,Time[SECOND], 2);	
}	

void Modify_Time(void)
{
	if(KeyNumber == 2)
	{
		++Time[Index];
		if(Time[YEAR] > 99) Time[YEAR] = 0;
		if(Time[MONTH] > 12) Time[YEAR] = 1;
		
		switch(Time[MONTH])
		{
			case 1:case 3:case 5:case 7:case 8:case 10:case 12:
				if(Time[DATE] > 31) Time[DATE] = 1;
				break;
			
			case 4:case 6:case 9:case 11:
				if(Time[DATE] > 30) Time[DATE] = 1;
				break;
			
			case 2:
			{
				if(Time[YEAR] % 4 == 0)
				{
					if(Time[DATE] > 29) Time[DATE] = 1;
				}else
				{
					if(Time[DATE] > 28) Time[DATE] = 1;
				}
			}
		}
		
		if(Time[HOUR] > 23) Time[HOUR] = 0;
		if(Time[MINUTE] > 59) Time[MINUTE] = 0;
		if(Time[SECOND] > 59) Time[SECOND] = 0;
	}
	
	if(KeyNumber == 3)
	{
		--Time[Index];
		if(Time[YEAR] < 0) Time[YEAR] = 99;
		if(Time[MONTH] < 1) Time[YEAR] = 12;
		
		switch(Time[MONTH])
		{
			case 1:case 3:case 5:case 7:case 8:case 10:case 12:
				if(Time[DATE] > 31) Time[DATE] = 1;
				if(Time[DATE] < 1) Time[DATE] = 31;
				break;
			
			case 4:case 6:case 9:case 11:
				if(Time[DATE] > 30) Time[DATE] = 1;
				if(Time[DATE] < 1) Time[DATE] = 30;
				break;
			
			case 2:
			{
				if(Time[YEAR] % 4 == 0)
				{
					if(Time[DATE] > 29) Time[DATE] = 1;
					if(Time[DATE] < 1) Time[DATE] = 29;
				}else
				{
					if(Time[DATE] > 28) Time[DATE] = 1;
					if(Time[DATE] < 1) Time[DATE] = 28;
				}
			}
		}
		
		if(Time[HOUR] < 0) Time[HOUR] = 23;
		if(Time[MINUTE] < 0) Time[MINUTE] = 59;
		if(Time[SECOND] < 0) Time[SECOND] = 59;
	}
	
	if(KeyNumber == 4)
	{
		LCD_ShowNum(1, 15, Index, 1);
		Index++;
		Index %= 6;
	}
	
	if(FlashFlag && Index == YEAR)
	{
		LCD_ShowString(1,1,"  ");
	}else
	{
		LCD_ShowNum(1,1,Time[YEAR], 2);
	}
	
	if(FlashFlag && Index == MONTH)
	{
		LCD_ShowString(1,4,"  ");		
	}else
	{
		LCD_ShowNum(1,4,Time[MONTH], 2);
	}
	
	if(FlashFlag && Index == DATE)
	{
		LCD_ShowString(1,7,"  ");
	}else
	{
		LCD_ShowNum(1,7,Time[DATE], 2);
	}
	
	if(FlashFlag && Index == HOUR)
	{
		LCD_ShowString(2,1,"  ");		
	}else
	{
		LCD_ShowNum(2,1,Time[HOUR], 2);
	}
	
	if(FlashFlag && Index == MINUTE)
	{
		LCD_ShowString(2,4,"  ");		
	}else
	{
		LCD_ShowNum(2,4,Time[MINUTE], 2);
	}
	
	if(FlashFlag && Index == SECOND)
	{
		LCD_ShowString(2,7,"  ");	
	}else
	{
		LCD_ShowNum(2,7,Time[SECOND], 2);
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	
	if(T0Count++>=500)//每500ms进入一次
	{
		T0Count=0;
		FlashFlag = !FlashFlag;
	}
}