#include "../Headers/SqStack.h"
#include <stdio.h>

//初始化栈
Status InitStack(Stackptr * S, int n)
{
	if (NULL == S || n <= 0) return ERROR;
	*S = (Stackptr)malloc(sizeof(struct Stack));
	if (NULL == *S)	return ERROR;
	(*S)->data = (ElemType *)malloc(sizeof(ElemType) * n);
	if (NULL == (*S)->data) {
		free(*S);
		*S = NULL;
		return ERROR;
	}
	(*S)->maxsize = n;
	(*S)->top = -1;
	return OK;
}

//判断栈是否为满
bool IsFull(Stackptr S)
{
	return S != NULL && (S->top + 1 == S->maxsize);
}

//判断栈是否为空
bool IsEmpty(Stackptr S)
{
	return S == NULL || S->top == -1;
}

//元素入栈
Status Push(Stackptr S, ElemType e)
{
	if (NULL == S) return ERROR;
	if (IsFull(S))	return ERROR;
	S->data[++S->top] = e;
	return OK;
}

//元素弹栈
Status Pop(Stackptr S, ElemType * e)
{
	if (NULL == S || NULL == e) return ERROR;
	if (IsEmpty(S))	return ERROR;
	*e = S->data[S->top--];
	return OK;
}

//返回栈长度
int StackLength(Stackptr S)
{
	if (NULL == S)	return 0;
	return S->top + 1;
}

//返回栈顶元素
Status GetTop(Stackptr S, ElemType * e)
{
	if (NULL == S || NULL == e) return ERROR;
	if (IsEmpty(S)) return ERROR;
	*e = S->data[S->top];
	return OK;
}

// 打印栈中所有元素（从栈底到栈顶）
void PrintStack(Stackptr S)
{
	if (NULL == S) {
		printf("栈未初始化!\n");
		return;
	}

	if (IsEmpty(S)) {
		printf("栈为空!\n");
		return;
	}

	for (int i = 0; i <= S->top; i++) {
		printf("%d ", S->data[i]);
	}

	putchar('\n');
}

Status DestroyStack(Stackptr * S)
{
	if (NULL == S || NULL == *S)	return ERROR;
	if (NULL != (*S)->data) {
		free((*S)->data);
	}

	free(*S);
	*S = NULL;
	return OK;
}

Status ClearStack(Stackptr S)
{
	if (NULL == S)	return ERROR;
	S->top = -1;
	return OK;
}
