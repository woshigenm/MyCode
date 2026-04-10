#include "../Headers/DoubleStack.h"
#include <stdio.h>

Status InitStack(DoubleStack * DStack, int maxsize)
{
	if (NULL == DStack)	return ERROR;
	*DStack = (DoubleStack)malloc(sizeof(struct DoubleStack));
	if (NULL == *DStack)	return ERROR;
	(*DStack)->data = (ElemType *)malloc(sizeof(ElemType) * maxsize);
	if (NULL == (*DStack)->data) {
		free(*DStack);
		DStack = NULL;
		return ERROR;
	}

	(*DStack)->top[0] = -1;
	(*DStack)->top[1] = maxsize;

	(*DStack)->maxsize = maxsize;
	return OK;
}

bool IsFull(DoubleStack DStack)
{
	return DStack == NULL ? false : DStack->top[0] + 1 == DStack->top[1];
}

bool IsEmpty(DoubleStack DStack, Which_Stack s)
{
	if (NULL == DStack)	return true;
	if (s == STACK1) {
		return DStack->top[0] == -1;
	}
	return DStack->top[1] == DStack->maxsize;
}

Status Push(DoubleStack DStack, Which_Stack s, ElemType e)
{
	if (NULL == DStack)	return ERROR;
	if (IsFull(DStack))	return ERROR;

	if (s == STACK1) {
		DStack->data[++DStack->top[0]] = e;
	} else if (s == STACK2) {
		DStack->data[--DStack->top[1]] = e;
	}else {
		return ERROR;
	}

	return OK;
}

Status Pop(DoubleStack DStack, Which_Stack s, ElemType * e)
{
	if (NULL == DStack)	return ERROR;
	if (IsEmpty(DStack, s))	return ERROR;

	if (s == STACK1) {
		*e = DStack->data[DStack->top[0]--];
	} else if (s == STACK2) {
		*e = DStack->data[DStack->top[1]++];
	}else {
		return ERROR;
	}

	return OK;
}

Status GetTop(DoubleStack DStack, Which_Stack s, ElemType * e)
{
	if (NULL == DStack)	return ERROR;
	if (IsEmpty(DStack, s))	return ERROR;

	if (s == STACK1) {
		*e = DStack->data[DStack->top[0]];
	} else if (s == STACK2) {
		*e = DStack->data[DStack->top[1]];
	}else {
		return ERROR;
	}

	return OK;
}

void StackPrint(DoubleStack DStack, Which_Stack s)
{
	if (NULL == DStack || IsEmpty(DStack, s)) {
		return;
	}

	if (s == STACK1) {
		for (int i = 0; i <= DStack->top[0]; i++) {
			printf("%d ", DStack->data[i]);
		}
	} else {
		for (int i = DStack->maxsize - 1; i >= DStack->top[1]; i--) {
			printf("%d ", DStack->data[i]);
		}
	}

	putchar('\n');
}

int StackLength(DoubleStack DStack, Which_Stack s)
{
	if (NULL == DStack)	return 0;
	if (s == STACK1)	return DStack->top[0] + 1;
	else return DStack->maxsize - DStack->top[1];
}

Status DestroyStack(DoubleStack * DStack)
{
	if (NULL == DStack)	return ERROR;
	if (NULL == *DStack)	return OK;

	if ((*DStack)->data != NULL) {
		free((*DStack)->data);
		(*DStack)->data = NULL;
	}

	free(*DStack);
	*DStack = NULL;

	return OK;
}

Status ClearStack(DoubleStack DStack)
{
	if (NULL == DStack)	return ERROR;

	DStack->top[0] = -1;
	DStack->top[1] = DStack->maxsize;

	return OK;
}

