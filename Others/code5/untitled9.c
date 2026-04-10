#include <stdio.h>

void test_2()
{
	int n, i, fan;

	int array[4] = {};
	scanf("%d", &n);

	for (i = 1; i <= n; i++) {
		scanf("%d", &fan);

		if (fan > 3 || fan < 0) {
			array[0]++;
		} else {
			array[fan]++;
		}
	}

	for (i = 1; i < 4; i++) {
		printf("%d候选人有:%d票\n", i, array[i]);
	}

	printf("无效票有:%d票\n", array[0]);
}

int main()
{
	test_2();
	return 0;
}


