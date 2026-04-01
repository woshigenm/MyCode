#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 10

int main() {
	int i, j;

	int array[SIZE];

	for (i = 0, j = 2; i < SIZE; i++, j += 2) {
		array[i] = j;
	}

	for (i = 0; i < SIZE; i++) {
		printf("%d ", array[i]);
	}

	putchar('\n');

	for (i = 0; i < SIZE / 2; i++) {
		int tmp = array[i];
		array[i] = array[SIZE - i - 1];
		array[SIZE - i - 1] = tmp;
	}

	for (i = 0; i < SIZE; i++) {
		printf("%d ", array[i]);
	}
	return 0;
}

