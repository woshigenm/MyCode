/*
【完数的判定】求1000以内所有的完数。（完数就是一个整数，除他本身之外，因子和等于他本身，例如6=1+2+3,6是完数），
输入输出形式如下。*/
#include <stdio.h>

int main()
{
	int i,j,sum;
	
	printf("1000以内的完数有");
	for(i = 1; i <= 1000; i++)
	{
		sum = 0;
		for(j = 1; j < i; j++)
		{
			if(i % j == 0)
			{
				sum += j;
			}
		}
		
		if(sum == i)
		{
			printf("%d ", i);
		}
	}
	return 0;
}
