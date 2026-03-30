#include <stdio.h>

int main() {
	int n, sum = 0, sums = 0;
	scanf("%d", &n);

//	if (n <= 0) {
//	printf("Error");
//	} else {
//	for (int i = 1; i <= n; i++) {
//	for (int j = 1; j <= i; j++) {
//	sum += j;
//	}
//	}
//	printf("%d\n", sum);
//	}

	if (n <= 0) {
		printf("Error");
	} else {
		for (int i = 1; i <= n; i++) {
			sum += i;
			sums += sum;
		}
		printf("%d\n", sums);
	}
	return 0;
}
