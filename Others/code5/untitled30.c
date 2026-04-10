#include <stdio.h>
#include <math.h>

int main()
{
	int an;
	long long sum = 0;
	for (int i = 1; i <= 9; i++) {
		an = (pow(10, i) - 1) / 9 * i;
		sum += an;
		printf("%d -> %d S1= %.0f S2=%lld\n", i, an, (double)(pow(10, i + 1) * (9 * i - 1) + 10 - (float)81 / 2 * i * (i + 1)) / 729, sum);
	}
}
