#include <stdio.h>

/*
7高考真题第一问
输入输出样例
请输入年月份(空格分隔): 2024 2
2 月有 29 天
请输入年月份(空格分隔): 2024 13
月份输入有误
*/
void test_1()
{
	int year, month;
GO:
	printf("请输入年月(空格分隔): ");
	scanf("%d%d", &year, &month);

	if (month > 12 || month < 0) {
		printf("月份输入有误\n");
		goto GO;
	} else {
		switch (month) {
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				printf("%d 月有 %d 天\n", month, 31);
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				printf("%d 月有 %d 天\n", month, 30);
				break;
			case 2:
				if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
					printf("2 月有 %d 天\n", 29);
				else
					printf("2 月有 %d 天\n", 28);
		}
	}
}

/*
7高考真题第二问
输出样例
121 121 131 131 141 141 212 212 232 232 242 242 313 313 323 323 343 343 414 414 424 424 434 434
*/
void test_2()
{
	void test_2() {
		int i, j, k;
		for (i = 1; i <= 4; i++) {
			for (j = 1; j <= 4; j++) {
				for (k = 1; k <= 4; k++) {
					if (i != j && i != k && j != k) {
						int t = i * 100 + j * 10 + i;
						printf("%d ", t);
					}
				}
			}
		}
	}
}
int main()
{
	int i, j, k;
	for (i = 1; i <= 4; i++) {
		for (j = 1; j <= 4; j++) {
			for (k = 1; k <= 4; k++) {
				if (i != j && i != k && j != k) {
					int t = i * 100 + j * 10 + i;
					printf("%d ", t);
				}
			}
		}
	}
	return 0;
}
