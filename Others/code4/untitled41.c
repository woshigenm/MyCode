//【存储数组元素】把1-200中各位之和是10的数依次存储在数组a中，
//并输出所有的数，以及这样的数有多少个？按如下输入输出格式输出。
#include <stdio.h>

#define SIZE 128

int main()
{
	int i, j, sum, k = 0;

	int array[SIZE];

	for (i = 1; i <= 200; i++) {
		sum = 0;
		j = i;
		while (j) {
			sum += j % 10;
			j /= 10;
		}

		if (sum == 10) {
			array[k++] = i;
		}
	}

	for (i = 0; i < k; i++) {
		printf("%d ", array[i]);
	}

	printf("\n共有%d个\n", k);

	return 0;
}
