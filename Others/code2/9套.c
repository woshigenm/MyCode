#include <stdio.h>

/*
9高考真题第一问
输入输出样例
114
输入有误
50
E
79
C
*/
void test_1() {
	float score;
GO:
	printf("请输入百分制成绩: ");
	scanf("%f", &score);

	if (score > 100 || score < 0) {
		printf("输入有误\n");
		goto GO;
	} else {
		if (score >= 90)
			putchar('A');
		else if (score >= 80)
			putchar('B');
		else if (score >= 70)
			putchar('C');
		else if (score >= 60)
			putchar('D');
		else
			putchar('E');
	}
}

/*
9高考真题第二问
输入输出样例
1 2 3 4 5 6 7 8
最大值 8 最小值 1, 最大值与最小值的差值为 7
2 4 6 8 10 12 14 16
最大值 16 最小值 2, 最大值与最小值的差值为 14
*/
void test_2() {
	int array[8];

	int i, j;
	printf("请输入八个整数(空格分隔): ");
	for (i = 0; i < 8; i++)	scanf("%d", &array[i]);

	int max, min;

	max = min = array[0];

	for (j = 1; j < 8; j++) {
		if (array[j] > max)
			max = array[j];

		if (array[j] < min)
			min = array[j];
	}

	printf("最大值 %d 最小值 %d, 最大值与最小值的差值为 %d\n", max, min, max - min);
}

int main() {
	test_2();
	return 0;
}
