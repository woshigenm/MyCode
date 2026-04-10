#include <REGX52.H>

void Timer0_Init()
{
	TMOD = (TMOD & 0XF0) | 0x01;
	TF0 = 0;
	TR0 = 1;

	TH0 = 0xFC;
	TL0 = 0x17;

	ET0 = 1;
	EA = 1;
	PT0 = 0;
}