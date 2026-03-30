#include <stdio.h>

/*
19高考真题第一问
输出样例
6 28
*/
void test_1() {
	int sum;

	int i, j;
	for(i = 1; i <= 100; i++) {
		sum = 0;
		for(j = 1; j < i; j++) {
			if(i % j == 0)	sum += j;
		}

		if(i == sum)	printf("%d ", i);
	}
}

/*
19高考真题第二问 第一种做法
输入输出样例
f1A1n4X5i1A9oChAo@Sm
这个数为 11451
*/
void test_2_1() {
	char str[11];

	gets(str);

	int i;

	int sum = 0;
	for(i = 0; str[i] != '\0'; i++) {
		if(str[i] >= '0' && str[i] <= '9') {
			sum = sum * 10 + (str[i] - '0');
		}
	}

	printf("这个数为 %d\n", sum);
}

/*
19高考真题第二问 第二种做法
输入输出样例
f1A1n4X5i1A9oChAo@Sm
这个数为 11451
*/
void test_2_2() {
	char c;

	int i = 0;

	int sum = 0;

	for(i = 0; (c = getchar()) != '\n' && i < 10; i++) {
		if(c >= '0' && c <= '9') {
			sum = sum * 10 + (c - '0');
		}
	}

	printf("这个数为 %d\n", sum);
}


int main() {

	return 0;
}
