#include <stdio.h>

long long factorial(int n) {
	long long result = 1;
	for (int i = 1; i <= n; i++) {
		result *= i;
	}
	return result;
}

int main() {
	int n;
	double sum = 0.0;
	
	// 输入项数n
	printf("请输入项数n: ");
	scanf("%d", &n);
	
	// 计算数列的和
	for (int i = 1; i <= n; i++) {
		// 交替加减
		if (i % 2 == 1) {
			sum += 1.0 / factorial(i);  // 奇数项加
		} else {
			sum -= 1.0 / factorial(i);  // 偶数项减
		}
	}
	
	// 输出结果
	printf("数列的和为: %.6lf\n", sum);
	return 0;
}
