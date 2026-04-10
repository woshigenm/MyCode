#include "timer0.h"
#include <REGX52.H>

//xms 为微秒
void Timer0_Init(unsigned int xms)
{
	TMOD = (TMOD & 0XF0) | 0x01;
	TF0 = 0;
	TR0 = 1;

	TH0 = (MAX_US - xms) / 256;
	TL0 = (MAX_US - xms) % 256;

	ET0 = 1;
	EA = 1;
	PT0 = 0;
}