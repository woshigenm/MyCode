#include <stdio.h>

#define SIZE 128

int main() {
	char arr[SIZE];
	gets(arr);

	int i, j, flag, count;
	flag = 1;
	count = 0;
	for (i = 0; arr[i] != '\0'; i++) {
		if (arr[i] != ' ') {
			if (flag) count++;
			flag = 0;
		} else {
			flag = 1;
		}
	}

	printf("%s有%d个单词\n", arr, count);

	//"I LOVE YOU"
	count = 0;
	for (i = 0; arr[i] != '\0'; i++) {
		if (arr[i] != ' ' && (arr[i + 1] == ' ' || arr[i + 1] == '\0')) {
			count++;
		}
	}
	printf("%s有%d个单词\n", arr, count);

	return 0;
}
