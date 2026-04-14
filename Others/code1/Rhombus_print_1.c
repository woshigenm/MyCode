#include <stdio.h>
#include <math.h>

int main()
{
	/*
	0123456
	   1		1 7-6		3
	  121		3 7-4		2
	 12321		5 7-2		1
	1234321		7 7-0		0
	 12321		5 7-abs(-2)	1
	  121		3 7-abs(-4)	2
	   1		1 7-abs(-5)	3
	*/

	/*
	0123456
	  1		1 5-4		2
	 121	3 5-2		1
	12321	5 5-0		0
	 121	3 5-abs(-2)	1
	  1		1 5-abs(-4)	2
	*/

	int i, j, k, m;

	int n;
	scanf("%d", &n);
	for (i = 1, k = n - 1; i <= n; i++, k -= 2) {
		int t = n - abs(k);
		int u = (n + 1) / 2;
		for (int p = abs(u - i); p >= 1 ; p--)
			putchar(' ');

		for (j = 1, m = 0; j <= t; j++, m++) {
			if (j <= (t / 2) + 1)
				printf("%d", j);
			else {
				printf("%d", t - m);
			}
		}
		putchar('\n');
	}

	putchar('\n');

//	for (i = 1; i <= (n / 2) + 1; i++) {
//		int t = 2 * i - 1;
//		for (j = 1, k = 0; j <= t; j++, k++) {
//			if (j <= (t / 2) + 1)
//				printf("%d", j);
//			else {
//				printf("%d", t - k);
//			}
//		}
//		putchar('\n');
//	}
//
//	for (i = n / 2; i >= 1; i--) {
//		int t = 2 * i - 1;
//		for (j = 1, k = 0; j <= t; j++, k++) {
//			if (j <= (t / 2) + 1)
//				printf("%d", j);
//			else {
//				printf("%d", t - k);
//			}
//		}
//		putchar('\n');
//	}
	return 0;
}
