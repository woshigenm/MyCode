//一个球从100m高度自由落下,每次落地后反跳回原来高度的一半,再落下,再反弹.求它在第N次落地时共经过多少米?
#include <stdio.h>

int main()
{
	float sum_all = 0.0;
	float next = 100.0;
	int N;
	scanf("%d", &N);
	sum_all = next;
	
	for(int i = 2; i <= N; i++)
	{
		next /= 2;
		sum_all += next * 2;
	}
	
	printf("%.4f\n", sum_all);
	
	return 0;
}
