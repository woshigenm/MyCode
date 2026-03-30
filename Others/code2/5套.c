#include <stdio.h>

/*
5高考真题第一问
输入输出样例
114 191
114 到 191 之间能被 6 整除的数为:
114 120 126 132 138 144 150 156 162 168 174 180 186
80 到 90 之间能被 6 整除的数为:
84 90
*/
void test_1() {
	int x, y, t;
	GO: printf("请输入两个不超过200的正整数(空格分隔): ");
	scanf("%d%d", &x, &y);
	if (x > 200 || y > 200 || x < 0 || y < 0) {
		printf("请正确输入数\n");
		goto GO;
	} else {
		if (x > y) {
			t = x;
			x = y;
			y = t;
		}

		printf("%d 到 %d 之间能被 6 整除的数为:\n", x, y);

		int i;
		for (i = x; i <= y; i++) {
			if (i % 6 == 0) {
				printf("%d ", i);
			}
		}
	}
}

/*
5高考真题第二问
输出样例
*
***
*****
*******
*********
*/
void test_2() {
	int i, j;
	for (i = 1; i <= 5; i++) {
		for (j = 1; j <= 2 * i - 1; j++)
			putchar('*');
		putchar('\n');
	}
}

int main() {
	test_1();
	return 0;
}
