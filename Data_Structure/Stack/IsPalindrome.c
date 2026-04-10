#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool IsPalindrome(char * string);
int main()
{
	char string[128];
	while (fgets(string, 128, stdin) != NULL) {
		string[strcspn(string, "\n")] = '\0';
		printf("%d\n", IsPalindrome(string));
	}
	return 0;
}

bool IsPalindrome(char * string)
{
	int len = strlen(string);
	bool result = true;
	char * Stack = (char *)malloc(sizeof(char) * (len / 2));
	if (NULL == Stack)	return false;
	int top = -1;

	char * pstring = string + len / 2 + len % 2;
	for (int i = 0; i < len / 2; ++i) {
		Stack[++top] = *pstring++;
	}

	while (top >= 0) {
		if (*string++ != Stack[top--]) {
			result = false;
			break;
		}
	}

	free(Stack);
	return result;
}

