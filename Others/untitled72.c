#include <stdio.h>
#include <stdlib.h>

int id = 1;

typedef struct QueueNode {
	int data;
	int id;
	struct QueueNode * next;
} QueueNode;

typedef struct Queue {
	QueueNode * head;
	QueueNode * tail;
} Queue;

void QueueInit(Queue * queue);

void QueueDestory(Queue * queue);

void swap(int * a, int * b);

void QueuePush(Queue * queue, int data);

void QueuePop(Queue * queue, int data);

int QueueFront(Queue * queue) {
	return queue->head->data;
}

int QueueBack(Queue * queue) {
	return queue->tail->data;
}

int QueueEmpty(Queue * queue) {
	return queue->head == NULL ? 1 : 0;
}

void QueueSelect(Queue * queue);

int QueueSize(Queue * queue);

void QueueSort(Queue * queue);

int QueueMax(Queue * queue, int target);

int main() {
	
	return 0;
}

void QueuePush(Queue * queue, int data) {
	QueueNode * Node = (QueueNode *)malloc(sizeof(QueueNode));
	if(NULL == Node) {
		printf("PUSH FAILD\n");
		return;
	}

	Node->data = data;
	Node->id = id++;
	Node->next = NULL;

	if(queue->head == NULL) {
		queue->head = queue->tail = Node;
	} else {
		queue->tail->next = Node;
		queue->tail = Node;
	}

	//QueueSort(queue);
}

int QueueSize(Queue * queue) {
	QueueNode* cur = queue->head;
	int size = 0;
	while (cur) {
		++size;
		cur = cur->next;
	}

	return size;
}

void QueuePop(Queue * queue, int data) {
	QueueNode * Cur = queue->head;

	QueueNode * temp = queue->head->next;

	if(queue->head->data == data) {
		free(queue->head);
		queue->head = temp;
		return;
	}

	while(NULL != Cur->next && Cur->next->data != data) {
		Cur = Cur->next;
	}

	if(Cur->next == NULL) {
		printf("Pop Failed\n");
		return;
	} else {
		Cur->next = Cur->next->next;
		free(Cur->next);
	}
}

void QueueDestory(Queue * queue) {
	QueueNode * Cur = queue->head;

	while(Cur) {
		QueueNode * next = Cur->next;
		free(Cur);
		Cur = next;
	}

	queue->tail = queue->head = NULL;
}

void QueueInit(Queue * queue) {
	queue->head = queue->tail = NULL;
}

void QueueSelect(Queue * queue) {
	if(QueueEmpty(queue)) {
		printf("The Queue Is NULL\n");
		return;
	}

	QueueNode * Cur = queue->head;

	while(Cur) {
		printf("[%d] %p -> %d\n", Cur->id, Cur, Cur->data);
		Cur = Cur->next;
	}

	putchar('\n');
}

void swap(int * a, int * b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int QueueMax(Queue * queue, int target) {
	QueueNode * Cur = queue->head;

	//QueueSort(queue);
	//QueueSelect(queue);

//	while(--target) {
//		Cur = Cur->next;
//	}

	int max = Cur->data;

	while(Cur->next != NULL) {
		if(Cur->data > max)
			max = Cur->data;
		Cur = Cur->next;
	}

	return max;
}

void QueueSort(Queue * queue) {
	if(QueueEmpty(queue)) {
		printf("The Queue Is NULL\n");
		return;
	}

	if(QueueSize(queue) <= 1) {
		return;
	}

	int flag;
	for(QueueNode * i = queue->head; i != NULL; i = i->next) {
		flag = 0;
		for(QueueNode * j = queue->head; j->next != NULL; j = j->next) {
			if(j->data < j->next->data) {
				swap(&j->data, &j->next->data);
				flag = 1;
			}
		}
		if(!flag)	break;
	}
}

