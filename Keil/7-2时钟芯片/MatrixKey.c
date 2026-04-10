#include <REGX51.H>
#include "Delay.h"

#define ROW 4
#define COL 4

// 按键值枚举
enum KeyValues {
	KEY_1 = 1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_10,
	KEY_11,
	KEY_12,
	KEY_13,
	KEY_14,
	KEY_15,
	KEY_16
};

unsigned char MatrixKey()
{
	static const unsigned char KeyMap[4][4] = {
		{KEY_1, KEY_4, KEY_7, KEY_16},   // 第0行
		{KEY_2, KEY_5, KEY_8, KEY_15},   // 第1行
		{KEY_3, KEY_6, KEY_9, KEY_14},   // 第2行
		{KEY_10, KEY_11, KEY_12, KEY_13} // 第3行
	};

	unsigned char i, j;
	for (i = 0; i < ROW; ++i) {
		P1 = 0xFF;
		P1 &= ~(1 << (3 - i));

		for (j = 0; j < COL; ++j) {
			if (!(P1 & (1 << (j + 4)))) {
				Delay(5);
				while (!(P1 & (1 << (j + 4))));
				return KeyMap[i][j];
			}
		}
	}

	return 0;
}