#include <stdio.h>

int main()
{
	int n = 1234321;
	int m = n;

	int sum = 0;
	while (m) {
		sum = sum * 10 + m % 10;
		m /= 10;
	}
	printf("%d\n", sum);


	if (m == n) {
		printf("%d是回文数\n", n);
	}
	return 0;
}

