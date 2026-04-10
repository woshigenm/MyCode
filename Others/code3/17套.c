#include <stdio.h>

/*
17高考真题第一问
输入输出样例
7
YES
1002
NO
1
NO
*/
void test_1()
{
	int x;
	scanf("%d", &x);

	if (x < 2) {
		printf("NO\n");
	} else {
		int i;
		for (i = 2; i < x; i++) {
			if (x % i == 0)
				break;
		}

		if (i >= x) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
}

/*
17高考真题第二问
输出样例
127 129 172 179 192
197 217 219 271 279
291 297 712 719 721
729 791 792 912 917
921 927 971 972
一共有 24 个
*/
void test_2()
{
	int array[4] = {1, 2, 7, 9};
	int i, j, k, t, count;

	count = 0;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			for (k = 0; k < 4; k++) {
				if (i != j && i != k && j != k) {
					t = array[i] * 100 + array[j] * 10 + array[k];
					count++;
					printf("%d ", t);

					if (count % 5 == 0)
						putchar('\n');
				}
			}
		}
	}

	printf("\n一共有 %d 个\n", count);
}

int main()
{
	test_2();
	return 0;
}
