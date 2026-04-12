#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, an;

	printf("输入栈长度: ");
	scanf("%d", &n);
	if (n <= 0) {
		printf("栈长度必须为正整数！\n");
		return -1;
	}

	int * Stack = (int *)malloc(sizeof(int) * n);
	if (NULL == Stack) {
		printf("内存分配失败！\n");
		return -1;
	}

	int top = -1;
	while (scanf("%d", &an) == 1) {
		if (an != -1) {
			if (top < n - 1)
				Stack[++top] = an;
			else
				printf("栈满不可入栈\n");
		} else {
			if (top < 0) {
				printf("空栈不可输出\n");
			} else {
				printf("%d\n", Stack[top]);
				top--;
			}
		}
	}

	free(Stack);
	return 0;
}

