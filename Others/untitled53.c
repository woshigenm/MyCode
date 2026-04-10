#include <stdio.h>

int main()
{
	char input[256];
	gets(input);

	int alpha = 0;
	int number = 0;
	int space = 0;
	int others = 0;

	for (int i = 0; input[i]; i++) {
		if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
			alpha++;
		else if (input[i] >= '0' && input[i] <= '9')
			number++;
		else if (input[i] == ' ')
			space++;
		else
			others++;
	}

	printf("%d\n%d\n%d\n%d\n", alpha, space, number, others);

	return 0;
}
