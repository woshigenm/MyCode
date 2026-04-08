#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__

#include <stdlib.h>
#include <stdbool.h>

typedef int Elemtype;
typedef enum {
	ERROR, OK
} Status;

typedef struct QueueNode {
	Elemtype data;
	struct QueueNode * next;
} QueueNode;

typedef struct LinkQueue {
	struct QueueNode * front;
	struct QueueNode * rear;
	int size;
} LinkQueue;

typedef LinkQueue * LinkQueuePtr;

// 函数声明
Status InitLinkQueue(LinkQueuePtr * Q);
bool IsEmpty(LinkQueuePtr Q);
Status EnQueue(LinkQueuePtr Q, Elemtype e);
Status DeQueue(LinkQueuePtr Q, Elemtype * e);
int QueueLength(LinkQueuePtr Q);
void Print(LinkQueuePtr Q);
Status GetHead(LinkQueuePtr Q, Elemtype * e);
Status DestroyQueue(LinkQueuePtr * Q);
Status ClearQueue(LinkQueuePtr Q);

#endif
