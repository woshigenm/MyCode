#include <stdio.h>
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

int main() {
	LinkStack S;
	ElemType e;

	printf("=== 链栈测试 ===\n\n");

	// 1. 初始化栈
	printf("1. 初始化栈\n");
	if (InitStack(&S) == OK) {
		printf("初始化成功！\n");
	} else {
		printf("初始化失败！\n");
		return 1;
	}
	printf("栈是否为空: %s\n\n", IsEmpty(S) ? "是" : "否");

	// 2. 入栈操作
	printf("2. 入栈操作\n");
	for (int i = 1; i <= 5; i++) {
		printf("入栈元素: %d\n", i * 10);
		Push(S, i * 10);
	}
	printf("\n");
	PrintStack(S);

	// 3. 获取栈顶元素
	printf("3. 获取栈顶元素\n");
	if (GetTop(S, &e) == OK) {
		printf("栈顶元素: %d\n\n", e);
	} else {
		printf("获取栈顶元素失败！\n\n");
	}

	// 4. 获取栈长度
	printf("4. 栈长度: %d\n\n", StackLength(S));

	// 5. 出栈操作
	printf("5. 出栈操作\n");
	for (int i = 0; i < 3; i++) {
		if (Pop(S, &e) == OK) {
			printf("出栈元素: %d\n", e);
		} else {
			printf("出栈失败！\n");
		}
	}
	printf("\n");
	PrintStack(S);

	// 6. 再次获取栈信息
	printf("6. 当前栈信息\n");
	printf("栈是否为空: %s\n", IsEmpty(S) ? "是" : "否");
	printf("栈长度: %d\n", StackLength(S));
	if (GetTop(S, &e) == OK) {
		printf("栈顶元素: %d\n\n", e);
	}

	// 7. 清空栈
	printf("7. 清空栈\n");
	if (ClearLinkStack(S) == OK) {
		printf("清空成功！\n");
	} else {
		printf("清空失败！\n");
	}
	printf("栈是否为空: %s\n", IsEmpty(S) ? "是" : "否");
	printf("栈长度: %d\n\n", StackLength(S));

	// 8. 销毁栈
	printf("8. 销毁栈\n");
	if (DestoryLinkStack(&S) == OK) {
		printf("销毁成功！\n");
	} else {
		printf("销毁失败！\n");
	}

	printf("\n=== 测试完成 ===\n");
	return 0;
}

//初始化栈
Status InitStack(LinkStack * S) {
	if (S == NULL)	return ERROR;
	*S = (StackNode *)malloc(sizeof(StackNode));
	if (*S == NULL) return ERROR;
	(*S)->next = NULL;
	return OK;
}

//入栈元素
Status Push(LinkStack S, ElemType e) {
	if (S == NULL)	return ERROR;
	StackNode * cur = (StackNode *)malloc(sizeof(StackNode));
	if (NULL == cur)	return ERROR;
	cur->data = e;
	cur->next = S->next;
	S->next = cur;
	return OK;
}

//判断栈是否为空
bool IsEmpty(LinkStack S) {
	if (NULL == S)	return true;
	return S->next == NULL;
}

//弹出元素
Status Pop(LinkStack S, ElemType * e) {
	if (S == NULL || IsEmpty(S))	return ERROR;
	StackNode * cur = S->next;
	*e = cur->data;
	S->next = cur->next;
	free(cur);
	return OK;
}

// 打印栈中所有元素（从栈底到栈顶）
void PrintStack(LinkStack S) {
	if (S == NULL || IsEmpty(S)) {
		printf("栈为空！\n");
		return;
	}
	printf("栈中元素（栈底→栈顶）：\n");
	for (StackNode * cur = S->next; cur ; cur = cur->next)
		printf("%d \n", cur->data);
	printf("\n");
}

//返回栈长度
int StackLength(LinkStack S) {
	if (NULL == S)	return 0;

	int j = 0;
	for (StackNode * cur = S->next; cur ; cur = cur->next)
		j++;
	return j;
}

//返回栈顶元素
Status GetTop(LinkStack S, ElemType * e) {
	if (S == NULL || IsEmpty(S))	return ERROR;
	*e = S->next->data;
	return OK;
}

//销毁链栈
Status DestoryLinkStack(LinkStack * S) {
	if (S == NULL || *S == NULL)	return ERROR;
	StackNode * cur = (*S)->next, *p;
	while (cur) {
		p = cur->next;
		free(cur);
		cur	= p;
	}
	free(*S);
	*S = NULL;
	return OK;
}

//清空栈
Status ClearLinkStack(LinkStack S) {
	if (S == NULL)	return ERROR;
	StackNode * cur = S->next, *tmp;
	while (cur) {
		tmp = cur->next;
		free(cur);
		cur	= tmp;
	}
	S->next = NULL;
	return OK;
}
