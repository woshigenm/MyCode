#ifndef __CSQUEUE_H__
#define __CSQUEUE_H__

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
} QueueNode, *CSqQueue;

// 函数声明
Status InitQueue(CSqQueue * Q, int n);
bool IsEmpty(CSqQueue Q);
bool IsFull(CSqQueue Q);
Status EnQueue(CSqQueue Q, Elemtype e);
Status DeQueue(CSqQueue Q, Elemtype * e);
int QueueLength(CSqQueue Q);
void Print(CSqQueue Q);
Status GetHead(CSqQueue Q, Elemtype * e);
Status DestroyQueue(CSqQueue * Q);
Status ClearQueue(CSqQueue Q);

#endif
