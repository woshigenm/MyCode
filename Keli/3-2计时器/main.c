#include <REGX51.H>
#include "LCD1602.h"
#include "timer0.h"

#define TIMER_US 10000 // Timer0 interrupt every 10ms
#define FIRST_ROW 1
#define SECOND_ROW 2

void delay_ms(unsigned int ms);

unsigned char second = 0, minute = 0, hour = 0;
int main()
{
    LCD_Init();
    Timer0_Init(TIMER_US); // Initialize Timer0 for 1 US
    
    LCD_ShowString(FIRST_ROW, 1, "Timer0 Test");
    while(1)
    {
        if(second >= 60)
        {
            second = 0;
            minute++;
        }

        if(minute >= 60)
        {
            minute = 0;
            hour++;
        }

        if(hour >= 24)
        {
            hour = 0;
        }

        LCD_ShowNum(SECOND_ROW, 1, hour, 2);
        LCD_ShowChar(SECOND_ROW, 3, ':');
        LCD_ShowNum(SECOND_ROW, 4, minute, 2);
        LCD_ShowChar(SECOND_ROW, 6, ':');
        LCD_ShowNum(SECOND_ROW, 7, second, 2);

        delay_ms(100); // Update display every 100ms
    }
}

void Timer0_Rountine(void) interrupt 1
{
	static unsigned int T0Count = 0;

	TH0 = (MAX_US - TIMER_US) / 256;
	TL0 = (MAX_US - TIMER_US) % 256;
	
	if(++T0Count >= 100)
	{
        second++;
		T0Count = 0;
	}
}

// 毫秒级延时函数（基于12MHz晶振）
void delay_ms(unsigned int ms) {
	unsigned int i, j;
	for (i = 0; i < ms; i++)
		for (j = 0; j < 112; j++);
}
