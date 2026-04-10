#include "../Headers/CSLinkList.h"
#include <stdio.h>
Status ListDeleteByNode(CSLinkList L, CSNode * Node, ElemType * e);
void Josephus(int n, int m);

int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m) == 2) {
		Josephus(n, m);
	}

	return 0;
}

Status ListDeleteByNode(CSLinkList L, CSNode * Node, ElemType * e)
{
	if (NULL == L || NULL == Node || IsEmpty(L))	return ERROR;
	CSNode * pre = L, * cur = pre->next;
	while (cur != L && cur != Node) {
		pre = pre->next;
		cur = cur->next;
	}

	if (cur == L)
		return ERROR;

	*e = cur->data;
	pre->next = cur->next;
	free(cur);
	return OK;
}

void Josephus(int n, int m)
{
	CSLinkList L;
	InitList(&L);

	int * result;

	if (n <= 0 || m <= 0) {
		return;
	}

	for (int i = 1; i <= n; ++i)
		ListInsert(L, i, i);

	result = (int *)malloc(sizeof(int) * n);

	CSNode * cur = NULL, *tmp = NULL;
	ElemType e;
	int j = 0;
	tmp = L->next;

	while (j < n) {
		cur = tmp;
		// i < m，表示走 m-1 步（数到 m 出列）
		for (int i = 1; i < m; ++i) {
			cur = cur->next;
			if (cur == L) {
				cur = cur->next;
			}
		}

		tmp = cur->next;
		if (tmp == L) {
			tmp = L->next;
		}

		ListDeleteByNode(L, cur, &e);
		result[j++] = e;
	}

	for (int i = 0; i < n; i++)
		printf("%d ", result[i]);
	putchar('\n');

	free(result);

	DestroyList(&L);
}
