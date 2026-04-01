#include <stdio.h>

int main() {
	char str[128];
	gets(str);

	int i;

	int flag = 1;
	for (i = 0; str[i]; i++) {
		if (str[i] != ' ') {
			if (flag) {
				if (str[i] >= 'a' && str[i] <= 'z')
					str[i] -= 32;

				flag = 0;
			}
		} else flag = 1;
	}

	puts(str);
}
