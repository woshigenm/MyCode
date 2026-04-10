#include <stdio.h>
#include <math.h>

#define SIZE 3

int main()
{
	int array[SIZE][SIZE];

	int a, b;

	int sums = 0, sum = 0;
	for (a = 0; a < SIZE; a++) {
		for (b = 0; b < SIZE; b++) {
			scanf("%d", &array[a][b]);
		}
	}

	for (a = 0; a < SIZE; a++) {
		for (b = 0; b < SIZE; b++) {
			if (a + b == 2) {
				sums += array[a][b];
			}

			if (a == b) {
				sum += array[a][b];
			}
		}
	}

	printf("%d %d\n", sum, sums);
	return 0;
}


