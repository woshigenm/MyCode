#include <stdio.h>

int sumOfDivisors (int x)
{
	int sum = 1;

	for (int i = 2; i <= x / 2; i++) {
		if (x % i == 0) sum += i;
	}

	return sum;
}
int main()
{
	int m, a, b;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &a, &b);
		int first = sumOfDivisors (a);
		int second = sumOfDivisors (first);

		if (second == a && second < first) {
			printf("YES\n");
		} else printf("NO\n");
	}
	return 0;
}

