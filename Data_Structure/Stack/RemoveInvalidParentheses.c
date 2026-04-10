#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
	OK, ERROR
} Status;

Status RemoveInvalidParentheses(char* str);
bool MatchParentheses(char* str);

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
				str[i] = '\0';
			}
		}
	}

	//如果栈中还有元素，说明括号未匹配完
	//根据 index_stack 中存储的 str 的 index 标记为'\0'
	while (top >= 0) {
		str[index_stack[top--]]	= '\0';
	}

	int write_pos = 0;
	//字符串压缩
	for (int read_pos = 0; read_pos < len; read_pos++) {
		if (str[read_pos] != '\0') {
			str[write_pos++] = str[read_pos];
		}
	}

	str[write_pos] = '\0';

	free(index_stack);
	return OK;
}

