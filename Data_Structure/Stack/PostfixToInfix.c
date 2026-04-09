#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// ======================== 宏定义与类型定义 ========================
#define STR_MAX_LEN 32
#define MAXINPUT 128
#define DEBUG 1
#define RESET_STR(str) (str[0] = '\0')

typedef union {
	int num;
	char oper;
	char alpha[STR_MAX_LEN];
} ElemData;

typedef enum {
	ALPHA, NUMBER, OPERATOR
} CalType;

typedef struct {
	CalType WhatIs;
	ElemData data;
} ElemType;

typedef enum {
	ERROR, OK
} Status;

typedef struct StackNode {
	ElemType data;
	struct StackNode *next;
} StackNode, *LinkStack;

// ======================== 函数声明 ========================
Status InitStack(LinkStack *stack);
Status Push(LinkStack stack, ElemType elem);
bool IsEmpty(LinkStack stack);
Status Pop(LinkStack stack, ElemType *out_elem);
void PrintPoLishStack(LinkStack stack);
Status GetTop(LinkStack stack, ElemType *out_elem);
int StackLength(LinkStack stack);
Status DestroyStack(LinkStack *stack);
Status ClearStack(LinkStack stack);
Status ReverseStack(LinkStack stack);

int GetPriority(char oper);
bool IsRightAssoc(char oper);
Status InfixToPostfix(const char *infix_str, LinkStack *out_postfix);
bool MatchParentheses(const char *infix_str);
Status PostfixToInfix(LinkStack polish_stack, char *infix_str);

//独立辅助函数声明
static void reverse_str(char *str);
static void append_char(char *str, char ch);
static void int_to_string(int num, char *out_str);

// ======================== 核心逻辑 ========================
int main() {
	char str[MAXINPUT];
	fgets(str, MAXINPUT, stdin);
	str[strcspn(str, "\n")] = '\0';

	if (!MatchParentheses(str)) {
		printf("表达式转换失败\n");
		return -1;
	}

	LinkStack PoLish = NULL;
	if (InfixToPostfix(str, &PoLish) == OK) {
		#if DEBUG
		PrintPoLishStack(PoLish);
		#endif
		char InfixStr[STR_MAX_LEN * 2] = "";
		if (PostfixToInfix(PoLish, InfixStr) == OK) {
			printf("%s\n", InfixStr);
		} else {
			printf("表达式转换失败\n");
		}
		DestroyStack(&PoLish);
	} else {
		printf("表达式转换失败\n");
	}

	return 0;
}

Status PostfixToInfix(LinkStack polish_stack, char *infix_str) {
	ElemType top_elem, push_elem, oprand1, oprand2;
	LinkStack Infix;
	InitStack(&Infix);

	char temp[STR_MAX_LEN * 2];
	ReverseStack(polish_stack);

	while (!IsEmpty(polish_stack)) {
		if (Pop(polish_stack, &top_elem) == ERROR) {
			DestroyStack(&Infix);
			return ERROR;
		}

		if (top_elem.WhatIs == ALPHA) {
			Push(Infix, top_elem);

		} else if (top_elem.WhatIs == OPERATOR) {
			if (Pop(Infix, &oprand2) == ERROR || Pop(Infix, &oprand1) == ERROR) {
				DestroyStack(&Infix);
				return ERROR;
			}

			RESET_STR(temp);
			if (top_elem.data.oper == '+' || top_elem.data.oper == '-') {
				append_char(temp, '(');
				strcat(temp, oprand1.data.alpha);
				append_char(temp, top_elem.data.oper);
				strcat(temp, oprand2.data.alpha);
				append_char(temp, ')');
			} else {
				strcat(temp, oprand1.data.alpha);
				append_char(temp, top_elem.data.oper);
				strcat(temp, oprand2.data.alpha);
			}

			push_elem.WhatIs = ALPHA;
			strcpy(push_elem.data.alpha, temp);
			Push(Infix, push_elem);

		} else if (top_elem.WhatIs == NUMBER) {
			push_elem.WhatIs = ALPHA;
			int_to_string(top_elem.data.num, push_elem.data.alpha);
			Push(Infix, push_elem);
		}
	}

	if (StackLength(Infix) == 1) {
		Pop(Infix, &top_elem);
		strcpy(infix_str, top_elem.data.alpha);
	} else {
		DestroyStack(&Infix);
		return ERROR;
	}

	DestroyStack(&Infix);
	return OK;
}


// ======================== 辅助函数实现 ========================
static void reverse_str(char *str) {
	if (str == NULL) return;
	int len = strlen(str);
	for (int i = 0; i < len / 2; i++) {
		char tmp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = tmp;
	}
}

static void append_char(char *str, char ch) {
	int len = strlen(str);
	str[len] = ch;
	str[len + 1] = '\0';
}

static void int_to_string(int num, char *out_str) {
	char buf[32];
	int i = 0;

	do {
		buf[i++] = num % 10 + '0';
		num /= 10;
	} while (num);

	buf[i] = '\0';

	reverse_str(buf);
	strcpy(out_str, buf);
}


// ======================== 链栈基础操作实现 ========================
Status InitStack(LinkStack *stack) {
	if (stack == NULL) return ERROR;
	*stack = (StackNode *)malloc(sizeof(StackNode));
	if (*stack == NULL) return ERROR;
	(*stack)->next = NULL;
	return OK;
}

Status Push(LinkStack stack, ElemType elem) {
	if (stack == NULL) return ERROR;
	StackNode *cur = (StackNode *)malloc(sizeof(StackNode));
	if (NULL == cur) return ERROR;
	cur->data = elem;
	cur->next = stack->next;
	stack->next = cur;
	return OK;
}

bool IsEmpty(LinkStack stack) {
	if (NULL == stack) return true;
	return stack->next == NULL;
}

Status Pop(LinkStack stack, ElemType *out_elem) {
	if (stack == NULL || IsEmpty(stack)) return ERROR;
	StackNode *cur = stack->next;
	*out_elem = cur->data;
	stack->next = cur->next;
	free(cur);
	return OK;
}

void PrintPoLishStack(LinkStack stack) {
	if (stack == NULL) {
		printf("栈未初始化！\n");
		return;
	}
	if (IsEmpty(stack)) {
		printf("栈为空！\n");
		return;
	}

	LinkStack tempStack;
	InitStack(&tempStack);
	ElemType top_elem;
	while (!IsEmpty(stack)) {
		Pop(stack, &top_elem);
		Push(tempStack, top_elem);
	}

	while (!IsEmpty(tempStack)) {
		Pop(tempStack, &top_elem);
		switch (top_elem.WhatIs) {
			case OPERATOR:
				printf("%c ", top_elem.data.oper);
				break;
			case NUMBER:
				printf("%d ", top_elem.data.num);
				break;
			case ALPHA:
				printf("%s ", top_elem.data.alpha);
				break;
		}
		Push(stack, top_elem);  // 恢复原栈
	}
	putchar('\n');
	DestroyStack(&tempStack);
}

int StackLength(LinkStack stack) {
	if (NULL == stack) return 0;
	int j = 0;
	for (StackNode *cur = stack->next; cur; cur = cur->next)
		j++;
	return j;
}

Status GetTop(LinkStack stack, ElemType *out_elem) {
	if (stack == NULL || IsEmpty(stack)) return ERROR;
	*out_elem = stack->next->data;
	return OK;
}

Status DestroyStack(LinkStack *stack) {
	if (stack == NULL || *stack == NULL) return ERROR;
	StackNode *cur = (*stack)->next, *p;
	while (cur) {
		p = cur->next;
		free(cur);
		cur = p;
	}
	free(*stack);
	*stack = NULL;
	return OK;
}

Status ClearStack(LinkStack stack) {
	if (stack == NULL) return ERROR;
	StackNode *cur = stack->next, *tmp;
	while (cur) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	stack->next = NULL;
	return OK;
}

Status ReverseStack(LinkStack stack) {
	if (NULL == stack) return ERROR;
	StackNode *cur = stack->next, *pre = NULL, *next = NULL;
	while (cur) {
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	stack->next = pre;
	return OK;
}

// ======================== 表达式解析实现 ========================
int GetPriority(char oper) {
	switch (oper) {
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
		case '%':
			return 2;
		case '^':
			return 3;
		case '(':
			return 0;
	}
	return -1;
}

bool IsRightAssoc(char oper) {
	return oper == '^';
}

Status InfixToPostfix(const char *infix_str, LinkStack *out_postfix) {
	if (infix_str == NULL || out_postfix == NULL) return ERROR;

	LinkStack Operator;
	if (InitStack(&Operator) != OK) return ERROR;
	if (InitStack(out_postfix) != OK) {
		DestroyStack(&Operator);
		return ERROR;
	}

	const char *strp = infix_str;
	ElemType top_elem, now_elem, push_elem;

	while (*strp != '\0') {
		if (*strp == ' ') {
			strp++;
			continue;
		} else if (isalpha(*strp)) {
			int i = 0;
			char arr[STR_MAX_LEN + 1];
			while (i < STR_MAX_LEN && *strp != '\0' && (isalpha(*strp) || isdigit(*strp))) {
				arr[i++] = *strp;
				strp++;
			}
			arr[i] = '\0';
			push_elem.WhatIs = ALPHA;
			strcpy(push_elem.data.alpha, arr);
			Push(*out_postfix, push_elem);
			continue;
		} else if (isdigit(*strp)) {
			int num = 0;
			while (*strp != '\0' && isdigit(*strp)) {
				num = num * 10 + (*strp - '0');
				strp++;
			}
			push_elem.WhatIs = NUMBER;
			push_elem.data.num = num;
			Push(*out_postfix, push_elem);
			continue;
		}

		switch (*strp) {
			case '(': {
				push_elem.WhatIs = OPERATOR;
				push_elem.data.oper = *strp;
				Push(Operator, push_elem);
				break;
			}
			case ')': {
				while (!IsEmpty(Operator) && GetTop(Operator, &top_elem)) {
					if (top_elem.WhatIs == OPERATOR && top_elem.data.oper == '(') break;
					Pop(Operator, &now_elem);
					Push(*out_postfix, now_elem);
				}
				if (!IsEmpty(Operator)) Pop(Operator, &top_elem);
				break;
			}
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			case '^': {
				while (!IsEmpty(Operator) && GetTop(Operator, &top_elem)) {
					if (top_elem.WhatIs != OPERATOR || top_elem.data.oper == '(') break;
					int cur_priority = GetPriority(*strp);
					int top_priority = GetPriority(top_elem.data.oper);
					if (IsRightAssoc(*strp)) {
						if (cur_priority >= top_priority) break;
					} else {
						if (cur_priority > top_priority) break;
					}
					Pop(Operator, &now_elem);
					Push(*out_postfix, now_elem);
				}
				push_elem.WhatIs = OPERATOR;
				push_elem.data.oper = *strp;
				Push(Operator, push_elem);
				break;
			}
			default:
				DestroyStack(&Operator);
				DestroyStack(out_postfix);
				return ERROR;
		}
		strp++;
	}

	while (!IsEmpty(Operator)) {
		Pop(Operator, &now_elem);
		Push(*out_postfix, now_elem);
	}

	DestroyStack(&Operator);
	return OK;
}

bool MatchParentheses(const char *infix_str) {
	if (NULL == infix_str) return false;
	ElemType push_elem, top_elem;
	LinkStack Parentheses;
	InitStack(&Parentheses);
	bool flag = true;
	while (*infix_str && flag) {
		switch (*infix_str) {
			case '(': {
				push_elem.WhatIs = OPERATOR;
				push_elem.data.oper = *infix_str;
				Push(Parentheses, push_elem);
				break;
			}
			case ')': {
				if (GetTop(Parentheses, &top_elem) == OK && top_elem.data.oper == '(') {
					Pop(Parentheses, &top_elem);
				} else {
					flag = false;
				}
				break;
			}
		}
		infix_str++;
	}

	bool result = IsEmpty(Parentheses) && flag;
	DestroyStack(&Parentheses);
	return result;
}

