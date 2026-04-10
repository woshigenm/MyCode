#include <REGX52.H>
#include "LCD1602.H"
#include "DS1302.H"
#include "Key.H"
#include "Delay.H"
#include "MatrixKey.H"
#include "timer0.H"

#define TIME_SIZE 6

char Time[TIME_SIZE] = {25, 8, 20, 10, 30, 30};
unsigned char Key_Num = 0;
unsigned char index;
bit MODE = 0; // 0:显示模式, 1:修改模式
bit TimeSetFlashFlag = 0;

void TimeShow();
void TimeSet();

void main()
{
	LCD_Init();
	DS1302_Init();
	Timer0_Init();

	SetTime();

	LCD_ShowString(1, 1, "  -  -  ");
	LCD_ShowString(2, 1, "  :  :  ");
	while (1) {
		Key_Num = Key();

		if (Key_Num == 2) {
			MODE = !MODE;
			if (MODE) {
				LCD_ShowString(1, 13, "EDIT");
				index = 0;
			} else {
				LCD_ShowString(1, 13, "    ");
				SetTime();
			}
		}

		if (MODE) {
			TimeSet();
		} else {
			TimeShow();
		}
	}
}

void TimeShow()
{
	ReadTime();
	LCD_ShowNum(1, 1, Time[YEAR], 2);   // 年
	LCD_ShowNum(1, 4, Time[MONTH], 2);  // 月
	LCD_ShowNum(1, 7, Time[DATE], 2);   // 日

	LCD_ShowNum(2, 1, Time[HOUR], 2);   // 时
	LCD_ShowNum(2, 4, Time[MINUTES], 2);// 分
	LCD_ShowNum(2, 7, Time[SECONDS], 2);// 秒
}


void TimeSet()
{
	if (Key_Num == 1) {
		++Time[index];
		if (Time[YEAR] > 99) Time[YEAR] = 0;
		if (Time[MONTH] > 12) Time[MONTH] = 1;

		switch (Time[MONTH]) {
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				if (Time[DATE] > 31)	Time[DATE] = 1;
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				if (Time[DATE] > 30)	Time[DATE] = 1;
				break;
			case 2:
				if (Time[YEAR] % 4 == 0) {
					if (Time[DATE] > 29)	Time[DATE] = 1;
				} else {
					if (Time[DATE] > 28)	Time[DATE] = 1;
				}
		}

		if (Time[HOUR] > 23)	Time[HOUR] = 0;
		if (Time[MINUTES] > 59)	Time[MINUTES] = 0;
		if (Time[SECONDS] > 59)	Time[SECONDS] = 0;
	}

	if (Key_Num == 3) {
		--Time[index];
		if (Time[YEAR] < 0) Time[YEAR] = 99;
		if (Time[MONTH] < 1) Time[MONTH] = 12;

		switch (Time[MONTH]) {
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				if (Time[DATE] < 1)	Time[DATE] = 31;
				if (Time[DATE] > 31)	Time[DATE] = 1;
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				if (Time[DATE] < 1)	Time[DATE] = 30;
				if (Time[DATE] > 30)	Time[DATE] = 1;
				break;
			case 2:
				if (Time[YEAR] % 4 == 0) {
					if (Time[DATE] < 1)	Time[DATE] = 29;
					if (Time[DATE] > 29)	Time[DATE] = 1;
				} else {
					if (Time[DATE] < 1)	Time[DATE] = 28;
					if (Time[DATE] > 28)	Time[DATE] = 1;
				}
		}

		if (Time[HOUR] < 0)	Time[HOUR] = 23;
		if (Time[MINUTES] < 0)	Time[MINUTES] = 59;
		if (Time[SECONDS] < 0)	Time[SECONDS] = 59;
	}

	if (Key_Num == 4) {
		index++;
		index %= 6;
	}

	if (index == 0 && TimeSetFlashFlag)
		LCD_ShowString(1, 1, "  ");
	else
		LCD_ShowNum(1, 1, Time[YEAR], 2);

	if (index == 1 && TimeSetFlashFlag)
		LCD_ShowString(1, 4, "  ");
	else
		LCD_ShowNum(1, 4, Time[MONTH], 2);

	if (index == 2 && TimeSetFlashFlag)
		LCD_ShowString(1, 7, "  ");
	else
		LCD_ShowNum(1, 7, Time[DATE], 2);

	if (index == 3 && TimeSetFlashFlag)
		LCD_ShowString(2, 1, "  ");
	else
		LCD_ShowNum(2, 1, Time[HOUR], 2);

	if (index == 4 && TimeSetFlashFlag)
		LCD_ShowString(2, 4, "  ");
	else
		LCD_ShowNum(2, 4, Time[MINUTES], 2);

	if (index == 5 && TimeSetFlashFlag)
		LCD_ShowString(2, 7, "  ");
	else
		LCD_ShowNum(2, 7, Time[SECONDS], 2);
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if (T0Count >= 300) { // 每300ms进入一次
		T0Count = 0;
		TimeSetFlashFlag = !TimeSetFlashFlag; //闪烁标志位取反
	}
}