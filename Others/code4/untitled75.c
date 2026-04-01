#include <stdio.h>

int main() {
	char str[128];
	gets(str);

	int count = 0;

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0'))	count++;
	}

	printf("一共有 %d 个单词\n", count);

	return 0;
}

void fanxiaochaoNMSL() {
	char str[128];
	gets(str);

	int count = 0, fanxiaochao = 0;

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] != ' ') {
			if (!fanxiaochao) {
				fanxiaochao = 1;
				count++;
			}
		} else {
			fanxiaochao = 0;
		}
	}

	printf("一共有 %d 个单词\n", count);
}
