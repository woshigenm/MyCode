#include <stdio.h>

#define SIZE 128

int main() {
	char arr[SIZE];
	gets(arr);

	int i, j;

	int case_xiao = 0;

	for (i = 0; arr[i] != '\0'; i++) {
		if (arr[i] >= 'a' && arr[i] <= 'z') {
			case_xiao++;
		}
	}

	printf("%s小写字母有%d个\n", arr, case_xiao);

	return 0;
}

