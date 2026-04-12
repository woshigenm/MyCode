#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool IsPalindrome(char * string);
bool IsPalindrome_DPoint(char * string);

int main()
{
	char string[128];
	while (fgets(string, 128, stdin) != NULL) {
		string[strcspn(string, "\n")] = '\0';
		printf("%d\n", IsPalindrome(string));
		printf("%d\n", IsPalindrome_DPoint(string));
	}

	return 0;
}

bool IsPalindrome(char * string)
{
	if (NULL == string)	return false;

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

bool IsPalindrome_DPoint(char * string)
{
	if (NULL == string)	return false;
	if (*string == '\0') return true;

	char * left = string;
	char * right = string + strlen(string) - 1;
	while (left < right) {
		if (*left != *right) {
			return false;
		}
		left++;
		right--;
	}

	return true;
}

