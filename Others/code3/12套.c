#include <stdio.h>

/*
12高考真题第一问
输出样例
19 28 37 46 55 64 73 82 91
*/
void test_1() {
	int i;
	for(i = 10; i <= 99; i++) {
		int j = i / 10;
		int k = i % 10;
		if(j + k == 10) {
			printf("%d ", i);
		}
	}
}

/*
12高考真题第二问 (冒泡排序)
输入输出样例
1 1 4 5 1 4 19 198 10 114514
114514 198 19 10 5 4 4 1 1 1
*/
void test_2_1() {
	int i, j, t;
	int array[10];

	for(i = 0; i < 10; i++)	scanf("%d", &array[i]);

	for(i = 1; i < 10; i++) {
		for(j = 0; j < 10 - i; j++) {
			if(array[j] < array[j + 1]) {
				t = array[j];
				array[j] = array[j + 1];
				array[j + 1] = t;
			}
		}
	}

	for(i = 0; i < 10; i++) printf("%d ", array[i]);
}

/*
12高考真题第二问 (选择排序)
输入输出样例
114 514 19198 10 4 52 5 25 55 23
19198 514 114 55 52 25 23 10 5 4
*/
void test_2_2() {
	int i, j, t;
	int array[10];

	for(i = 0; i < 10; i++)	scanf("%d", &array[i]);

	int pos;
	for(i = 0; i < 9; i++) {
		pos = i;
		for(j = i + 1; j < 10; j++) {
			if(array[j] > array[pos])	pos = j;
		}

		if(pos != i) {
			t = array[i];
			array[i] = array[pos];
			array[pos] = t;
		}
	}

	for(i = 0; i < 10; i++) printf("%d ", array[i]);
}

int main() {
	
	return 0;
}
