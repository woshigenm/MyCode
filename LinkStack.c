#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	OK, ERROR
} Status;

#define MAXSIZE 10
typedef struct StackNode {
	ElemType data;
	struct StackNode * next;
} StackNode, *LinkStack;

Status InitStack(LinkStack * S) {
	if (S == NULL)	return ERROR;
	*S = (StackNode *)malloc(sizeof(StackNode));
	if (*S == NULL) return ERROR;
	(*S)->next = NULL;
	return OK;  // 关键修复点2：返回正确状态
}

Status Push(LinkStack S, ElemType e) {
	if (S == NULL)	return ERROR;
	StackNode * cur = (StackNode *)malloc(sizeof(StackNode));
	if (NULL == cur)	return ERROR;
	cur->data = e;
	cur->next = S->next;
	S->next = cur;
	return OK;
}

bool IsEmpty(LinkStack S) {
	if (NULL == S)	return false;
	return S->next == NULL;
}

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
		printf("%d -> %p\n", cur->data, cur);
	printf("\n");
}

int StackLength(LinkStack S) {
	int j = 0;
	for (StackNode * cur = S->next; cur ; cur = cur->next)
		j++;
	return j;
}
Status GetTop(LinkStack S, ElemType * e) {
	if (S == NULL || IsEmpty(S))	return ERROR;
	*e = S->next->data;
	return OK;
}

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

//232433
int main() {
	LinkStack s;
	ElemType e;

	// 1. 初始化栈
	if (InitStack(&s) == OK) {
		printf("栈初始化成功！\n");
	}

	// 2. 入栈操作
	Push(s, 1);
	Push(s, 2);
	Push(s, 3);
	printf("入栈1、2、3后，栈长度：%d\n", StackLength(s));
	PrintStack(s);

	// 3. 获取栈顶元素
	if (GetTop(s, &e) == OK) {
		printf("当前栈顶元素：%d\n", e);
	}

	// 4. 出栈操作
	if (Pop(s, &e) == OK) {
		printf("弹出的栈顶元素：%d\n", e);
	}
	printf("出栈后，栈长度：%d\n", StackLength(s));
	PrintStack(s);

	// 5. 判空/判满测试
	printf("栈是否为空？%s\n", IsEmpty(s) ? "是" : "否");

	// 6. 填满栈测试
	for (int i = 4; i <= 10; i++) {
		Push(s, i);
	}
	printf("填满栈后，栈长度：%d\n", StackLength(s));
	PrintStack(s);

	// 7. 栈满时入栈测试
	Push(s, 11);

	// 8. 清空栈测试
	while (!IsEmpty(s)) {
		Pop(s, &e);
		printf("弹出元素：%d\n", e);
	}
	printf("清空栈后，栈是否为空？%s\n", IsEmpty(s) ? "是" : "否");
	return 0;
}
