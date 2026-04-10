#include <stdio.h>

int main()
{
	int n, m, k;
	scanf("%d%d", &n, &m);

	int p = n * m;

	if (n > m) {
		int tmp = n;
		n = m;
		m = tmp;
	}

	while (k = n % m) {
		n = m;
		m = k;
	}

	printf("最大公因数%d\n最小公倍数%d\n", m, p / m);
	return 0;
}

