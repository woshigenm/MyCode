#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__

#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	ERROR, OK
} Status;

typedef struct QueueNode {
	ElemType data;
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
Status EnQueue(LinkQueuePtr Q, ElemType e);
Status DeQueue(LinkQueuePtr Q, ElemType * e);
int QueueLength(LinkQueuePtr Q);
void Print(LinkQueuePtr Q);
Status GetHead(LinkQueuePtr Q, ElemType * e);
Status DestroyQueue(LinkQueuePtr * Q);
Status ClearQueue(LinkQueuePtr Q);

#endif
