#ifndef __DOUBLESTACK_H__
#define __DOUBLESTACK_H__

#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	ERROR, OK
} Status;

typedef enum Which_Stack {
	STACK1, STACK2
} Which_Stack;

typedef struct DoubleStack {
	int top[2];
	ElemType * data;
	int maxsize;
} *DoubleStack;

Status InitStack(DoubleStack * DStack, int maxsize);
bool IsFull(DoubleStack DStack);
bool IsEmpty(DoubleStack DStack, Which_Stack s);
Status Pop(DoubleStack DStack, Which_Stack s, ElemType * e);
Status Push(DoubleStack DStack, Which_Stack s, ElemType e);
void StackPrint(DoubleStack DStack, Which_Stack s);
Status GetTop(DoubleStack DStack, Which_Stack s, ElemType * e);
int StackLength(DoubleStack DStack, Which_Stack s);
Status ClearStack(DoubleStack S);
Status DestroyStack(DoubleStack * DStack);

#endif
