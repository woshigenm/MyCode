#include <stdio.h>
#include <math.h>

int main() {
	int n;
	scanf("%d", &n);

	int e = 10;
	printf("1到%d之间符合特征的正整数有\n", n);

	int c = 0;
	for (int i = 1; i <= n; i++) {
		int t = i * i * i;

		if (i / e > 0)
			e *= 10;

		if (t % e == i) {
			printf("%d ", i);
			c++;
		}
	}

	return 0;
}
