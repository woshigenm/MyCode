#include <stdio.h>

int main() {
	int i, j;
	for (i = 9; i >= 1; i--) {
		for (j = 1; j <= i; j++)
			printf("%d*%d=%-2d ", i, j, i * j);
		putchar('\n');
	}

	return 0;
}
