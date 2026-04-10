#include <stdio.h>

#define SIZE 26

int main()
{
	int array[SIZE] = {};
	char str[128];
	gets(str);

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			array[str[i] - 'a']++;
		}
	}

	for (int i = 0; i < SIZE; i++) {
		printf("字母 %c 有 %d 个\n", 'a' + i, array[i]);
	}
	return 0;
}

