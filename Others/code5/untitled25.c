#include <stdio.h>

int main()
{
	int i, j;
	scanf("%d", &i);
	int sum;

	int count = 1;
	for (i = 1; i < 1000; i++) {
		sum = 1;
		for (j = 2; j * j <= i; j++) {
			if (i % j == 0) {
				sum += j;
				if (j * j != i) {
					sum += i / j;
				}
			}
		}

		if (sum == i) {
			printf("%d ", i);
		}
	}

	return 0;
}

