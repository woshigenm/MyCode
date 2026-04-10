#include <stdio.h>
//【求最值】输入三个整数a,b,c,输出其中的最大数和最小数。

void swap(int * a, int * b);

int main()
{
	int a, b, c, d;

	scanf("%d%d%d%d", &a, &b, &c, &d);

	if (a > b) swap(&a, &b);
	if (a > b) swap(&a, &b);
	if (a > c) swap(&a, &c);
	if (a > d) swap(&a, &d);
	if (b > c) swap(&b, &c);
	if (b > d) swap(&b, &d);
	if (c > d) swap(&c, &d);


	printf("从小到大为%d %d %d %d", a, b, c, d);
	return 0;
}

void swap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
