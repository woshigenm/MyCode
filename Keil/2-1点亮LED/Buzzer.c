#include <REGX51.H>
#include <INTRINS.H>
#include "Buzzer.h"

sbit beep = P2 ^ 5;
void Delay500us(void);

/**
 * @brief 蜂鸣器响动函数
 * @param xms 响动毫秒数
 */
void Buzzer(unsigned int xms)
{
	unsigned int i;
	for (i = 0; i < 2 * xms; ++i) {
		beep = ~beep;
		Delay500us();
	}
}

/**
 * @brief 蜂鸣器专用延时函数
 */
void Delay500us(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 227;
	while (--i);
}
