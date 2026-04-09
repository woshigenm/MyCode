#include "../Headers/LinkStack.h"
#include <stdio.h>
#include <string.h>

bool Matching(char * str);
int main() {
	char arr[128];
	while (scanf("%s", arr) == 1 && strcmp(arr, "#")) {
		printf("%s -> %d\n", arr, Matching(arr));
	}

	return 0;
}

bool Matching(char * str) {
	if (NULL == 	str)	return false;
	ElemType e;
	LinkStack S;
	InitStack(&S);
	bool flag = true;
	while (*str && flag) {
		switch (*str) {
			case '(':
			case '[':
			case '{': {
				Push(S, *str);
				break;
			}
			case ')': {
				if (GetTop(S, &e) == OK && e == '(') {
					Pop(S, &e);
				} else {
					flag = false;
				}
				break;
			}
			case ']': {
				if (GetTop(S, &e) == OK && e == '[') {
					Pop(S, &e);
				} else {
					flag = false;
				}
				break;
			}
			case '}': {
				if (GetTop(S, &e) == OK && e == '{') {
					Pop(S, &e);
				} else {
					flag = false;
				}
			}
		}
		str++;
	}

	bool result = IsEmpty(S) && flag;
	DestroyStack(&S);
	return result;
}

