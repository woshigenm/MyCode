#include <REGX52.H>
#include "AT24C02.h"
#include "Key.h"
#include "Delay.h"
#include "Timer0.h"
#include "Nixie.h"

unsigned char KeyNumber = 0;
unsigned int Number = 0;
unsigned char Hour, Min, Sec;
bit RunFlag = 0;

void main()
{
	Timer0_Init();

	while (1) {
		KeyNumber = GetKey();
		if (KeyNumber == 1) {
			RunFlag = !RunFlag;
		}

		if (KeyNumber == 2) {
			Hour = Min = Sec = 0;
		}

		if (KeyNumber == 3) {
			AT24C02_WriteByte(0, Hour);
			Delay(5);
			AT24C02_WriteByte(1, Min);
			Delay(5);
			AT24C02_WriteByte(2, Sec);
			Delay(5);
		}

		if (KeyNumber == 4) {
			Hour = AT24C02_ReadByte(0);
			Min = AT24C02_ReadByte(1);
			Sec = AT24C02_ReadByte(2);
		}

		Nixie_SetBuf(7, Hour / 10);
		Nixie_SetBuf(6, Hour % 10);
		Nixie_SetBuf(4, Min / 10);
		Nixie_SetBuf(3, Min % 10);
		Nixie_SetBuf(1, Sec / 10);
		Nixie_SetBuf(0, Sec % 10);
	}
}

void Sec_Loop(void)
{
	if (RunFlag) {
		if (Sec++ >= 60) {
			Sec = 0;
			if (Min++ >= 60) {
				Min = 0;
				if (Hour++ >= 24) {
					Hour = 0;
				}
			}
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count, T1Count, T2Count;
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值

	if (T0Count++ >= 20) { //每20ms进入一次
		T0Count = 0;
		Key_Loop();
	}

	if (T1Count++ >= 2) { //每20ms进入一次
		T1Count = 0;
		Nixie_Loop();
	}

	if (T2Count++ >= 1000) {
		T2Count = 0;
		Sec_Loop();
	}
}