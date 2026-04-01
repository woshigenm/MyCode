#include <stdio.h>
#define SIZE 10

void swap(int * a, int * b);

int main() {
	int array[SIZE];
	int arr[SIZE];
	int i, j;

	while (scanf("%d", &array[0]) != EOF) {
		for (i = 1; i < SIZE; i++)
			scanf("%d", &array[i]);

		j = 0;
		for (i = 0; i < SIZE; i++) {
			if (array[i] % 2 != 0) {
				arr[j++] = array[i];
			}
		}

		int fanxiaochao = j;

		for (i = 0; i < SIZE; i++) {
			if (array[i] % 2 == 0) {
				arr[j++] = array[i];
			}
		}

		int m;
		for (i = 1; i < fanxiaochao; i++) {
			m = 0;
			for (j = 0; j < fanxiaochao - i; j++) {
				if (arr[j] < arr[j + 1]) {
					swap(&arr[j], &arr[j + 1]);
					m = 1;
				}
			}
			if (!m) break;
		}


		for (i = 1; i < SIZE; i++) {
			m = 0;
			for (j = fanxiaochao; j < SIZE - i; j++) {
				if (arr[j] > arr[j + 1]) {
					swap(&arr[j], &arr[j + 1]);
					m = 1;
				}
			}

			if (!m) break;
		}

		for (int i = 0; i < SIZE; i++) {
			printf("%d ", arr[i]);
		}
		putchar('\n');
	}
	return 0;
}

void swap(int * a, int * b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
