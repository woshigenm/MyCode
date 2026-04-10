#include <stdio.h>

int main()
{
	char ch;

	int str_s = 0;
	int str_z = 0;
	while ((ch = getchar()) != '\n') {
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
			str_z++;
		}

		if (ch >= '0' && ch <= '9') {
			str_s++;
		}
	}

	printf("英文字母有%d个\n数字字符有%d个\n", str_z, str_s);
	return 0;
}

