#include <stdio.h>

int main() {
	int input;

	scanf("%d", &input);

	if (input == -1) {
		printf("不要一来就输-1!!!\n");
		return 0;
	}

	int max, min;
	max = min = input;
	int sum = input;

	int i = 1;
	while (1) {
		scanf("%d", &input);
		if (input == -1)	break;
		sum += input;
		if (input > max)	max = input;
		if (input < min)	min = input;
		i++;
	}

	printf("MAX -> %d MIN -> %d AVG -> %f\n", max, min, (float)sum / i);
	return 0;
}

