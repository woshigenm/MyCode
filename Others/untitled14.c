#include <stdio.h>

int main() {
	int n = 10;

	int i, j = 10, k;
	printf("1到%d之间符合特征的正整数有\n", n);
	
	int l = 0;
	
	for(i = 1; i <= n; i++) 
	{
		k = i * i * i;
		if(i / j > 0)
			j *= 10;
		if(k % j == i)
		{
			printf("%d ", i);
			l++;
		}
	}
	
	printf("\n总数%d个", l);
	return 0;
}
