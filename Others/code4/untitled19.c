#include <stdio.h>

int gcd(int x, int y)
{
	if (y == 0) {
		return x;
	}

	return (x % y) != 0 ? gcd(y, x % y) : y;
}

int lcm(int x, int y)
{
	return (x * y) / gcd(x, y);
}

int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	printf("最大公约数%d\n最小公倍数%d\n", gcd(a, b), lcm(a, b));
	return 0;
}
