#include <stdio.h>
#include <math.h>

#define N 10

int main() {
	double arr[N];
	int i, j, k;

	double sum = 0.0, avg;
	for (i = 0; i < N; i++) {
		scanf("%lf", &arr[i]);
		sum += arr[i];
	}

	avg = sum / N;
	double min = fabs(avg - arr[0]);

	for (j = 1; j < N; j++) {
		if (fabs(avg - arr[j]) < min) {
			min = fabs(avg - arr[j]);
		}
	}

	for (k = 0; k < N; k++) {
		if (fabs(avg - arr[k]) == min)
			printf("最近它们平均的数是:%f,位置在:%d\n", arr[k], k + 1);
	}

	return 0;
}

