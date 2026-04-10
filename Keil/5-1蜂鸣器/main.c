#include <REGX52.H>
#include "Key.h"
#include "timer0.h"
#include "LCD1602.h"
#include "Nixie.h"
#include "Delay.h"
#include "Buzzer.h"

unsigned int code FreqTable[] = {
	63628, 63731, 63835, 63928, 64021, 64103, 64185, 64260, 64331, 64400, 64463, 64524,
	64580, 64633, 64684, 64732, 64777, 64820, 64860, 64898, 64934, 64968, 65000, 65030,
	65058, 65085, 65110, 65134, 65157, 65178, 65198, 65217, 65235, 65252, 65268, 65283
};

unsigned char KeyNum = 0;

void main()
{
	LCD_Init();

	Nixie(NIXIE_1, 0);
	while (1) {
		KeyNum = Key();
		if (KeyNum) {
			LCD_ShowNum(1, 1, KeyNum, 1);
			Buzzer(600);
			Nixie(NIXIE_1, KeyNum);
		}
	}
}