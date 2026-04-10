//1^3+2^3+...+m^3 <= n
#include <stdio.h>

int main()
{
	int n, m = 1;
	scanf("%d", &n);

	int sum = 0;
	while (1) {
		sum += m * m * m;
		if (sum > n) {
			break;
		}
		m++;
	}

	printf("%d\n", m - 1);

	return 0;
}
