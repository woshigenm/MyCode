/*
【π的值】编程实现求π的近似值，公式π/4=1-1/3+1/5-1/7... 直到发现某一项的绝对值小于10的6次方为止。
*/
#include <stdio.h>

int main()
{
	float sum = 0.0;
	int tn = 1;
	int an = 1;

	while (1.0 / an >= 1E-6) {
		sum += 1.0 / an * tn;
		tn = -tn;
		an += 2;
	}

	printf("pi=%f\n", 4 * sum);

	return 0;
}
