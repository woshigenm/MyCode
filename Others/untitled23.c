#include <stdio.h>

/*
【特征数车牌搜寻】一辆卡车违反交通规则，撞人逃逸。现场三人目击事件，但都没有记住车号，只记下车的一些特征。
甲说：牌照的前两位数字是相同的，后面的数字与前面不同；乙说：牌照的后两位数字是相同的；
丙是位数学家，他说：四位的车号正好是一个整数的平方。请根据以上线索求出可能的车牌号，输入输出形式如下。
*/

int gcd(int x) {
	static int i = 32;
	for (; i <= x / i; i++) {
		if (i * i == x) {
			return 1;
		}
	}

	return 0;
}

int main() {
	int i, j, k;
	for (i = 1; i <= 9; i++) {
		for (j = 0; j <= 9; j++) {
			if (i != j) {
				k = i * 1000 + i * 100 + j * 10 + j;
				if (gcd(k)) {
					printf("车牌是%d\n", k);
				}
			}
		}
	}
	return 0;
}
