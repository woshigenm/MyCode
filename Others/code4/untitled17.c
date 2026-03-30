/*
【抓球枚举法】现有红球3个，白球7个，黑球4个，任意抓8个球，红球和白球必须要抓一个
，输出每种组合方式，红球，白球，黑球各多少个,并输出共有多少种可能，输入输出形式如下。
*/
#include <stdio.h>

int main() {
	int red, white, black;

	int counter = 0;

	for(red = 1; red <= 3; red++) {
		for(white = 1; white <= 7; white++) {
			for(black = 0; black <= 4; black++) {
				if(red + white + black == 8) {
					printf("红球有%d个,白球有%d个,黑球有%d个\n", red, white, black);
					counter++;
				}
			}
//	black = 8 - red - white;
//
//	if(black >= 0 && black <= 4)
//	{
//	printf("红球有%d个,白球有%d个,黑球有%d个\n", red, white, black);
//	counter++;
//	}
		}
	}

	printf("共有%d种可能\n", counter);
	return 0;
}

