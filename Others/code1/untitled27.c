#include <stdio.h>

int main()
{
	
	int a, n, i;
	
	printf("输入a: ");
	scanf("%d", &a);
	printf("输入n: ");
	scanf("%d", &n);
	
	int an, sum = 0;
	
	for(i = 1; i < n; i++)
	{
		an = add(i, a);
		printf("-%d ", an);
		sum += -an;
	}
	
	an = add(i, a);
	sum += an;
	
	printf("+ %d\n", an);
	printf("sum = %d\n", sum);
	
	sum = 0;
	
	an = 0;
	
	for(i = 1; i < n; i++)
	{
		an = an * 10 + a;
		printf("-%d ", an);
		sum += -an;
	}
	an = an * 10 + a;
	printf("+ %d\n", an);
	
	sum += an;
	printf("sum = %d\n", sum);
	
	return 0;
}

