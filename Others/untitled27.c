/*
【回文数的判定】输出100到200的回文数
（回文数是一个整数，从最高位到最低位组成的数和从最低位到最高位组成的数相同，这个数就是回文数），输入输出形式如下。
*/

#include <stdio.h>

int main() {
	int i, j;
	int k = 10;

	printf("100到200的回文数有");
	for (i = 100; i <= 200; i++) {
		int m = i;
		int sum = 0;
		while (m) {
			sum = sum * 10 + m % 10;
			m /= 10;
		}

		if (sum == i) {
			printf("%d ", i);
		}
	}
	return 0;
}
