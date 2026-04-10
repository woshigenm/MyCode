#ifndef __DLINKQUEUE_H__
#define __DLINKQUEUE_H__

#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	ERROR, OK
} Status;

typedef enum {
	FRONT, REAR
} Which_Ended;

typedef struct DLinkQueueNode {
	ElemType data;
	struct DLinkQueueNode * prior;
	struct DLinkQueueNode * next;
} DLinkQueueNode;

typedef struct DLinkQueue {
	struct	DLinkQueueNode * front;
	struct	DLinkQueueNode * rear;
	int length;
}*DLinkQueue;

Status InitQueue(DLinkQueue * DLQ);
bool IsEmpty(DLinkQueue DLQ);
Status EnQueue(DLinkQueue DLQ, Which_Ended s, ElemType e);
Status DeQueue(DLinkQueue DLQ, Which_Ended s, ElemType * e);
int QueueLength(DLinkQueue DLQ);
void Print(DLinkQueue DLQ, Which_Ended s);
Status GetHead(DLinkQueue DLQ, Which_Ended s, ElemType * e);
Status DestroyQueue(DLinkQueue * DLQ);
Status ClearQueue(DLinkQueue DLQ);

#endif
