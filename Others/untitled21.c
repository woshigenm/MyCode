#include <stdio.h>

//【1+22+333+4444+……的和】编程实现1+22+333+4444+55555+……nn……n(n<=9)的和
int main()
{
	int i, j, n;
	scanf("%d", &n);

	int sum = 0;

	int an;
	for (i = 1; i <= n; i++) {
		an = 0;
		for (j = 1; j <= i; j++) {
			an = an * 10 + i;
		}
		sum += an;
	}

	printf("%d\n", sum);
	return 0;
}
