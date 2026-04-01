/*
【n！】用for循环编写程序，输入任意一个整数n（1<=n<=9），求n！,输入输出形式如下。
*/
#include <stdio.h>

int main() {
	int n;
	scanf("%d", &n);
	int sum = 1;

	for (int i = 1; i <= n; i++) {
		sum *= i;
	}

	printf("%d!=%d\n", n, sum);
	return  0;
}
