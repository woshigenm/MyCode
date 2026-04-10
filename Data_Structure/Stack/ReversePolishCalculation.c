#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define STR_MAX_LEN 32
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
	struct StackNode * next;
} StackNode, *LinkStack;

Status InitStack(LinkStack * S);
Status Push(LinkStack S, ElemType e);
bool IsEmpty(LinkStack S);
Status Pop(LinkStack S, ElemType * e);
void PrintPoLishStack(LinkStack S);
Status GetTop(LinkStack S, ElemType * e);
int StackLength(LinkStack S);
Status DestroyStack(LinkStack * S);
Status ClearStack(LinkStack S);
int GetPriority(char oper);
bool IsRightAssoc(char oper);
Status InfixToPostfix(const char *infix_str, LinkStack *out_postfix);
bool MatchParentheses(const char *infix_str);
int Calculate(char oper, int oprand1, int oprand2);
int ReversePolishCalculate(LinkStack PoLish);
Status ReverseStack(LinkStack S);

#define MAXINPUT 128
#define DEBUG 1
int main()
{
	char str[MAXINPUT];
	fgets(str, MAXINPUT, stdin);
	str[strcspn(str, "\n")] = '\0';

	LinkStack PoLish = NULL;
	if (!MatchParentheses(str)) {
		printf("表达式转换失败\n");
		return -1;
	}

	if (InfixToPostfix(str, &PoLish) == OK) {
#if DEBUG
		PrintPoLishStack(PoLish);
#endif
		int result = ReversePolishCalculate(PoLish);
		printf("%d\n", result);
		DestroyStack(&PoLish);
	} else {
		printf("表达式转换失败\n");
	}

	return 0;
}

int ReversePolishCalculate(LinkStack PoLish)
{
	LinkStack Oprand;
	InitStack(&Oprand);

	ElemType top_elem, oprand1, oprand2, push_elem;
	int result;

	ReverseStack(PoLish);
	while (!IsEmpty(PoLish)) {
		Pop(PoLish, &top_elem);
		if (top_elem.WhatIs == NUMBER) {
			Push(Oprand, top_elem);
		} else if (top_elem.WhatIs == OPERATOR) {
			if (Pop(Oprand, &oprand2) == ERROR || Pop(Oprand, &oprand1) == ERROR) {
				printf("计算失败：表达式格式错误，缺少操作数\n");
				DestroyStack(&PoLish);
				DestroyStack(&Oprand);
				exit(EXIT_FAILURE);
			}

			push_elem.WhatIs = NUMBER;
			push_elem.data.num = Calculate(top_elem.data.oper, oprand1.data.num, oprand2.data.num);
			Push(Oprand, push_elem);
		} else if (top_elem.WhatIs == ALPHA) {
			printf("计算失败：表达式中包含无法解析的变量 '%s'\n", top_elem.data.alpha);
			DestroyStack(&PoLish);
			DestroyStack(&Oprand);
			exit(EXIT_FAILURE);
		}
	}

	if (StackLength(Oprand) != 1) {
		printf("计算失败：表达式格式不正确（可能缺少运算符）\n");
		DestroyStack(&PoLish);
		DestroyStack(&Oprand);
		exit(EXIT_FAILURE);
	}

	Pop(Oprand, &top_elem);
	result = top_elem.data.num;

	DestroyStack(&Oprand);

	return result;
}

int Calculate(char oper, int oprand1, int oprand2)
{
	switch (oper) {
		case '+':
			return oprand1 + oprand2;
		case '-':
			return oprand1 - oprand2;
		case '*':
			return oprand1 * oprand2;
		case '/':
			if (oprand2 == 0) {
				printf("除数不能为零\n");
				exit(EXIT_FAILURE);
			}
			return oprand1 / oprand2;
		case '%':
			if (oprand2 == 0) {
				printf("模数不能为零\n");
				exit(EXIT_FAILURE);
			}
			return oprand1 % oprand2;
		case '^':
			if (oprand2 < 0) return 0;
			int res = 1;
			for (int i = 0; i < oprand2; i++) {
				res *= oprand1;
			}
			return res;
	}

	return 0;
}

//初始化栈
Status InitStack(LinkStack * S)
{
	if (S == NULL)  return ERROR;
	*S = (StackNode *)malloc(sizeof(StackNode));
	if (*S == NULL) return ERROR;
	(*S)->next = NULL;
	return OK;
}

//入栈元素
Status Push(LinkStack S, ElemType e)
{
	if (S == NULL)  return ERROR;
	StackNode * cur = (StackNode *)malloc(sizeof(StackNode));
	if (NULL == cur)    return ERROR;
	cur->data = e;
	cur->next = S->next;
	S->next = cur;
	return OK;
}

//判断栈是否为空
bool IsEmpty(LinkStack S)
{
	if (NULL == S)  return true;
	return S->next == NULL;
}

//弹出元素
Status Pop(LinkStack S, ElemType * e)
{
	if (S == NULL || IsEmpty(S))    return ERROR;
	StackNode * cur = S->next;
	*e = cur->data;
	S->next = cur->next;
	free(cur);
	return OK;
}

// 打印栈中所有元素
void PrintPoLishStack(LinkStack S)
{
	if (S == NULL) {
		printf("栈未初始化！\n");
		return;
	}
	if (IsEmpty(S)) {
		printf("栈为空！\n");
		return;
	}

	LinkStack tempStack;
	InitStack(&tempStack);
	ElemType top_elem;
	while (!IsEmpty(S)) {
		Pop(S, &top_elem);
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
		}
		Push(S, top_elem);  // 恢复原栈
	}

	putchar('\n');

	DestroyStack(&tempStack);
}

//返回栈长度
int StackLength(LinkStack S)
{
	if (NULL == S)  return 0;

	int j = 0;
	for (StackNode * cur = S->next; cur ; cur = cur->next)
		j++;
	return j;
}

//返回栈顶元素
Status GetTop(LinkStack S, ElemType * e)
{
	if (S == NULL || IsEmpty(S))    return ERROR;
	*e = S->next->data;
	return OK;
}

//销毁链栈
Status DestroyStack(LinkStack * S)
{
	if (S == NULL || *S == NULL)    return ERROR;
	StackNode * cur = (*S)->next, *p;
	while (cur) {
		p = cur->next;
		free(cur);
		cur = p;
	}
	free(*S);
	*S = NULL;
	return OK;
}

//清空栈
Status ClearStack(LinkStack S)
{
	if (S == NULL)  return ERROR;
	StackNode * cur = S->next, *tmp;
	while (cur) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	S->next = NULL;
	return OK;
}

int GetPriority(char oper)
{
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

Status InfixToPostfix(const char *infix_str, LinkStack *out_postfix)
{
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
					if (top_elem.WhatIs == OPERATOR && top_elem.data.oper == '(')
						break;
					Pop(Operator, &now_elem);
					Push(*out_postfix, now_elem);
				}
				if (!IsEmpty(Operator))
					Pop(Operator, &top_elem); // 舍弃'('
				break;
			}
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			case '^': {
				while (!IsEmpty(Operator) && GetTop(Operator, &top_elem)) {
					if (top_elem.WhatIs != OPERATOR || top_elem.data.oper == '(')
						break;

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

// 判断是否为右结合运算符
bool IsRightAssoc(char oper)
{
	return oper == '^';
}

bool MatchParentheses(const char *infix_str)
{
	if (NULL == infix_str)	return false;
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

// 反转链栈（原地修改指针方向，无需额外空间）
Status ReverseStack(LinkStack S)
{
	if (NULL == S)	return ERROR;

	StackNode *cur = S->next, *pre = NULL, *next = NULL;
	while (cur) {
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}

	S->next = pre; // 头结点重新指向新的栈顶
	return OK;
}

