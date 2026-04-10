#include<stdio.h>

#define SIZE 3

void swap(int * a, int * b);

int main()
{
	int array[SIZE][SIZE];
	int arr[SIZE][SIZE];

	int a, b;

	for (a = 0; a < SIZE; a++) {
		for (b = 0; b < SIZE; b++) {
			scanf("%d", &array[a][b]);
		}
	}

	for (a = 0; a < SIZE; a++) {
		for (b = 0; b < SIZE; b++) {
			//arr[a][b] = array[b][a];
			swap(&array[a][b], &array[b][a]);
		}
	}

	for (a = 0; a < SIZE; a++) {
		for (b = 0; b < SIZE; b++) {
			printf("%d ", array[a][b]);
		}
		putchar('\n');
	}
	return 0;
}

void swap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

