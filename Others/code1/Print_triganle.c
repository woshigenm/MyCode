#include <stdio.h>

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int k = 1; k <= 2 * i - 1; k++)
			if (k == 1 || k == 2 * i - 1 || i == n) {
				putchar('*');
			} else
				putchar(' ');

		putchar('\n');
	}

	return 0;
}
