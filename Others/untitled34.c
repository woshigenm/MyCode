//【位数的判定】输入一个不超过5位数的正整数，输出它是几位数的信息，并求各个位数和，
//(如果输入的数为负数或超过5位数，显示输入错误)，输入输出形式如下。

#include <stdio.h>

int main() {
	int input;
	scanf("%d", &input);

	if (input < 0 || input > 99999) {
		printf("输入错误");
		return 0;
	}

	if (input == 0) {
		printf("1位数,各个位数和是0");
		return 0;
	}

	int sum = 0;
	int temp = input;

	int count = 0;
	while (temp) {
		sum += temp % 10;
		temp /= 10;
		count++;
	}

	printf("%d位数,各个位数和是%d", count, sum);

	return 0;
}
