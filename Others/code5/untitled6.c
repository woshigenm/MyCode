#include <stdio.h>

#define N 100

int main()
{
	int array[N + 1] = {};
	for (int i = 2; i <= N; i++) {
		if (!array[i]) {
			for (int j = i * i; j <= N; j += i)
				array[j] = 1;
		}
	}

	for (int i = 2; i <= N; i++) {
		if (!array[i]) {
			array[0] += i;
			printf("%d ", i);
		}
	}

	printf("\n%d\n", array[0]);

	return 0;
}
