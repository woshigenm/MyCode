#include <stdio.h>

/*
15高考真题第一问
输入输出样例
1 2 3
3 2 1

1 3 2
3 2 1
*/
void test_1() {
	int x, y, z, t;
	printf("请输入三个整数(空格分隔): \n");
	scanf("%d%d%d", &x, &y, &z);
	if (x < y) {
		t = x;
		x = y;
		y = t;
	}

	if (x < z) {
		t = x;
		x = z;
		z = t;
	}
	if (y < z) {
		t = y;
		y = z;
		z = t;
	}

	printf("%d %d %d\n", x, y, z);
}

/*
15高考真题第二问 第一种做法
输入输出样例
24
24 的二进制为 11000
114
114 的二进制为 1110010
*/
void test_2_1() {
	int x;
	printf("请输入一个十进制整数: ");
	scanf("%d", &x);

	int e = 1;
	int t = x;

	int sum = 0;
	while (t) {
		sum += e * (t % 2);
		e *= 10;
		t /= 2;
	}

	printf("%d 的二进制为 %d\n", x, sum);
}

/*
15高考真题第二问 第二种做法
输入输出样例
114514
114514 的二进制为 11011111101010010
1919810
1919810 的二进制为 111010100101101000010
*/
void test_2_2() {
	int array[32];
	int x, i, j, t;

	printf("请输入一个十进制整数: ");
	scanf("%d", &x);
	t = x;
	for (i = 0; t != 0; i++) {
		array[i] = t % 2;
		t /= 2;
	}

	printf("%d 的二进制为 ", x);
	for (j = i - 1; j >= 0; j--)
		printf("%d", array[j]);
}

/*
15高考真题第二问 第三种做法
输入输出样例
24
11000
*/
void test_2_3(int x) {
	int t = x % 2;

	if (x > 1) {
		test_2_3(x / 2);
	}

	putchar(t == 0 ? '0' : '1');
}

void test_2_4() {
	int array[32] = {};
	int x, i, t;

	printf("请输入一个十进制整数: ");
	scanf("%d", &x);
	t = x;

	for (i = 0; t != 0; i++, t /= 2) {
		if (t % 2 == 1) {
			array[i] = 1;
		}
	}

	for (i = 31; i >= 0; i--) {
		printf("%d", array[i]);
		if (i % 8 == 0)
			putchar(' ');
	}
}

int main() {
	test_2_4();
	return 0;
}
