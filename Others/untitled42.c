//【字符删除】输入任意一串字符str，删除其中不是字母的字符，并输出新的字符串str，输入输出形式如下。
#include <stdio.h>

#define SIZE 128

#define ALP(x) ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'))
int main() {
	char array[SIZE];
	gets(array);

	int i, j = 0;

	for (i = 0; array[i] != '\0'; i++) {
		if (ALP(array[i])) {
			array[j++] = array[i];
		}
	}
	array[j] = '\0';
	puts(array);

	return 0;
}
