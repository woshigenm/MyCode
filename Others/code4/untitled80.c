#include <stdio.h>

#define SIZE 4

int main() {
	int count = 0;
	for (int i = 0; i <= 5; i++) {
		for (int j = 0; j <= 4; j++) {
			for (int k = 0; k <= 3; k++) {
				int t = 8 - i - j - k;
				if (t >= 0 && t <= 4) {
					printf("%d %d %d %d\n", i, j, k, t);
					count++;
				}
			}
		}
	}

	printf("一共有 %d 个\n", count);

	return 0;
}

