#include <stdio.h>

long long C(int n, int m);

int main() {
	int n = 10;
	int i, j, k;
	for (i = 0; i < n; i++) {
		for (j = n - 1; j > i; j--) {
			putchar(' ');
		}

		for (k = 0; k <= i; k++) {
			printf("%lld ", C(i, k));
		}

		putchar('\n');
	}
	return 0;
}

long long C(int n, int m) {
	//C52 5*4/1*2

	if (n < m)	return -1;

	if (m == n || m == 0)	return 1;

	if (m > n / 2)	m = n - m;

	long long sum = 1;

	for (int i = n, j = 1; i >= m && j <= m; i--, j++) {
		sum *= i;
		sum /= j;
	}

	return sum;
}
