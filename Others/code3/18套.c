#include <stdio.h>

/*
18高考真题第一问
输入输出样例
2 4 6 8 10 12 14 16 18 20
偶数的平均值为 11.000000
没有奇数
*/
void test_1()
{
	int array[10];
	int i;

	int sum_o, sum_ji;
	int count_o, count_ji;
	sum_ji = sum_o = 0;
	count_o = count_ji = 0;

	for (i = 0; i < 10; i++) {
		scanf("%d", &array[i]);
		if (array[i] % 2 == 0) {
			sum_o += array[i];
			count_o++;
		} else {
			sum_ji += array[i];
			count_ji++;
		}
	}

	if (count_o > 0) {
		printf("偶数的平均值为 %f\n", (float)sum_o / count_o);
	} else {
		printf("没有偶数\n");
	}

	if (count_ji > 0) {
		printf("奇数的平均值为 %f\n", (float)sum_ji / count_ji);
	} else {
		printf("没有奇数\n");
	}
}

/*
18高考真题第二问
输出样例
101 103 107 109 113
127 131 137 139 149
151 157 163 167 173
179 181 191 193 197
199 211
*/
void test_2()
{
	int i, j, count;
	count = 0;
	for (i = 100; j <= 200; i++) {
		for (j = 2; j < i; j++) {
			if (i % j == 0) {
				break;
			}
		}

		if (j >= i) {
			count++;
			printf("%d ", i);
			if (count % 5 == 0)
				putchar('\n');
		}
	}
}

int main()
{
	test_1();
	return 0;
}
