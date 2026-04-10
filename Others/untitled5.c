#include <stdio.h>
#include <stdarg.h>

//交换函数
void swap(int * x, int * y);

//辗转相除法求最大公约数(递归)
int gcd(int x, int y);

//辗转相除法求最大公约数(迭代)
int gcd1(int x, int y);

//辗转相减法求最大公约数(迭代)
int gcd2(int x, int y);

//辗转相减法求最大公约数(递归)
int gcd3(int x, int y);

//最小递减法求最大公约数
int gcd4(int x, int y);

//辗转相减法求最大公约数(三数)
int gcd5(int x, int y, int z);

//最大递增法求最小公倍数
int lcm(int x, int y);

//最大递增法求最小公倍数
int lcm3s(int x, int y, int z);

//定义法求最小公倍数
int lcm1(int x, int y);

#define TEST1 24
#define TEST2 12

int main()
{
	int a = TEST1, b = TEST2;
	printf("%d 和 %d 的 最大公约数为 %d\n", a, b, gcd(a, b));
	printf("%d 和 %d 的 最大公约数为 %d\n", a, b, gcd1(a, b));
	printf("%d 和 %d 的 最大公约数为 %d\n", a, b, gcd2(a, b));
	printf("%d 和 %d 的 最大公约数为 %d\n", a, b, gcd3(a, b));
	printf("%d 和 %d 的 最大公约数为 %d\n", a, b, gcd4(a, b));
	printf("%d 和 %d 的 最小公倍数为 %d\n", a, b, lcm(a, b));
	printf("%d 和 %d 的 最小公倍数为 %d\n", a, b, lcm1(lcm1(13, 15), 125));
	return 0;
}

void swap(int * x, int * y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

int gcd(int x, int y)
{
	//gcd(x, 0) = x
	if (y == 0)	return x;
	return (x % y) != 0 ? gcd(y, x % y) : y;
}

int gcd1(int x, int y)
{
	int z;
	while (z = x % y) {
		x = y;
		y = z;
	}

	return y;
}

int gcd2(int x, int y)
{
	while (x != y) {
		if (x > y) {
			x = x - y;
		} else {
			y = x - y;
		}
	}

	return x;
}

int gcd3(int x, int y)
{
	if (x < y)	swap(&x, &y);
	//gcd(x, 0) = x
	if (y == 0)	return x;
	//x为最大
	return (x != y) ? gcd3(y, x - y) : x;
}

int gcd4(int x, int y)
{
	int i;
	for (i = (x > y) ? y : x; i >= 1; i--) {
		if (x % i == 0 && y % i == 0) {
			return i;
		}
	}
}

int lcm(int x, int y)
{
	for (int i = (x > y) ? x : y; i <= x * y; i++) {
		if (i % x == 0 && i % y == 0) {
			return i;
		}
	}
}

int lcm1(int x, int y)
{
	//注意gcd(x,y)为x,y的最大公约数
	return (x * y) / gcd(x, y);
}

int gcd5(int x, int y, int z)
{
	//gcd(x, gcd(y, z)) 与 gcd(y, gcd(x, z)) 与 gcd(z, gcd(x, y)) 等价
	return gcd(x, gcd(y, z));
}

int lcm3s(int x, int y, int z)
{
	return lcm1(lcm1(x, y), z);
}

