#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

typedef int ElemType;
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
Status GetTop(LinkStack S, ElemType * e);
int StackLength(LinkStack S);
Status DestoryLinkStack(LinkStack * S);

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
	StackNode * cur = (*S)->next, *p;
	while (cur) {
		p = cur->next;
		free(cur);
		cur	= p;
	}
	free(*S);
	*S = NULL;
	return OK;
}

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

int Calculate(char oper, int oprand1, int oprand2) {
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
			return (int)powf(oprand1, oprand2);
	}

	return 0;
}

int main() {
	char str[1024];
	char * pstr = str;
	gets(str);

	ElemType oprand1, oprand2, top_oper, now_oper, reslut, Nothing;
	LinkStack Operator, Operand;
	InitStack(&Operator);
	InitStack(&Operand);

	while (*pstr) {
		if (isdigit(*pstr)) {
			int sum = 0;
			while (*pstr && isdigit(*pstr)) {
				sum = sum * 10 + (*pstr - '0');
				pstr++;
			}
			Push(Operand, sum);
		}

		switch (*pstr) {
			case ' ':
				pstr++;
				continue;
			case '(':
				Push(Operator, *pstr);
				break;
			case ')':
				while (GetTop(Operator, &top_oper) == OK && top_oper != '(') {
					Pop(Operator, &now_oper);
					Pop(Operand, &oprand2);
					Pop(Operand, &oprand1);
					reslut = Calculate(now_oper, oprand1, oprand2);
					Push(Operand, reslut);
				}
				Pop(Operator, &Nothing);//抛弃'('
				break;
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			case '^':
				while (!IsEmpty(Operator) && GetTop(Operator, &top_oper) == OK && top_oper != '(' && GetPriority(*pstr) <= GetPriority(top_oper)) {
					Pop(Operator, &now_oper);
					Pop(Operand, &oprand2);
					Pop(Operand, &oprand1);
					reslut = Calculate(now_oper, oprand1, oprand2);
					Push(Operand, reslut);
				}
				Push(Operator, *pstr);
				break;
		}
		pstr++;
	}

	while (!IsEmpty(Operator)) {
		Pop(Operator, &now_oper);
		Pop(Operand, &oprand2);
		Pop(Operand, &oprand1);
		reslut = Calculate(now_oper, oprand1, oprand2);
		Push(Operand, reslut);
	}

	if (Pop(Operand, &oprand1) == OK && IsEmpty(Operator)) {
		printf("%d\n", oprand1);
	} else {
		printf("表达式有误\n");
	}

	return 0;
}

