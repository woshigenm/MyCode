#include <REGX52.H>
#include <INTRINS.H>
#include "Buzzer.h"

void Delay500us(void);

void Buzzer(unsigned int xms)
{
	unsigned int i;
	for (i = 0; i < 2 * xms; ++i) {
		beep = ~beep;
		Delay500us();
	}
}

void Delay500us(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 227;
	while (--i);
}
