#ifndef __CSQUEUE_H__
#define __CSQUEUE_H__

#include <stdlib.h>
#include <stdbool.h>

typedef int Elemtype;
typedef enum {
	ERROR, OK
} Status;

#define MAXSIZE 1024
typedef struct QueueNode {
	Elemtype data[MAXSIZE];
	int front, rear;
} QueueNode, SqQueue;

Status InitQueue(SqQueue * Q);
bool IsEmpty(SqQueue * Q);
bool IsFull(SqQueue * Q);
Status EnQueue(SqQueue * Q, Elemtype e);
Status DeQueue(SqQueue * Q, Elemtype * e);
int QueueLength(SqQueue * Q);
void Print(SqQueue * Q);
Status GetFront(SqQueue * Q, Elemtype * e);
#endif
