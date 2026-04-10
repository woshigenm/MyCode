#include <stdio.h>

//已有一个已正序排好的9个元素的数组，今输入一个数要求按原来排序的规律将它插入数组中。
#define SIZE 10

int main()
{
	int array[SIZE];

	int k;

	for (int i = 0; i < SIZE - 1; i++)
		scanf("%d", &array[i]);

	scanf("%d", &k);

	int i, j;
	for (i = 0; i < SIZE; i++) {
		if (k < array[i]) {
			for (j = SIZE - 1; j >= i; j--) {
				array[j] = array[j - 1];
			}

			array[i] = k;

			break;
		}
	}

	if (i == SIZE) {
		array[SIZE - 1] = k;
	}

	for (int i = 0; i < SIZE; i++) {
		printf("%d\n", array[i]);
	}
	return 0;
}
