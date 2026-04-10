#include <stdio.h>

#define SIZE 100

int main()
{
	int array[SIZE + 1] = {1, 1};

	for (int i = 2; i * i <= SIZE; i++) {
		if (!array[i]) {
			for (int j = i * i; j <= SIZE; j += i) {
				array[j] = 1;
			}
		}
	}

	for (int i = 2; i <= SIZE; i++) {
		if (!array[i]) {
			printf("%d ", i);
		}
	}
	return 0;
}

