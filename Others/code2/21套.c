#include <stdio.h>

/*
21高考真题第一问 第一种做法
输入输出样例
f1A1n4X5i1A9oChAo@Sm
F1A1N4X5I1A9OCHAO@SM
*/
void test_1_1()
{
	char c;

	char str[256];

	int i = 0;

	printf("请输入一个字符串: ");
	while ((c = getchar()) != '\n') {
		if (c >= 'a' && c <= 'z') {
			c -= 32;
		}
		str[i++] = c;
	}
	str[i] = '\0';
	puts(str);
}

/*
21高考真题第一问 第二种做法
输入输出样例
f1A1n4X5i1A9oChAo@Sm
F1A1N4X5I1A9OCHAO@SM
*/
void test_1_2()
{
	char str[256];

	printf("请输入一个字符串: ");
	gets(str);

	int i;
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			str[i] -= 32;
		}
	}

	puts(str);
}

/*
21高考真题第二问 第一种做法
输入输出样例
10
2 3 6 1 8 8 6 4 2 4
*/
void test_2_1()
{
	int array[256] = {2, 3};

	int n;
	printf("请输入一个正整数n: ");
	scanf("%d", &n);

	int i, j, t, count;

	for (i = 2; i < n;) {
		t = array[i - 1] * array[i - 2];
		j = t;

		count = 0;
		while (j) { //计算乘积的位数
			count++;
			j /= 10;
		}

		if (count == 1) { //一位数
			array[i++] = t;
		} else if (count == 2) { //两位数
			array[i++] = t / 10;
			array[i++] = t % 10;
		}
	}

	for (i = 0; i < n; i++)
		printf("%d ", array[i]);
}


/*
21高考真题第二问 第一种做法
输入输出样例
20
2 3 6 1 8 8 6 4 2 4 8 3 2 6 1 2 2 4 8 3
*/
void test_2_2()
{
	int array[128] = {2, 3};

	int n;
	printf("请输入一个正整数n: ");
	scanf("%d", &n);

	int i, t;

	for (i = 2; i < n;) {
		t = array[i - 1] * array[i - 2];

		if (t / 10 == 0) { //一位数
			array[i++] = t;
		} else {
			array[i++] = t / 10;
			array[i++] = t % 10;
		}
	}

	for (i = 0; i < n; i++)
		printf("%d ", array[i]);
}

int main()
{

	return 0;
}
