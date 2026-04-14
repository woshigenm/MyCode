#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 45

int fbi(int x)
{
	if (x == 1 || x == 2)	return 1;
	return fbi(x - 1) + fbi(x - 2);
}

long long int palouti(int x)
{
	if (x == 1) return 1;
	if (x == 2)	return 2;
	if (x == 3)	return 4;

	return palouti(x - 1) + palouti(x - 2) + palouti(x - 3);
}

int main()
{
	int i, j, sum, m, n;

	sum = 0;

	for (i = 1; i <= SIZE; i++) {
		j = (sqrt(5) / 5.0) * (pow((1 + sqrt(5)) / 2.0, i) - pow((1 - sqrt(5)) / 2.0, i));
		printf("%d ", j);
		sum += j;
	}

	printf("\nsum = %d\n", sum);

	int array[SIZE] = {1, 1};

	sum = array[0] + array[0];
	printf("%d %d ", array[0], array[1]);

	for (i = 2; i < SIZE; i++) {
		array[i] = array[i - 1] + array[i - 2];
		printf("%d ", array[i]);
		sum += array[i];
	}

	printf("\nsum = %d\n", sum);

	sum = 0;
	m = 1, n = 1;
	sum += m + n;

	printf("%d %d ", m, n);

	for (i = 3; i <= SIZE; i++) {
		j = m + n;
		sum += j;
		printf("%d ", j);
		m = n;
		n = j;
	}

	printf("\nsum = %d\n", sum);

	sum = 0;

	for (i = 1; i <= SIZE; i++) {
		int n = fbi(i);
		sum += n;
		printf("%d ", n);
	}

	printf("\nsum = %d\n", sum);

	printf("%lld\n",  palouti(24));
	return 0;
}

