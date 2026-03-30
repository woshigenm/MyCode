#include <stdio.h>

int main() {
	int k = 120;

	int i, j = k;

	for(i = 2; i <= k / i; i++) {
		if(k % i == 0)	break;
	}

	if(i > k / i) {
		printf("%d 不能质因数分解 因为它是素数\n", j);
	} else {
		for(i = 2; i <= k; i++) {
			if(k % i == 0) {
				printf("%d ", i);
				k /= i;
				i--;
			}
		}
	}

	return 0;
}
