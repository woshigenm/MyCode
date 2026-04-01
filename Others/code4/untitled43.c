//【删除字符串中某个字符】输入任意字符串s，再输入要删除的字符x，
//编程实现删除字符串s中的x字符。（例如s字符串为“ee12dseW36e”，删除的x字符为‘e’，结果s为“12dsW36”）,按下列样例输入输出。

#include <stdio.h>

#define SIZE 128

int main() {
	char array[SIZE];
	gets(array);
	char x;
	x = getchar();

	int i, j = 0;

	for (i = 0; array[i] != '\0'; i++) {
		if (array[i] != x) {
			array[j++] = array[i];
		}
	}
	array[j] = '\0';
	puts(array);
	return 0;
}
