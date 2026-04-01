#include <stdio.h>
#include <math.h>

int main() {
	int n;
	scanf("%d", &n);

	int i, j, k, h;

	for (i = 1; i <= n; i++) {

		for (j = 1; j <= abs((n - (2 * i - 1)) / 2); j++) {
			printf(" ");
		}

		for (k = 1; k <= abs(n - 2 * (j - 1)); k++) {
			putchar('#');
		}
		putchar('\n');
	}

	h = n / 2 + 1;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= abs(h - i); j++) {
			putchar(' ');
		}

		for (k = 0; k < abs(n - 2 * (j - 1)); k++) {
			putchar('*');
		}
		putchar('\n');
	}

	for (i = 1; i <= n / 2; i++) {
		for (j = n / 2; j >= i; j--) {
			printf(" ");
		}

		for (k = 1; k <= 2 * i - 1; k++) {
			putchar('@');
		}
		putchar('\n');
	}

	for (i =  n / 2; i >= 1; i--) {
		for (j = n / 2; j >= i; j--) {
			putchar(' ');
		}

		for (k = 1; k <= 2 * i - 1; k++) {
			putchar('@');
		}
		putchar('\n');
	}
	return 0;
}
