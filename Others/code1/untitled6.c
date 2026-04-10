#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i, j, tmp;

	int n, k;
	printf("输入数组长度 n: ");
	scanf("%d", &n);

	int *array = (int *)malloc(sizeof(int) * n);
	printf("输入数组%d个元素： ", n);
	for (int i = 0; i < n; i++) {
		scanf("%d", array + i);
	}

	printf("输入移位次数 k: ");
	scanf("%d", &k);

	//左移k位
	for (i = 1; i <= k; i++) {
		tmp = array[0];
		for (j = 0; j < n - 1; j++) {
			array[j] = array[j + 1];
		}

		array[n - 1] = tmp;
	}

	printf("移位后的数组元素为：");
	for (i = 0; i < n; i++) {
		printf("%d ", array[i]);
	}

	putchar('\n');

	//右移k位
	for (i = 1; i <= k; i++) {
		tmp = array[n - 1];
		for (j = n - 1; j > 0; j--) {
			array[j] = array[j - 1];
		}

		array[0] = tmp;
	}

	printf("移位后的数组元素为：");
	for (i = 0; i < n; i++) {
		printf("%d ", array[i]);
	}

	free(array);

	return 0;
}

