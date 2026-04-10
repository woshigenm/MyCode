#include <REGX52.H>
#include "delay.h"
#include "oled.h"

void main()
{
	oled_init();
	while (1) {
		oled_clear();
		delay_ms(500);
		oled_full();
		delay_ms(500);
	}
}
