/*【排列组合题 数字组合】用户输入一个正整数N (3<=N<=9) ，
从0到N之间的所有正整数(包含0和N) 中选择2个数，组成一个两位数，且两位数个位十位互不相同，共有多少种两位数。
*/

#include <stdio.h>

int main() {
	int n;
	scanf("%d", &n);

	int i, j;

	int counter = 0;

	for (i = 1; i <= n; i++) {
		for (j = 0; j <= n; j++) {

			if (i != j) {
				printf("%d ", i * 10 + j);
				counter++;
			}
		}
	}
	printf("组成的两位数有%d个\n", counter);
	return 0;
}
