//【水仙花数判断】输入任意一个数，判定是否是水仙花数（水仙花数是一个三位数，每位的立方和等于它本身），输入输出格式如下。
#include <stdio.h>

int main() {
	int input;
	scanf("%d", &input);

	if (input > 999) {
		printf("不是水仙花数\n");
	} else {
		int a = input / 100;
		int b = input / 10 % 10;
		int c = input % 10;

		if (a * a * a + b * b * b + c * c * c == input) {
			printf("是水仙花数\n");
		} else {
			printf("不是水仙花数\n");
		}
	}
	return 0;
}
