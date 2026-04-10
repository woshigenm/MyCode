#include <stdio.h>

#define SIZE 12

void swap(int * a, int * b);

int main()
{
//	int array[SIZE] = {73, 85, 60, 75, 26, 58, 6, 64, 64, 10, 7, 70};
//
//	int i, j, t;
//	for(i = 1; i < SIZE; i++) {
//		j = i - 1;
//		t = array[i];
//		while((j >= 0) && (array[j] < t)){
//			array[j + 1] = array[j];
//			j--;
//		}
//
//		array[j + 1] = t;
//	}

	printf("%d\n", 036);
	return 0;
}

void SelectSort(int array[])
{
	int i, j, minindex;

	for (i = 0; i < SIZE - 1; i++) {
		minindex = i;
		for (j = i + 1; j < SIZE; j++) {
			if (array[j] > array[minindex]) {
				minindex = j;
			}
		}

		if (minindex != j) {
			swap(&array[i], &array[minindex]);
		}
	}
}

void swap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
