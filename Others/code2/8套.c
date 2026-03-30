#include <stdio.h>


void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}
/*
8高考真题第一问
输入输出样例
1 2 3 4
4 3 2 1
114 514 1919 8101
8101 1919 514 114
*/
void test_1() {
	int a, b, c, d, t;
	printf("请输入四个整数(空格分隔): ");

	scanf("%d%d%d%d", &a, &b, &c, &d);
	if (a < b) {
		t = a;
		a = b;
		b = t;
	}

	if (a < c) {
		t = a;
		a = c;
		c = t;
	}

	if (a < d) {
		t = a;
		a = d;
		d = t;
	}

	if (b < c) {
		t = b;
		b = c;
		c = t;
	}

	if (b < d) {
		t = b;
		b = d;
		d = t;
	}

	if (c < d) {
		t = c;
		c = d;
		d = t;
	}

	printf("从大到小为 %d %d %d %d\n", a, b, c, d);
}

/*
8高考真题第二问
输出样例
1+1/2+1/3+...1/50 = 4.499206
*/
void test_2() {
	float sum = 0;

	int i;

	for (i = 1; i <= 50; i++) {
		sum += 1.0 / i;
	}

	printf("1+1/2+1/3+...1/50 = %f\n", sum);
}

int main() {

	return 0;
}
