#include <stdio.h>
#include <stdlib.h>

int main() {
	int i, j, n = 10;

	int * array = (int *)malloc(sizeof(int) * n);
	array[0] = 3;
	array[1] = 5;

	for (i = 2; i < n; i++) {
		int sum = array[i - 1] * array[i - 2];
		if (sum / 10 > 0) { // 两位数
			array[i] = sum / 10;
			array[i + 1] = sum % 10;
			i++;
		} else { // 一位数
			array[i] = sum;
		}
	}

	int sum = 0;
	for (int i = 0; i < n; i++) {
		printf("%d ", array[i]);
		sum += array[i];
	}

	printf("\nsum=%d\n", sum);
	return 0;
}
