#include <stdio.h>

int main()
{

	long long i, k;

	k = 10;

	for (i = 0; i <= 200000; i++) {
		if (i / k > 0)
			k *= 10;

		if ((i * i) % k == i) {
			printf("%lld  ", i);
		}
	}
	return 0;
}
