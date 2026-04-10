#include <stdio.h>

int gcd(int x, int y)
{
	return (x % y) == 0 ? y : gcd(y, x % y);
}

int lcm(int x, int y)
{
	return x * y / gcd(x, y);
}

int main()
{
	int x, y;
	scanf("%d%d", &x, &y);
	printf("最大公约数%d\n最小公倍数%d\n", gcd(x, y), lcm(x, y));
	return 0;
}
