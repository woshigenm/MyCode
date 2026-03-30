//【质数的判定】输入任意一个正整数，判断它是否是质数，输入输出形式如下。

#include <stdio.h>

int main()
{
	int n;
	scanf("%d", &n);

	if(n <= 1)
	{
		printf("%d不是质数\n", n);
		return 0;
	}
	int i;
	for(i = 2; i <= n / i; i++)
	{
		if(n % i == 0)	break;
	}

	if(i > n / i)
	{
		printf("%d是质数\n", n);
	}
	else
	{
		printf("%d不是质数\n", n);
	}
	return 0;
}
