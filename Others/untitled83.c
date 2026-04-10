#include <stdio.h>

#define SIZE 10

int main()
{
	int array[SIZE];

	for (int i = 0; i < SIZE; i++)
		scanf("%d", &array[i]);

	for (int i = 0; i < SIZE - 1; i++) {
		int index = i;
		for (int j = i + 1; j < SIZE; j++) {
			if (array[index] > array[j]) {
				index = j;
			}
		}

		if (index != i) {
			int t = array[i];
			array[i] = array[index];
			array[index] = t;
		}
	}

	for (int i = 0; i < SIZE; i++)
		printf("%d ", array[i]);
	return 0;
}

