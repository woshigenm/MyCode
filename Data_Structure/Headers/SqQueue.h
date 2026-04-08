#ifndef __SQQUEUE_H__
#define __SQQUEUE_H__

#include <stdlib.h>
#include <stdbool.h>

typedef int Elemtype;
typedef enum {
	ERROR, OK
} Status;

typedef struct QueueNode {
	Elemtype * data;
	int front, rear;
	int maxsize;
} QueueNode, *SqQueue;

Status InitQueue(SqQueue *Q, int n);
bool IsEmpty(SqQueue Q);
bool IsFull(SqQueue Q);
Status EnQueue(SqQueue Q, Elemtype e);
Status DeQueue(SqQueue Q, Elemtype *e);
int QueueLength(SqQueue Q);
void Print(SqQueue Q);
Status GetHead(SqQueue Q, Elemtype *e);
Status DestroyQueue(SqQueue * Q);
Status ClearQueue(SqQueue Q);

#endif
