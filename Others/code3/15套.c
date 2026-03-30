#include <stdio.h>

/*
15高考真题第一问
输入输出样例
1 2 3
3 2 1

1 3 2
3 2 1
*/
void test_1() {
	int x, y, z, t;
	scanf("%d%d%d", &x, &y, &z);
	if(x < y) {
		t = x;
		x = y;
		y = t;
	}

	if(x < z) {
		t = x;
		x = z;
		z = t;
	}
	if(y < z) {
		t = y;
		y = z;
		z = t;
	}
	
	printf("%d %d %d\n", x, y, z);
}

/*
15高考真题第二问 第一种做法
输入输出样例
24
24 的二进制为 11000
114
114 的二进制为 1110010
*/
void test_2_1() {
	int x;
	scanf("%d", &x);

	int e = 1;
	int t = x;

	int sum = 0;
	while(t) {
		sum += e * (t % 2);
		e *= 10;
		t /= 2;
	}

	printf("%d 的二进制为 %d\n", x, sum);
}

/*
15高考真题第二问 第二种做法
输入输出样例
114514
114514 的二进制为 11011111101010010
1919810
1919810 的二进制为 111010100101101000010
*/
void test_2_2() {
	int array[32];
	int x, i, j, t;
	scanf("%d", &x);
	t = x;
	for(i = 0; t != 0; i++) {
		array[i] = t % 2;
		t /= 2;
	}

	printf("%d 的二进制为 ", x);
	for(j = i - 1; j >= 0; j--)
		printf("%d", array[j]);
}

int main() {
	test_1();
	return 0;
}
