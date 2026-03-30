#include <stdio.h>

/*
13高考真题第一问
输出样例
10 11 12 13 14 15 16 17 18 19 20 21 30 31 40 41 50 51 60 61 70 71 80 81 90 91
*/
void test_1() {
	int i;

	int j, k;
	for(i = 10; i <= 99; i++) {
		j = i / 10;
		k = i % 10;

		if(j * k < j + k) {
			printf("%d ", i);
		}
	}
}

/*
13高考真题第二问 (冒泡排序)
输入输出样例
1 1 4 5 1 4 19 198 10 114514
1 1 1 4 4 5 10 19 198 114514
*/
void test_2_1() {
	int i, j, t;
	int array[10];

	for(i = 0; i < 10; i++)	scanf("%d", &array[i]);

	for(i = 1; i < 10; i++) {
		for(j = 0; j < 10 - i; j++) {
			if(array[j] > array[j + 1]) {
				t = array[j];
				array[j] = array[j + 1];
				array[j + 1] = t;
			}
		}
	}

	for(i = 0; i < 10; i++) printf("%d ", array[i]);
}

/*
13高考真题第二问 (选择排序)
输入输出样例
114 514 19198 10 4 52 5 25 55 23
4 5 10 23 25 52 55 114 514 19198
*/
void test_2_2() {
	int i, j, t;
	int array[10];

	for(i = 0; i < 10; i++)	scanf("%d", &array[i]);

	int pos;
	for(i = 0; i < 9; i++) {
		pos = i;
		for(j = i + 1; j < 10; j++) {
			if(array[j] < array[pos])	pos = j;
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
