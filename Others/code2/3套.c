#include <stdio.h>

/*
3高考真题第一问 第一种做法
输出样例
11411
是回文数
114514
请输入正确的数
*/
void test_1_1() {
	int x, t, sum;
	printf("请输入一个五位数: ");
	scanf("%d", &x);
	if (x > 99999 || x < 10000) {
		printf("请输入正确的数\n");
	} else {
		t = x;
		sum = 0;
		while (t) {
			sum = sum * 10 + t % 10;
			t /= 10;
		}

		if (sum == x) {
			printf("是回文数\n");
		} else {
			printf("不是回文数\n");
		}
	}
}

/*
3高考真题第一问 第一种做法
输出样例
14541
是回文数
-114514
请输入正确的数
*/
void test_1_2() {
	int x;
	printf("请输入一个五位数: ");
	scanf("%d", &x);
	if (x > 99999 || x < 10000) {
		printf("请输入正确的数\n");
	} else {
		int i, j, k, m, n;

		i = x / 10000;	//万位
		j = x / 1000 % 10;//千位
		k = x / 100 % 10;//百位
		m = x / 10 % 10;//十位
		n = x % 10;//个位

		int t = n * 10000 + m * 1000 + k * 100 + j * 10 + i;

		if (t == x) {
			printf("是回文数\n");
		} else {
			printf("不是回文数\n");
		}
	}
}

/*
3高考真题第二问
输入输出样例
2000 2025
2000 到 2025 之间的闰年为:
2000 2004 2008 2012 2016 2020 2024
114514 114500
114500 到 114514 之间的闰年为:
114504 114508 114512
*/
void test_2() {
	int year1, year2, t;
	printf("请输入两个年份(空格分隔): ");
	scanf("%d%d", &year1, &year2);

	if (year1 > year2) {
		t = year1;
		year1 = year2;
		year2 = t;
	}

	printf("%d 到 %d 之间的闰年为:\n", year1, year2);
	int i;
	for (i = year1; i <= year2; i++) {
		if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0) {
			printf("%d ", i);
		}
	}
}

int main() {
	int year1, year2, t;
	printf("请输入两个年份(空格分隔): ");
	scanf("%d%d", &year1, &year2);

	if (year1 > year2) {
		t = year1;
		year1 = year2;
		year2 = t;
	}

	printf("%d 到 %d 之间的闰年为:\n", year1, year2);
	int i;
	for (i = year1; i <= year2; i++) {
		if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0) {
			printf("%d ", i);
		}
	}
	return 0;
}
