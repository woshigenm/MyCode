/*
【最值求解】从键盘上输入若干个整数，正负数都可以，不包括-1，-1作为结束标志，
输出其中的最大数和最小数，以及平均数（保留两位小时），按下列格式输入输出。
*/
#include <stdio.h>

int main()
{
	int input;

	float sum = 0.0;
	scanf("%d", &input);
	if (input == -1) {
		printf("开始-1结束\n");
		return 0;
	}

	sum = input;

	int max, min;
	max = min = input;

	int count = 1;

	while (input != -1) {
		scanf("%d", &input);

		if (input == -1)	break;

		if (input > max) {
			max = input;
		}

		if (input < min) {
			min = input;
		}

		sum += input;
		count++;
	}

	printf("max=%d,min=%d,ave=%.2f\n", max, min, (sum) / (count));
	return 0;
}
