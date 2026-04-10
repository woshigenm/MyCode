#include <stdio.h>

long long int palouti(int x)
{
	if (x == 1)	return 1;
	if (x == 2)	return 2;
	if (x == 3)	return 4;

	return palouti(x - 1) + palouti(x - 2) + palouti(x - 3);
}

#define SIZE 46

int main()
{
	int n, i;
	printf("输入一个整数n,(1<=n<46): ");

	scanf("%d", &n);

	printf("上楼方式总数是%lld\n", palouti(n));

	long long int array[SIZE] = {1, 2, 4};

	for (i = 3; i < n; i++) {
		array[i] = array[i - 1] + array[i - 2] + array[i - 3];
	}

	printf("上楼方式总数是%lld\n", array[n - 1]);

	long long int a, b, c, d;

	a = 1, b = 2, c = 4;

	for (i = 3; i < n; i++) {
		d = a + b + c;
		a = b;
		b = c;
		c = d;
	}
	printf("上楼方式总数是%lld\n", d);

	return 0;
}

