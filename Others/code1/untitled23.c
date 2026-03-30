#include <stdio.h>

int main()
{
	float i;
	scanf("%f", &i);
	float max, sum = i;
	int count = 1;

	max = i;

	while(i != -1.0)
	{
		scanf("%f", &i);
		if(i > max)
		{
			max = i;
		}

		sum += i;

		count++;
	}

	sum += 1;

	printf("max -> %f avg -> %f\n", max, sum / (count - 1));

	return 0;
}
