#include <stdio.h>

#define SIZE 10

int main() {
	int array[SIZE];

	for(int i = 0; i < SIZE; i++)
		scanf("%d", &array[i]);

	int t;
	for(int i = 1; i < SIZE; i++) {
		for(int j = 0; j < SIZE - i; j++) {
			if(array[j] > array[j + 1]) {
				t = array[j];
				array[j] = array[j + 1];
				array[j + 1] = t;
			}
		}
	}
	
	for(int i = 0; i < SIZE; i++)
		printf("%d ", array[i]);
	return 0;
}

