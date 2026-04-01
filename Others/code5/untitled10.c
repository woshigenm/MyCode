#include <stdio.h>

int C(int n, int m) {

	if (n < 0 || m < 0 || n < m)	return -1;

	if (m > n / 2)	m = n - m;
	int sum = 1;
	for (int i = n, j = 1; i >= m && j <= m; i--, j++) {
		sum *= i;
		sum /= j;
	}

	return sum;
}

int n;
void Yang() {
	int array[128][128] = {};
	/*
	{
	{1,0,0,0},
	{1,1,0,0},
	{1,2,1,0},
	{1,3,3,1},
	}
	*/

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			if (i == j)
				array[i][j] = 1;
			else {
				array[i][j] = array[i - 1][j] + array[i - 1][j - 1];
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int k = 1; k <= n - i; k++) {
			putchar(' ');
		}

		for (int j = 0; j <= i; j++) {
			printf("%d ", array[i][j]);
		}

		putchar('\n');
	}

	putchar('\n');
}

void Yang1() {
	for (int i = 0; i < n; i++) {

		for (int k = n - 1; k > i; k--) {
			putchar(' ');
		}

		for (int j = 0; j <= i; j++) {
			printf("%d ", C(i, j));
		}

		putchar('\n');
	}

	putchar('\n');
}

int main() {
	scanf("%d", &n);
	int a[128] = {0, 1};
	int b[128] = {0};


	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n - i; j++)
			putchar(' ');

		for (int k = 1; k <= i; k++)
			printf("%d ", b[k] = a[k - 1] + a[k]);

		for (int m = 1; m <= i; m++)
			a[m] = b[m];

		putchar('\n');
	}

	return 0;
}

