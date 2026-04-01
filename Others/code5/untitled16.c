#include <stdio.h>
#include <math.h>

int main() {
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
				putchar('A' + j - 1);
			else {
				putchar('A' + t - m - 1);
			}
		}
		putchar('\n');
	}

	return 0;
}
