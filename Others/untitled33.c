//求斐裂波数列 1 1 2 3 5……的第20项，以及前20项的和，输入输出形式如下。
#include <stdio.h>

#define SIZE 20

int main() {
	int array[SIZE] = {1, 1};
	int sum = array[0] + array[1];

	for (int i = 2; i < SIZE; i++) {
		array[i] = array[i - 1] + array[i - 2];
		sum += array[i];
	}

	printf("第20项是%d\n前20项的和是%d\n", array[SIZE - 1], sum);
	return 0;
}
