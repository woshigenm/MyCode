#include <stdio.h>
#include <math.h>
long long C(int n, int m);

#define SIZE 5

int main() {
	/*
	1 2 3 4 5
	1	    1
	2	   1 1
	3	  1 2 1
	4	 1 3 3 1
	5	1 4 6 4 1
	*/
	long long array[SIZE][SIZE] = {};
	/*
	{
		{1,0,0,0,0}
		{1,1,0,0,0}
		{1,2,1,0,0}
		{1,3,3,1,0}
		{1,4,6,4,1}
	}
	*/
	int n = SIZE;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == 0 || j == i) {
				array[i][j] = 1;
			} else
				array[i][j] = array[i - 1][j - 1] + array[i - 1][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int k = SIZE - 1; k > i; k--) {
			putchar(' ');
		}
		for (int j = 0; j < n; j++) {
			if (array[i][j] != 0)	printf("%lld ", array[i][j]);
		}
		putchar('\n');
	}
	return 0;
}

void fanxiaochao() {
	int n = 10;
	int i, j, k;
	for (i = 0; i < n; i++) {
		for (j = n - 1; j > i; j--) {
			putchar(' ');
		}

		for (k = 0; k <= i; k++) {
			long long a = C(i, k);
			printf("%lld ", a);
		}

		putchar('\n');
	}
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
