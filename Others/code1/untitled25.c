#include <stdio.h>

int main()
{
	int n;
	scanf("%d", &n);

	int m = n;
	int s = n * n;

	while(m)
	{
		if(m % 10 != s % 10)
		{
			break;
		}
		m /= 10;
		s /= 10;
	}
	
	if(m != 0)
	{
		printf("%d不是同构数\n", n);
	}else
	{
		printf("%d是同构数\n", n);
	}
	return 0;
}
