#include <stdio.h>

int main()
{
	int n;

	float m;
	scanf("%d%f", &n, &m);

	float all = n * m;

	if (all > 100.0 && all < 200.0) {
		all *= 0.9;
	} else if (all >= 200.0 && all < 400.0) {
		all *= 0.85;
	} else if (all >= 400.0) {
		all *= 0.7;
	}

	printf("%d人 每个人一个苹果要%.2f元\n", n, all / n);
	return 0;
}
