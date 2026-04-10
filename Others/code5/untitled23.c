#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5

int main()
{
	srand((unsigned)time(NULL));
	int ranom_number = rand() % 101;

	int input;
	int count = 0;
	while (count < N) {
		printf("请输入: ");
		scanf("%d", &input);
		count++;

		if (input > ranom_number)
			printf("太大了\n");

		if (input == ranom_number) {
			printf("你猜对了\n");
			break;
		}

		if (input < ranom_number)
			printf("太小了\n");

		printf("你还剩%d次机会\n", N - count);
	}

	if (count == N)
		printf("你失败了\n");
	else
		printf("你一共用了%d次\n", count);
}
