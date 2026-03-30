#include <stdio.h>
#include <stdlib.h>

#define SIZE1 4
#define SIZE2 4
int main() {
	int array1[SIZE1] = {1, 3, 5, 7};
	int array2[SIZE2] = {5, 6, 7, 8}; //1 3 5 6 7 8
	int * array3 = (int *)malloc(sizeof (int) * (SIZE1 + SIZE2));
	int i, j, k;
	i = j = k = 0;

	for (i = 0; i < SIZE1; i++)
		array3[k++] = array1[i];
	for (i = 0; i < SIZE2; i++)
		array3[k++] = array2[i];

	for (int i = 1; i < SIZE1 + SIZE2; ++i) {
		int p = 0;
		for (int j = 0; j < SIZE1 + SIZE2 - i; j++) {
			if (array3[j] > array3[j + 1]) {
				array3[j] = array3[j] ^ array3[j + 1];
				array3[j + 1] = array3[j] ^ array3[j + 1];
				array3[j] = array3[j] ^ array3[j + 1];
				p = 1;
			}
		}
		if (!p) break;
	}

	int length = SIZE1 + SIZE2;
	k = 0;
	for (int i = 0; i < length; ++i) {
		for (int j = i + 1; j < length - k; ++j) {
			if (array3[i] == array3[j]) {
				k++;
				for (int p = i; p < length - k; p++) {
					array3[p] = array3[p + 1];
				}
			}
		}
	}

	for (int i = 0; i < SIZE1 + SIZE2 - k; ++i)
		printf("%d ", array3[i]);

	putchar('\n');

	i = j = k = 0;
	while (i < SIZE1 && j < SIZE2) {
		if (array1[i] < array2[j]) {
			array3[k++] = array1[i++];
		} else if (array1[i] > array2[j]) {
			array3[k++] = array2[j++];
		} else {
			array3[k++] = array1[i++];
			j++;
		}
	}

	while (i < SIZE1) {
		array3[k++] = array1[i++];
	}

	while (j < SIZE2) {
		array3[k++] = array2[j++];
	}


	for (int p = 0; p < k; p++)
		printf("%d ", array3[p]);

	free(array3);

	return 0;
}

