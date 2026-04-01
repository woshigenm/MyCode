#include <stdio.h>

/*
16高考真题第一问
输出样例
153 370 371 407
*/
void test_1() {
	int i;
	printf("所有的水仙花数为:\n");
	for (i = 100; i < 1000; i++) {
		int j = i / 100;
		int k = i / 10 % 10;
		int m = i % 10;

		if (j * j * j + k * k * k + m * m * m == i)
			printf("%d ", i);
	}
}

/*
16高考真题第二问
输出样例
*********
 *******
  *****
   ***
    *
*/
void test_2() {
	int i, j, k;
	for (i = 5; i >= 1; i--) {
		for (k = 5; k > i; k--)
			putchar(' ');

		for (j = 2 * i - 1; j >= 1; j--)
			putchar('*');

		putchar('\n');
	}
}

int main() {

	return 0;
}
