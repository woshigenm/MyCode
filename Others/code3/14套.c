#include <stdio.h>

/*
14高考真题第一问
11451
11451 为 5 位数
114514
请输入不超过五位数的正整数
-114514
请输入不超过五位数的正整数
*/
void test_1()
{
	int x;
	scanf("%d", &x);

	int t = x;
	if (x / 100000 > 0 || x < 0) {
		printf("请输入不超过五位数的正整数\n");
	} else {
		int count = 0;
		while (t) {
			count++;
			t /= 10;
		}

		printf("%d 为 %d 位数\n", x, count);
	}
}

/*
14高考真题第二问
输出样例为
1!+2!+3!...10!为 4037913
*/
void test_2()
{
	int sum = 0;
	int fact = 1;

	int i;
	for (i = 1; i <= 10; i++) {
		fact *= i;
		sum += fact;
	}

	printf("1!+2!+3!...10!为 %d\n", sum);
}

int main()
{

	return 0;
}
