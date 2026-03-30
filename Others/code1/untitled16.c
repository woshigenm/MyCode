#include <stdio.h>

int main()
{
	int n,m;
	
	scanf("%d", &n);
	
	int sum = 0;
	
	for(m = 1; m < n; m++)
	{
		if(n % m == 0)
		{
			sum += m;
		}
	}
	
	if(sum == n)
	{
		printf("%d是完数\n", n);
	}
	return 0;
}

