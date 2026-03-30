#include <stdio.h>

/*
6高考真题第一问
输入输出样例
1
It is a number!
a
It is a letter!
!
It isn't a letter or number!
*/
void test_1() {
	char c;
	printf("请输入一个字符: ");
	c = getchar();

	if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
		printf("It is a letter!\n");
	else if (c >= '0' && c <= '9')
		printf("It is a number!\n");
	else
		printf("It isn't a letter or number!");
}

/*
6高考真题第二问
输入输出样例
114 514 19198 10 4 52 5 25 55 23
最大值 19198
*/
void test_2() {
	int array[10];

	int i, j;
	printf("请输入十个整数(空格分隔): ");
	for (i = 0; i < 10; i++)	scanf("%d", &array[i]);

	int max;

	max = array[0];
	for (j = 1; j < 10; j++) {
		if (array[j] > max)
			max = array[j];
	}

	printf("最大值为 %d \n", max);
}

int main() {
	test_2();
	return 0;
}
