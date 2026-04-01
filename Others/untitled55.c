#include <stdio.h>
#include <stdlib.h>

void swap(int * a, int * b);

int main() {
	int N;
	scanf("%d", &N);

	int * array = (int *)malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &array[i]);
	}

	int i, j, k;

	int c = 0;
	for (i = 0; i < N - c; i++) {
		for (j = i + 1; j < N - c; j++) {
			if (array[i] == array[j]) {
				c++;

				for (k = j; k < N - c; k++) {
					array[k] = array[k + 1];
				}
			}
		}
	}

	printf("%d\n", N - c);

	int yuanshen;
	for (int i = 1; i < N - c; i++) {
		yuanshen = 1;
		for (int j = 0; j < N - c - i; j++) {
			if (array[j] > array[j + 1]) {
				swap(&array[j], &array[j + 1]);
				yuanshen = 0;
			}
		}

		if (yuanshen) {
			break;
		}
	}

	for (int i = 0; i < N - c; i++) {
		printf("%d ", array[i]);
	}
	return 0;
}

void swap(int * a, int * b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
