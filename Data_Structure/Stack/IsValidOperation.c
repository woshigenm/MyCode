#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool IsValidOperation(char * string);
int main()
{
	char string[128];
	while (fgets(string, 128, stdin) != NULL) {
		string[strcspn(string, "\n")] = '\0';
		printf("%d\n", IsValidOperation(string));
	}
	return 0;
}

bool IsValidOperation(char * string)
{
	int len = strlen(string);
	char * Stack = (char *)malloc(sizeof(char) * (len + 1));
	if (NULL == Stack)	return false;
	int top = -1;
	bool result = true;

	while (*string && result) {
		char OneChar = toupper(*string);
		if (OneChar != 'I' && OneChar != 'O') {
			result = false;
		} else if (OneChar == 'I') {
			Stack[++top] = 'I';
		} else {
			if (top < 0) {
				result = false;
			} else {
				top--;
			}
		}
		string++;
	}

	if (top >= 0)	result = false;
	free(Stack);
	return result;
}

