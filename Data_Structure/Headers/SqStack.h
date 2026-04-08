#ifndef __SQSTACK_H__
#define __SQSTACK_H__

#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	OK, ERROR
} Status;

typedef struct Stack {
	ElemType * data;
	int maxsize;
	int top;
} Stack;

typedef Stack* Stackptr;

Status InitStack(Stackptr * S, int n);
Status Push(Stackptr S, ElemType e);
Status Pop(Stackptr S, ElemType * e);
bool IsEmpty(Stackptr S);
int StackLength(Stackptr S);
bool IsFull(Stackptr S);
Status GetTop(Stackptr S, ElemType * e);
void PrintStack(Stackptr S);
Status DestroyStack(Stackptr * S);
Status ClearStack(Stackptr S);

#endif
