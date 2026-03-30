#include <stdio.h>

//20高考真题第一问
void test_1() {
	float volume, bianchang, high;

	bianchang = 230.0;
	high = 146.5;
	volume = (bianchang * bianchang * high) / 3.0;

	printf("边长为 %f，高为 %f 的金字塔体积为 %f\n", bianchang, high, volume);
}

/*
20高考真题第二问 第一种做法
输入输出样例
fan xiao chao @ qq .com
6 number words
*/
void test_2_1() {
	char str[128];
	
	printf("请输入一个英语句子: ");
	gets(str);

	int i, count;

	count = 0;

	int flag = 1;
	for(i = 0; str[i] != '\0'; i++) {
		if(str[i] != ' ') {
			if(flag) count++;

			flag = 0;
		} else	flag = 1;
	}

	printf("%d number words\n", count);
}

/*
20高考真题第二问 第二种做法
输入输出样例
fan xiao chao @ sm qq .com
7 number words
*/
void test_2_2() {
	char str[128];
	printf("请输入一个英语句子: ");
	gets(str);

	int i, count;

	count = 0;
	for(i = 0; str[i] != '\0'; i++) {
		if(str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
			count++;
	}

	printf("%d number words\n", count);
}

int main() {

	return 0;
}
