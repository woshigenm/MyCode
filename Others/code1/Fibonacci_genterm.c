#include <stdio.h>
#include <math.h>

float Fbi(int x)
{
	return (sqrt(5) / 5) * (pow((sqrt(5) + 1) / 2, x) - pow((1 - sqrt(5)) / 2, x));
}
int main()
{
	float sum = 0.0;

	int i;

	int n;
	scanf("%d", &n);

	//2/1 3/2 5/3 8/5 13/8 21/13
	for (i = 1; i <= n; i++) {
		sum += Fbi(i + 2) / Fbi(i + 1);
	}

	printf("%.2f\n", sum);
	return 0;
}
