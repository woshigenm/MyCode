#include <stdio.h>

void print(int x)
{
	int r;
	r = x % 2;
	if (x >= 2) {
		print(x / 2);
	}

	putchar(r == 0 ? '0' : '1');
}

int main()
{
	int k = 24;
	print(k);
	putchar('\n');

	int t = k;

	int sum = 0;
	int e = 1;
	while (t != 0) {
		sum = sum + (t % 2) * e;
		t /= 2;
		e *= 10;
	}

	printf("%d\n", sum);
	return 0;
}

void Binary()
{
	int k = 1 << 14;

	int array[128] = {};
	int t = k;

	int i = 0;
	while (t != 0) {
		if (t % 2 == 1) {
			array[i] = 1;
		}
		i++;
		t /= 2;
	}

	for (int j = i - 1, m = 1; j >= 0; j--, m++) {
		printf("%d", array[j]);
		if (m % 4 == 0) {
			putchar(' ');
		}
	}
}
