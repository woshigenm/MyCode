#ifndef __LINKSTACK_H__
#define __LINKSTACK_H__

#include <stdlib.h>
#include <stdbool.h>

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
void PrintStack(LinkStack S);
Status GetTop(LinkStack S, ElemType * e);
int StackLength(LinkStack S);
Status DestoryLinkStack(LinkStack * S);
Status ClearLinkStack(LinkStack S);

#endif
