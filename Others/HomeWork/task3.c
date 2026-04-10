#include <stdio.h>
#include <stdlib.h>

typedef int Status;
typedef int ElemType;
enum {ERROR, OK};
typedef struct {
	int *data;
	int MAXSIZE;
	int length;
} SqList;

Status InitList(SqList * S, int n)
{
	S->data = (int *)malloc(sizeof(int) * n);
	S->MAXSIZE = n;
	S->length = 0;
	return OK;
}

Status ListInsert(SqList * S, int pos, ElemType data)
{
	if (S->length >= S->MAXSIZE)	return ERROR;
	if (pos < 0 || pos > S->length)	return ERROR;
	for (int i = S->length - 1; i >= pos; --i)
		S->data[i + 1] = S->data[i];
	S->data[pos] = data;
	S->length++;
	return OK;
}

void ListPrint(SqList * S)
{
	for (int i = 0; i < S->length; ++i)
		printf("%d ", S->data[i]);
	putchar('\n');
}

Status DestroyList(SqList * S)
{
	if (S == NULL) return ERROR;
	if (S->data != NULL) {
		free(S->data);
		S->data = NULL;
	}
	S->length = S->MAXSIZE = 0;
	return OK;
}

void Merge(SqList LA, SqList LB, SqList * LC)
{
	int i = 0, j = 0, k = 0;
	while (i < LA.length && j < LB.length) {
		if (LA.data[i] < LB.data[j]) {
			ListInsert(LC, k++, LA.data[i++]);
		} else if (LA.data[i] > LB.data[j]) {
			ListInsert(LC, k++, LB.data[j++]);
		} else {
			ListInsert(LC, k++, LA.data[i++]);
			j++;
			//ListInsert(LC, k++, LB.data[j++]);
		}
	}
	while (i < LA.length) 	ListInsert(LC, k++, LA.data[i++]);
	while (j < LB.length)	ListInsert(LC, k++, LB.data[j++]);
}

int main()
{
	SqList L1, L2, L3;
	InitList(&L1, 3);
	InitList(&L2, 6);
	InitList(&L3, L1.MAXSIZE + L2.MAXSIZE);

	ListInsert(&L1, 0, 3);
	ListInsert(&L1, 1, 5);
	ListInsert(&L1, 2, 8);

	ListInsert(&L2, 0, 0);
	ListInsert(&L2, 1, 3);
	ListInsert(&L2, 2, 7);
	ListInsert(&L2, 3, 8);
	ListInsert(&L2, 4, 9);
	ListInsert(&L2, 5, 12);

	Merge(L1, L2, &L3);
	ListPrint(&L3);

	DestroyList(&L1);
	DestroyList(&L2);
	DestroyList(&L3);
	return 0;
}
