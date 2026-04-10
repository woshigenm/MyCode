#include <stdio.h>

/*
4高考真题第一问
输出样例
105 140 175 210 245 280 315 350 385 420 455 490
*/
void test_1()
{
	int i;
	printf("100-500之间能被五和七整除的数为: ");
	for (i = 100; i <= 500; i++) {
		if (i % 5 == 0 && i % 7 == 0) {
			printf("%d ", i);
		}
	}
}

/*
4高考真题第二问
输入输出样例
f1A1n4X5i1A9oChAo@Sm
数字字符有 6 个
*/
void test_2()
{
	char str[51];
	printf("请输入长度不超过50的字符串: ");
	gets(str);

	int i;

	int count = 0;
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] >= '0' && str[i] <= '9')
			count++;
	}

	printf("数字字符有 %d 个\n", count);
}

int main()
{
	test_2();
	return 0;
}
