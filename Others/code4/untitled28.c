/*
【同构数】输出1到500之间的同构数。（如果一个数全部出现在这个数平方的右端，这个数就是同构数，例如25的平方625，25是同构数）
*/
#include <stdio.h>

int main()
{
	int i;
	
	int k = 1;
	for(i = 1; i <= 500; i++)
	{
		int m = i * i;
		if(i / k > 0)
		{
			k *= 10;
		}
		
		if(m % k == i)
		{
			printf("%d ", i);
		}
	}
	return 0;
}
