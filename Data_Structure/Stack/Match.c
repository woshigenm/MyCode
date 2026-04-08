#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef char ElemType;
typedef enum {
	OK, ERROR
} Status;

typedef struct StackNode {
	ElemType data;
	struct StackNode * next;
} StackNode, *LinkStack;

Status InitStack(LinkStack * S);
Status Push(LinkStack S, ElemType e);
bool IsEmpty(LinkStack S);
Status Pop(LinkStack S, ElemType * e);
void PrintStack(LinkStack S);
Status GetTop(LinkStack S, ElemType * e);
int StackLength(LinkStack S);
Status DestoryLinkStack(LinkStack * S);
Status ClearLinkStack(LinkStack S);
bool Matching(char * str);

int main() {
	char arr[128];

	while (scanf("%s", arr) == 1 && strcmp(arr, "#")) {
		printf("%s -> %d\n", arr, Matching(arr));
	}

	return 0;
}

bool Matching(char * str) {
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
	DestoryLinkStack(&S);
	return result;
}

//初始化栈
Status InitStack(LinkStack * S) {
	if (S == NULL)	return ERROR;
	*S = (StackNode *)malloc(sizeof(StackNode));
	if (*S == NULL) return ERROR;
	(*S)->next = NULL;
	return OK;
}

//入栈元素
Status Push(LinkStack S, ElemType e) {
	if (S == NULL)	return ERROR;
	StackNode * cur = (StackNode *)malloc(sizeof(StackNode));
	if (NULL == cur)	return ERROR;
	cur->data = e;
	cur->next = S->next;
	S->next = cur;
	return OK;
}

//判断栈是否为空
bool IsEmpty(LinkStack S) {
	if (NULL == S)	return true;
	return S->next == NULL;
}

//弹出元素
Status Pop(LinkStack S, ElemType * e) {
	if (S == NULL || IsEmpty(S))	return ERROR;
	StackNode * cur = S->next;
	*e = cur->data;
	S->next = cur->next;
	free(cur);
	return OK;
}

// 打印栈中所有元素（从栈底到栈顶）
void PrintStack(LinkStack S) {
	if (S == NULL || IsEmpty(S)) {
		printf("栈为空！\n");
		return;
	}
	printf("栈中元素（栈底→栈顶）：\n");
	for (StackNode * cur = S->next; cur ; cur = cur->next)
		printf("%d \n", cur->data);
	printf("\n");
}

//返回栈长度
int StackLength(LinkStack S) {
	if (NULL == S)	return 0;

	int j = 0;
	for (StackNode * cur = S->next; cur ; cur = cur->next)
		j++;
	return j;
}

//返回栈顶元素
Status GetTop(LinkStack S, ElemType * e) {
	if (S == NULL || IsEmpty(S))	return ERROR;
	*e = S->next->data;
	return OK;
}

//销毁链栈
Status DestoryLinkStack(LinkStack * S) {
	if (S == NULL || *S == NULL)	return ERROR;
	StackNode * cur = (*S)->next, *str;
	while (cur) {
		str = cur->next;
		free(cur);
		cur	= str;
	}
	free(*S);
	*S = NULL;
	return OK;
}

//清空栈
Status ClearLinkStack(LinkStack S) {
	if (S == NULL)	return ERROR;
	StackNode * cur = S->next, *tmp;
	while (cur) {
		tmp = cur->next;
		free(cur);
		cur	= tmp;
	}
	S->next = NULL;
	return OK;
}
