#include <stdio.h>

int main() {
	int n;
	scanf("%d", &n);

	if (n <= 1) {
		printf("请输入大于一的数\n");
		return -1;
	}

	int i;
	for (i = 2; i < n; i++) {
		if (n % i == 0) {
			printf("%d不是质数\n", n);
			break;
		}
	}

	if (i >= n) {
		printf("%d是质数\n", n);
	}

	for (i = 2; i <= n / 2; i++) {
		if (n % i == 0) {
			printf("%d不是质数\n", n);
			break;
		}
	}

	if (i > n / 2) {
		printf("%d是质数\n", n);
	}

	for (i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			printf("%d不是质数\n", n);
			break;
		}
	}

	if (i * i > n) {
		printf("%d是质数\n", n);
	}
	return 0;
}
