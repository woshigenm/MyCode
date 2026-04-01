#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

typedef int (*fp)(const void * a, const void * b);

int compare(const void * a, const void * b);

int main() {
	int i, j, k;
	int array[SIZE];
	srand((unsigned int)time(NULL));

	int a = 1, b = 100;
	for (i = 0; i < SIZE; i++) {
		array[i] = 	rand() % (b - a + 1) + a;
	}

	for (i = 0; i < SIZE; i++) {
		printf("%d ", array[i]);
	}

	putchar('\n');

	qsort(array, SIZE, sizeof(int), compare);

	for (i = 0; i < SIZE; i++) {
		printf("%d ", array[i]);
	}

	return 0;
}

int compare(const void * a, const void * b) {
	return *((int*)a) - *((int*)b);
}
