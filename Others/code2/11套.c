#include <stdio.h>

/*
11高考真题第一问
输出样例
123 124 132 134 142 143 213 214 231 234 241 243 312 314 321 324 341 342 412 413 421 423 431 432
*/
void test_1() {
	int i, j, k;
	for (i = 1; i <= 4; i++) {
		for (j = 1; j <= 4; j++) {
			for (k = 1; k <= 4; k++) {
				if (i != j && i != k && j != k) {
					int t = i * 100 + j * 10 + k;
					printf("%d ", t);
				}
			}
		}
	}
}

/*
11高考真题第二问
输出样例
113 128 143 158 173
188 203 218 233 248
263 278 293
*/
void test_2() {
	int i, count;

	count = 0;
	printf("100-300之间能被3除余剩2, 且被5除余剩3的数为:\n");
	for (i = 100; i <= 300; i++) {
		if (i % 3 == 2) {
			if (i % 5 == 3) {
				count++;
				printf("%d ", i);

				if (count % 5 == 0)
					putchar('\n');
			}
		}
	}
}

int main() {

	return 0;
}
