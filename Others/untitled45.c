#include <stdio.h>

int main()
{
	float money, r;

	scanf("%f", &money);

	switch ((int)money / 500)
	{
		case 1:
			r = 0.05;
			break;
		case 2:
		case 3:
			r = 0.08;
			break;
		case 4:
		case 5:
			r = 0.10;
			break;
		default :
			r = 0.15;
	}

	printf("实得奖金%.2f元钱\n", money - money * r);
	return 0;
}
