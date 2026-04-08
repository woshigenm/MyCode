#ifndef __SQSTACK_H__
#define __SQSTACK_H__

#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	OK, ERROR
} Status;

#define MAXSIZE 128
typedef struct Stack {
	ElemType data[MAXSIZE];
	int top;
} Stack;

Status InitStack(Stack * S);
Status Push(Stack * S, ElemType e);
Status Pop(Stack * S, ElemType * e);
bool IsEmpty(Stack * S);
int StackLength(Stack * S);
bool IsFull(Stack * S);
Status GetTop(Stack * S, ElemType * e);
void PrintStack(Stack *S);

#endif
