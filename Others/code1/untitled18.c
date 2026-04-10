#include <stdio.h>

#define SIZE 128

int main()
{
	char arr[SIZE];
	gets(arr);

	int i, j;

	int str_a, str_e, str_i, str_o, str_u;
	str_a = str_e = str_i = str_o = str_u = 0;

	for (i = 0; arr[i] != '\0'; i++) {
		switch (arr[i]) {
			case 'A':
			case 'a':
				break;
			case 'E':
			case 'e':

				break;
			case 'I':
			case 'i':
				break;
			case 'O':
			case 'o':
				break;
			case 'U':
			case 'u':
		}
	}
	return 0;
}

