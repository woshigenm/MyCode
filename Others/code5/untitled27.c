#include <stdio.h>
#include <string.h>
#include <stdint.h>
int main()
{
	int n = 3;
	char x;
	scanf("%c", &x);
// if (x >= 'a' && x <= 'z')
// printf("%c\n", 'a' + (x - 'a' + n) % 26);
// else if (x >= 'A' && x <= 'Z')
// printf("%c\n", 'A' + (x - 'A' + n) % 26);

	if (x >= 'a' && x <= 'z' - n)
		printf("%c\n", x + n);
	else
		printf("%c\n", x + n - 26);

	return 0;
}

