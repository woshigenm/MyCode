//某人有四张3分的邮票和三张5分的邮票，
//用这些邮票中的一张或若干张可以得到多少种不同的邮资？
#include <stdio.h>

int main() {
	int counter = 0;

	int array[28] = {};

	for(int i = 0; i <= 4; i++) {
		for(int j = 0; j <= 3; j++) {
			array[(i * 3 + j * 5) - 1]++;
			
			if(i + j > 0) {
				printf("3分 -> %d 五分 -> %d\n", i, j );
			}
		}
	}

	for(int i = 0; i < 28; i++) {
		if(array[i] != 0) {
			counter++;
		}
	}

	printf("%d\n", counter);
	return 0;
}
