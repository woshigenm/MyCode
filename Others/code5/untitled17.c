#include <stdio.h>
#include <math.h>

int main()
{
	int i;
	float a[10], avg, s = 0, x, min;

	for (i = 0; i < 10; i++)
		scanf("%f", &a[i]);
	for (i = 0; i < 10; i++)
		s = s + a[i];

	avg = s / 10;
	min = fabsf(avg - a[0]); //求两个数之差的绝对值
	for (i = 1; i < 10; i++) {
		x = fabsf(avg - a[i]);
		if (x <= min)
			min = x;
	}

	for (i = 0; i < 10; i++)
		if (fabsf(avg - a[i]) == min)
			printf("最近它们平均的数是:%f,位置在:%d\n", a[i], i + 1);
}
