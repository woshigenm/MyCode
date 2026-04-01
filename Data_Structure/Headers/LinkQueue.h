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

#endif
