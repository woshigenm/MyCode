#include <REGX51.H>
#include <INTRINS.H>
#include <STRING.H>
#include "LCD1602.H"
#include "timer0.h"
#include "Buzzer.h"
#include "Delay.h"
#include "MatrixKey.h"
#include "Nixie.h"

#define FIRST_ROW  1
#define SECOND_ROW 2
#define PASSWORD_LEN 13

// 函数声明
unsigned char MatrixKey();
void Delay(unsigned int xms);
void Init_PassWord();
void DisplayPasswordScreen();
void Show_Time();
void Buzzer(unsigned int xms);

// 全局变量
unsigned char GetKey = 0;
unsigned char hour = 0, minute = 0, second = 0;
char * PassWord = "1145141919810";
char InputPassWord[PASSWORD_LEN + 1];
bit timer_mode = 0;         // 0:密码模式, 1:计时器模式
bit timer_running = 0;       // 计时器运行状态

void main()
{
	unsigned char Current_Row = 1;
	unsigned char Current_Char = 0;

	// 初始化
	LCD_Init();
	Timer0_Init();
	DisplayPasswordScreen();

	while (1) {
		GetKey = MatrixKey();

		// 处理模式切换按键
		if (GetKey == KEY_13) {
			timer_mode = !timer_mode;

			LCD_ClearManual(2);
			if (timer_mode) {
				// 进入计时器模式
				LCD_ShowString(FIRST_ROW, 1, "TIMER:");
				timer_running = 1;
			} else {
				// 返回密码模式
				DisplayPasswordScreen();
				timer_running = 0; // 停止计时器
				Current_Row = 1;
				Current_Char = 0;
			}
		}

		// 根据当前模式处理按键
		if (timer_mode) {
			// 计时器模式下的按键处理
			switch (GetKey) {
				case KEY_11:
					// 暂停/继续计时器
					timer_running = !timer_running;
					LCD_ShowString(SECOND_ROW, 13, timer_running ? "RUN " : "PAUS");
					break;

				case KEY_12:
					// 重置计时器
					hour = minute = second = 0;
					Show_Time();
					break;
			}
		} else {
			// 密码模式下的按键处理
			switch (GetKey) {
				case KEY_1:
				case KEY_2:
				case KEY_3:
				case KEY_4:
				case KEY_5:
				case KEY_6:
				case KEY_7:
				case KEY_8:
				case KEY_9:
				case KEY_10:
					if (Current_Char < PASSWORD_LEN) {
						LCD_ShowNum(SECOND_ROW, Current_Row++, (GetKey == 10) ? 0 : GetKey, 1);
						InputPassWord[Current_Char++] = ((GetKey == 10) ? 0 : GetKey) + '0';

						Buzzer(100);

						if (Current_Char == PASSWORD_LEN) {
							InputPassWord[Current_Char] = '\0';
						}
					}
					break;

				case KEY_11:
					if (Current_Row > 1 && Current_Char > 0) {
						--Current_Row;
						--Current_Char;
					}
					LCD_ShowChar(SECOND_ROW, Current_Row, '*');
					InputPassWord[Current_Char] = '\0';
					break;

				case KEY_12:
					LCD_ClearManual(1);
					if (!strcmp(InputPassWord, PassWord)) {
						LCD_ShowString(SECOND_ROW, 1, "CORRECT");
					} else {
						LCD_ShowString(SECOND_ROW, 1, "ERROR");
					}

					Buzzer(100);
					Delay(500);
					Buzzer(100);

					LCD_ClearManual(1);
					Init_PassWord();
					Current_Row = 1;
					Current_Char = 0;
					break;
			}
		}

		// 显示当前按键值
		if (GetKey >= KEY_1 && GetKey <= KEY_16) {
			LCD_ShowNum(FIRST_ROW, 15, GetKey, 2);
		}
	}
}

/**
 * @brief 显示密码输入界面
 */
void DisplayPasswordScreen()
{
	LCD_ShowString(FIRST_ROW, 1, "PASSWORD:");
	Init_PassWord();
}

/**
 * @brief 初始化密码显示
 */
void Init_PassWord()
{
	unsigned char i;
	for (i = 1; i <= PASSWORD_LEN; ++i) {
		LCD_ShowChar(SECOND_ROW, i, '*');
	}
	memset(InputPassWord, 0, sizeof(InputPassWord));
}

/**
 * @brief 显示时间
 */
void Show_Time()
{
	LCD_ShowNum(SECOND_ROW, 1, hour, 2);
	LCD_ShowChar(SECOND_ROW, 3, ':');
	LCD_ShowNum(SECOND_ROW, 4, minute, 2);
	LCD_ShowChar(SECOND_ROW, 6, ':');
	LCD_ShowNum(SECOND_ROW, 7, second, 2);
}


void Time_Loop()
{
	// 只有在计时器运行状态下才更新时间
	if (timer_running) {
		if (++second >= 60) {
			second = 0;
			++minute;
		}

		if (minute >= 60) {
			minute = 0;
			++hour;
		}

		if (hour >= 24) {
			hour = 0;
		}

		// 更新计时器显示
		Show_Time();
	}
}
/**
 * @brief 定时器0中断服务程序
 */
void Timer0_Rountine() interrupt 1
{
	static unsigned int second_count = 0;

	// 重装定时器初值
	TH0 = 0xFC;
	TL0 = 0x17;

	if (++second_count >= 1000) {
		second_count = 0;

		Time_Loop();
	}
}
