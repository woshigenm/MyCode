#include <REGX52.H>
#include "timer0.h"
#include <INTRINS.H>

#define TIMER_US 10000 // US

void delay_ms(unsigned int ms);
void Timer0_Rountine(void);

bit Move_State = 0;

int main()
{
	Timer0_Init(TIMER_US);

	P2 = 0xFE; // Set P2.0 to low to indicate timer is running

	while (1) {
		if (!P3_1)	Move_State = 1;
		if (!P3_0)	Move_State = 0;
	}
}

void Timer0_Rountine(void) interrupt 1
{
	static unsigned int T0Count = 0;

	TH0 = (MAX_US - TIMER_US) / 256;
	TL0 = (MAX_US - TIMER_US) % 256;

	if (++T0Count >= 100) {
		if (Move_State)
			P2 = _cror_(P2, 1); // Rotate P2 bits to the left
		else
			P2 = _crol_(P2, 1);

		T0Count = 0;
	}
}

void delay_ms(unsigned int ms)
{
	unsigned int i, j;
	for (i = 0; i < ms; i++)
		for (j = 0; j < 112; j++);
}