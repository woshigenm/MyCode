#include <stdio.h>

#define SIZE 100

int main()
{
	int i, j, k;

	int array[SIZE + 1] = {1, 1};

	for (i = 2; i * i <= SIZE; i++) {
		if (!array[i]) {
			//i * 2
			for (k = i * i; k <= SIZE; k += i)	array[k] = 1;
		}
	}

	for (i = 1; i < SIZE; i++) {
		if (!array[i]) {
			printf("%d ", i);
		}
	}
}

