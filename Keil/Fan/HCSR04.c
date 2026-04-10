#include <REGX52.H>

sbit HCSR04_Trig = P1 ^ 1;
sbit HCSR04_Echo = P1 ^ 0;

unsigned int HCSR04_Measuring(void)
{
	unsigned char i;

	TMOD |= 0x01; // 设置定时器0 为 16位定时器

	HCSR04_Trig = 0;
	HCSR04_Trig = 1;
	i = 7;
	while (--i); // 20us 开始信号
	HCSR04_Trig = 0;

	while (!HCSR04_Echo);

	TR0 = 1;
	while (HCSR04_Echo);
	TR0 = 0;


}

//65536 us
void Timer0_Init(void) interrupt 1
{

}