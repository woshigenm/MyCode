#include <stdio.h>

#define N 11

int main() {
	float input[N];
	scanf("%f", &input[1]);

	float min, max;
	input[0] = min = max = input[1];
	for (int i = 2; i < N; i++) {
		scanf("%f", &input[i]);

		if (input[i] < min)	min = input[i];
		if (input[i] > max)	max = input[i];

		input[0] += input[i];
	}

	printf("%.2f\n", (input[0] - max - min) / 8);
	return 0;
}
