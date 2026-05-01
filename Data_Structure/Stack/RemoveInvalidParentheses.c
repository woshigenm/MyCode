#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
	OK, ERROR
} Status;

Status RemoveInvalidParentheses(char* str);
bool MatchParentheses(char* str);
char* minRemoveToMakeValid(char* str);

int main()
{
	char arr[128];
	while (scanf("%s", arr) == 1 && strcmp(arr, "#")) {
		printf("%s -> %d\n", arr, MatchParentheses(arr));
		RemoveInvalidParentheses(arr);
		printf("%s -> %d\n", arr, MatchParentheses(arr));
	}

	return 0;
}

bool MatchParentheses(char* str)
{
	if (NULL == str)	return false;

	int len = strlen(str);
	int* index_stack = (int*)malloc(sizeof(int) * (len + 1));
	if (NULL == index_stack)	return false;
	int top = -1;

	bool flag = true;
	for (int i = 0; flag && i < len; ++i) {
		if (str[i] != '(' && str[i] != ')' && str[i] != '[' && str[i] != ']' && str[i] != '{' && str[i] != '}') {
			continue;
		}

		if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
			index_stack[++top] = i;
		} else {
			char expect = str[i] == ')' ? '(' : str[i] == ']' ? '[' : '{';
			if (top >= 0 && str[index_stack[top]] == expect) {
				top--;
			} else {
				flag = false;
			}
		}
	}

	free(index_stack);
	return flag && top == -1;
}

Status RemoveInvalidParentheses(char* str)
{
	if (NULL == str)	return ERROR;
	int len = strlen(str);
	int* index_stack = (int*)malloc(sizeof(int) * (len + 1));
	if (NULL == index_stack)	return false;
	int top = -1;

	int i;
	for (i = 0; i < len; ++i) {
		if (str[i] != '(' && str[i] != ')') {
			continue;
		}

		if (str[i] == '(') {
			index_stack[++top] = i;
		} else {
			if (top >= 0 && str[index_stack[top]] == '(') {
				top--;
			} else {
				str[i] = '\0';
			}
		}
	}

	//如果栈中还有元素，说明括号未匹配完
	while (top >= 0) {
		str[index_stack[top--]]	= '\0';
	}

	int write_pos = 0;
	for (int read_pos = 0; read_pos < len; read_pos++) {
		if (str[read_pos] != '\0') {
			str[write_pos++] = str[read_pos];
		}
	}

	str[write_pos] = '\0';

	free(index_stack);
	return OK;
}

char* minRemoveToMakeValid(char* str)
{
	if (NULL == str) return NULL;

	int len = strlen(str);
	if (len == 0) {
		char* res = (char*)malloc(1);
		res[0] = '\0';
		return res;
	}

	int i = 0, j, top = -1;
	unsigned int * stack = (unsigned int *)malloc(sizeof(unsigned int) * len);
	unsigned char * to_remove = (unsigned char *)calloc(len, 1);

	if (stack == NULL || to_remove == NULL) {
		free(stack);
		free(to_remove);
		return NULL;
	}

	while (str[i]) {
		if (str[i] != '(' && str[i] != ')' && str[i] != '[' && str[i] != ']' && str[i] != '{' && str[i] != '}') {
			i++;
			continue;
		} else if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
			stack[++top] = i;
		} else {
			char expect = str[i] == ')' ? '(' : str[i] == ']' ? '[' : '{';
			if (top >= 0 && str[stack[top]] == expect) {
				--top;
			} else {
				int found_index = top;
				while (found_index >= 0) {
					if (str[stack[found_index]] == expect) {
						break;
					}
					--found_index;
				}

				if (found_index != -1) {
					while (top > found_index) {
						to_remove[stack[top--]] = 1;
					}
					top--;
				} else {
					to_remove[i] = 1;
				}
			}
		}
		i++;
	}

	while (top >= 0) {
		to_remove[stack[top--]] = 1;
	}

	for (i = 0, j = 0; i < len; i++) {
		if (!to_remove[i]) {
			str[j++] = str[i];
		}
	}
	str[j] = '\0';

	free(stack);
	free(to_remove);
	return str;
}

