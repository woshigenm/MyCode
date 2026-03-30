#include <stdio.h>

int main()
{
	float height = 100.0;

	float sum_ball = height;

	int i = 1;

	while(1)
	{
		height *= 3.0 / 4;
		sum_ball += height * 2;
		if(sum_ball >= 590.0)	break;
		i++;
	}

	printf("最大次数%d\n", sum_ball, i);

	return 0;
}
