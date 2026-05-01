#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ==================== 类型定义 ==================== */

typedef char TreeNodeData;
typedef enum { OK, ERROR } Status;
typedef enum { LINK, THREAD } ThreadTag;

typedef struct BTNode {
	TreeNodeData data;
	struct BTNode* lchild, * rchild;
	ThreadTag ltag, rtag;
} BTNode, * BTNodePtr;

typedef BTNodePtr StackElemType;
typedef struct StackNode {
	StackElemType data;
	struct StackNode* next;
} StackNode, * PStack;

typedef struct QueueNode {
	StackElemType data;
	struct QueueNode* next;
} QueueNode;

typedef struct LinkQueue {
	QueueNode* front;
	QueueNode* rear;
	int size;
} LinkQueue, * PQueue;


/* ==================== 栈函数声明 ==================== */

Status StackInit(PStack* stack);
Status StackPush(PStack stack, StackElemType elem);
bool StackIsEmpty(PStack stack);
Status StackPop(PStack stack, StackElemType* out_node);
Status StackGetTop(PStack stack, StackElemType* out_node);
Status StackDestroy(PStack* stack);


/* ==================== 队列函数声明 ==================== */

Status QueueInit(PQueue* queue);
bool QueueIsEmpty(PQueue queue);
Status QueueEnqueue(PQueue queue, StackElemType elem);
Status QueueDequeue(PQueue queue, StackElemType* out_node);
Status QueueGetFront(PQueue queue, StackElemType* out_node);
Status QueueDestroy(PQueue* queue);


/* ==================== 二叉树基础操作 ==================== */

Status TreeInit(BTNodePtr* root) {
	if (NULL == root) return ERROR;
	*root = NULL;
	return OK;
}

void TreeCreateByPreOrder(BTNodePtr* root) {
	char input;
	if (scanf(" %c", &input) != 1)
		exit(EXIT_FAILURE);
	if (input == '#') {
		*root = NULL;
	}
	else {
		*root = (BTNodePtr)malloc(sizeof(BTNode));
		if (*root == NULL) exit(EXIT_FAILURE);
		(*root)->data = input;
		(*root)->ltag = (*root)->rtag = LINK;
		(*root)->lchild = (*root)->rchild = NULL;
		TreeCreateByPreOrder(&(*root)->lchild);
		TreeCreateByPreOrder(&(*root)->rchild);
	}
}

// --- 递归遍历 ---
void TreePreOrder(BTNodePtr root) {
	if (root) {
		putchar(root->data); putchar(' ');
		TreePreOrder(root->lchild);
		TreePreOrder(root->rchild);
	}
}

void TreeInOrder(BTNodePtr root) {
	if (root) {
		TreeInOrder(root->lchild);
		putchar(root->data); putchar(' ');
		TreeInOrder(root->rchild);
	}
}

void TreePostOrder(BTNodePtr root) {
	if (root) {
		TreePostOrder(root->lchild);
		TreePostOrder(root->rchild);
		putchar(root->data); putchar(' ');
	}
}

// --- 树属性计算 ---
int TreeGetDepth(BTNodePtr root) {
	if (root == NULL) return 0;
	int left_depth = TreeGetDepth(root->lchild);
	int right_depth = TreeGetDepth(root->rchild);
	return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

int TreeGetLeafCount(BTNodePtr root) {
	if (root == NULL) return 0;
	if (root->lchild == NULL && root->rchild == NULL) return 1;
	return TreeGetLeafCount(root->lchild) + TreeGetLeafCount(root->rchild);
}

int TreeGetNodeCount(BTNodePtr root) {
	if (root == NULL) return 0;
	return TreeGetNodeCount(root->lchild) + TreeGetNodeCount(root->rchild) + 1;
}

int TreeGetDegreeOneCount(BTNodePtr root) {
	if (root == NULL) return 0;
	if ((root->lchild == NULL && root->rchild != NULL) ||
		(root->lchild != NULL && root->rchild == NULL))
		return 1;
	return TreeGetDegreeOneCount(root->lchild) + TreeGetDegreeOneCount(root->rchild);
}

// --- 销毁与清理 ---
static void TreeDestroyInternal(BTNodePtr* root) {
	if (*root) {
		TreeDestroyInternal(&(*root)->lchild);
		TreeDestroyInternal(&(*root)->rchild);
		free(*root);
		*root = NULL;
	}
}

Status TreeClear(BTNodePtr* root) {
	if (root == NULL) return ERROR;
	TreeDestroyInternal(root);
	return OK;
}


/* ==================== 线索二叉树操作 ==================== */

static BTNodePtr g_pre_node = NULL;
void TreeInThread(BTNodePtr root) {
	if (root) {
		TreeInThread(root->lchild);
		
		if (root->lchild == NULL) {
			root->lchild = g_pre_node;
			root->ltag = THREAD;
		}
		
		if (g_pre_node != NULL && g_pre_node->rchild == NULL) {
			g_pre_node->rchild = root;
			g_pre_node->rtag = THREAD;
		}
		
		g_pre_node = root;
		TreeInThread(root->rchild);
	}
}

void TreeCopy(BTNodePtr* dest, BTNodePtr src) {
	if (src) {
		*dest = (BTNodePtr)malloc(sizeof(BTNode));
		if (*dest == NULL) exit(EXIT_FAILURE);
		(*dest)->data = src->data;
		(*dest)->ltag = src->ltag;
		(*dest)->rtag = src->rtag;
		(*dest)->lchild = (*dest)->rchild = NULL;
		TreeCopy(&(*dest)->lchild, src->lchild);
		TreeCopy(&(*dest)->rchild, src->rchild);
	}
	else {
		*dest = NULL;
	}
}

void TreeInOrderThreaded(BTNodePtr root) {
	BTNodePtr curr = root;
	while (curr) {
		while (curr->ltag == LINK) curr = curr->lchild;
		
		putchar(curr->data); putchar(' ');
		while (curr->rtag == THREAD) {
			curr = curr->rchild;
			putchar(curr->data); putchar(' ');
		}
		curr = curr->rchild;
	}
}

void TreeDestroyThreaded(BTNodePtr* root) {
	if (root == NULL || *root == NULL) return;
	BTNodePtr curr = *root;
	while (curr) {
		while (curr->ltag == LINK) curr = curr->lchild;
		
		BTNodePtr to_free = curr;
		BTNodePtr next = curr->rchild;
		ThreadTag next_type = curr->rtag;
		
		free(to_free);
		curr = next;
		
		while (curr && next_type == THREAD) {
			to_free = curr;
			next = curr->rchild;
			next_type = curr->rtag;
			free(to_free);
			curr = next;
		}
	}
	*root = NULL;
}


/* ==================== 非递归遍历 ==================== */

void TreePreOrderByStack(BTNodePtr root) {
	if (root == NULL) return;
	PStack stack;
	StackInit(&stack);
	StackPush(stack, root);
	
	BTNodePtr top_node = NULL;
	while (!StackIsEmpty(stack)) {
		StackPop(stack, &top_node);
		printf("%c ", top_node->data);
		
		if (top_node->rchild != NULL) StackPush(stack, top_node->rchild);
		if (top_node->lchild != NULL) StackPush(stack, top_node->lchild);
	}
	StackDestroy(&stack);
}

void TreeInOrderByStack(BTNodePtr root) {
	if (root == NULL) return;
	PStack stack;
	StackInit(&stack);
	
	BTNodePtr curr = root;
	while (curr != NULL || !StackIsEmpty(stack)) {
		if (curr != NULL) {
			StackPush(stack, curr);
			curr = curr->lchild;
		}
		else {
			StackPop(stack, &curr);
			printf("%c ", curr->data);
			curr = curr->rchild;
		}
	}
	StackDestroy(&stack);
}

void TreePostOrderByTwoStacks(BTNodePtr root) {
	if (root == NULL) return;
	PStack stack1, stack2;
	StackInit(&stack1);
	StackInit(&stack2);
	
	StackPush(stack1, root);
	
	BTNodePtr top_node = NULL;
	while (!StackIsEmpty(stack1)) {
		StackPop(stack1, &top_node);
		StackPush(stack2, top_node);
		
		if (top_node->lchild != NULL) StackPush(stack1, top_node->lchild);
		if (top_node->rchild != NULL) StackPush(stack1, top_node->rchild);
	}
	
	while (!StackIsEmpty(stack2)) {
		StackPop(stack2, &top_node);
		printf("%c ", top_node->data);
	}
	
	StackDestroy(&stack1);
	StackDestroy(&stack2);
}

// 采用了无懈可击的逻辑，初始化为 NULL 也绝对安全
void TreePostOrderByOneStack(BTNodePtr root) {
	if (root == NULL) return;
	PStack stack;
	StackInit(&stack);
	
	BTNodePtr curr = root;
	BTNodePtr prev = NULL;
	StackPush(stack, curr);
	
	while (!StackIsEmpty(stack)) {
		StackGetTop(stack, &curr);
		
		if (curr->lchild != NULL &&
			curr->lchild != prev &&
			(curr->rchild == NULL || curr->rchild != prev)) {
			StackPush(stack, curr->lchild);
		}
		else if (curr->rchild != NULL && curr->rchild != prev) {
			StackPush(stack, curr->rchild);
		}
		else {
			StackPop(stack, &curr);
			printf("%c ", curr->data);
			prev = curr;
		}
	}
	
	StackDestroy(&stack);
}

void TreeLevelOrder(BTNodePtr root) {
	PQueue queue;
	QueueInit(&queue);
	
	BTNodePtr curr = root;
	QueueEnqueue(queue, curr);
	
	while (!QueueIsEmpty(queue)) {
		QueueDequeue(queue, &curr);
		printf("%c ", curr->data);
		if (curr->lchild != NULL) QueueEnqueue(queue, curr->lchild);
		if (curr->rchild != NULL) QueueEnqueue(queue, curr->rchild);
	}
	
	QueueDestroy(&queue);
}


/* ==================== 栈与队列的具体实现 ==================== */

Status StackInit(PStack* stack) {
	if (stack == NULL) return ERROR;
	*stack = (PStack)malloc(sizeof(StackNode));
	if (*stack == NULL) return ERROR;
	(*stack)->next = NULL;
	return OK;
}

Status StackPush(PStack stack, StackElemType elem) {
	if (stack == NULL) return ERROR;
	StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
	if (NULL == new_node) return ERROR;
	new_node->data = elem;
	new_node->next = stack->next;
	stack->next = new_node;
	return OK;
}

bool StackIsEmpty(PStack stack) {
	if (NULL == stack) return true;
	return stack->next == NULL;
}

Status StackPop(PStack stack, StackElemType* out_node) {
	if (stack == NULL || StackIsEmpty(stack)) return ERROR;
	StackNode* temp = stack->next;
	*out_node = temp->data;
	stack->next = temp->next;
	free(temp);
	return OK;
}

Status StackGetTop(PStack stack, StackElemType* out_node) {
	if (stack == NULL || StackIsEmpty(stack)) return ERROR;
	*out_node = stack->next->data;
	return OK;
}

Status StackDestroy(PStack* stack) {
	if (stack == NULL || *stack == NULL) return ERROR;
	StackNode* curr = (*stack)->next, * temp;
	while (curr) {
		temp = curr->next;
		free(curr);
		curr = temp;
	}
	free(*stack);
	*stack = NULL;
	return OK;
}

Status QueueInit(PQueue* queue) {
	if (NULL == queue) return ERROR;
	*queue = (PQueue)malloc(sizeof(LinkQueue));
	if (NULL == *queue) return ERROR;
	(*queue)->front = (*queue)->rear = NULL;
	(*queue)->size = 0;
	return OK;
}

bool QueueIsEmpty(PQueue queue) {
	return queue == NULL || queue->front == NULL;
}

Status QueueEnqueue(PQueue queue, StackElemType elem) {
	if (queue == NULL) return ERROR;
	QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
	if (new_node == NULL) return ERROR;
	new_node->data = elem;
	new_node->next = NULL;
	
	if (QueueIsEmpty(queue)) {
		queue->front = new_node;
	}
	else {
		queue->rear->next = new_node;
	}
	queue->rear = new_node;
	queue->size++;
	return OK;
}

Status QueueDequeue(PQueue queue, StackElemType* out_node) {
	if (queue == NULL || QueueIsEmpty(queue)) return ERROR;
	QueueNode* temp = queue->front;
	*out_node = temp->data;
	queue->front = temp->next;
	free(temp);
	queue->size--;
	if (queue->front == NULL) queue->rear = NULL;
	return OK;
}

Status QueueGetFront(PQueue queue, StackElemType* out_node) {
	if (NULL == queue || NULL == out_node || QueueIsEmpty(queue)) return ERROR;
	*out_node = queue->front->data;
	return OK;
}

Status QueueDestroy(PQueue* queue) {
	if (NULL == queue || NULL == *queue) return ERROR;
	QueueNode* curr = (*queue)->front, * temp = NULL;
	while (curr) {
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(*queue);
	*queue = NULL;
	return OK;
}


/* ==================== 主函数测试 ==================== */

//A B D # # E # # C # #
//A # C # D # #
//A B C # # # #
int main() {
	BTNodePtr root;
	TreeInit(&root);
	TreeCreateByPreOrder(&root);
	
	printf("前序: \n");
	TreePreOrder(root); putchar('\n');
	TreePreOrderByStack(root); putchar('\n');
	
	printf("中序: \n");
	TreeInOrder(root); putchar('\n');
	TreeInOrderByStack(root); putchar('\n');
	
	printf("后序: \n");
	TreePostOrder(root); putchar('\n');
	TreePostOrderByOneStack(root); putchar('\n');
	TreePostOrderByTwoStacks(root); putchar('\n');
	
	printf("层序:\n");
	TreeLevelOrder(root); putchar('\n');
	
	printf("线索化中序:\n");
	TreeInThread(root);
	TreeInOrderThreaded(root); putchar('\n');
	g_pre_node = NULL;
	TreeDestroyThreaded(&root);
	
	return 0;
}

