#include "../Headers/SeqList.h"
#include <stdio.h>

//初始化线性表
Status InitList(SqList ** S, int n)
{
	*S = (SqList *)malloc(sizeof(SqList));
	if (NULL == *S)	return ERROR;
	(*S)->data = (int *)malloc(sizeof(int) * n);
	if (NULL == (*S)->data)	return ERROR;
	(*S)->MAXSIZE = n;
	(*S)->length = 0;
	return OK;
}

//销毁线性表
Status DestroyList(SqList ** S)
{
	if (NULL == S || NULL == *S) return ERROR;

	if ((*S)->data != NULL) {
		free((*S)->data);
		(*S)->data = NULL;  // 置空，避免野指针
	}

	(*S)->length = (*S)->MAXSIZE = 0;

	free(*S);
	*S = NULL;
	return OK;
}

//扩大线性表
Status IncreaseList(SqList * S, int len)
{
	if (NULL == S || len <= 0)	return ERROR;
	ElemType *tmp = (ElemType *)malloc((sizeof(ElemType) * (len + S->MAXSIZE)));
	if (NULL == tmp)	return ERROR;
	for (int i = 0; i < S->length; ++i)
		tmp[i] = S->data[i];
	free(S->data);
	S->MAXSIZE += len;
	S->data = tmp;
	return OK;
}

//重置线性表为空表
Status ClearList(SqList * S)
{
	if (NULL == S)	return ERROR;
	S->length = 0;
	return OK;
}

//返回线性表是否为空表
bool ListEmpty(SqList * S)
{
	return S ? S->length == 0 : false;
}

//返回线性表中元素个数
int ListLength(SqList * S)
{
	return S ? S->length : 0;
}

//按位取值
ElemType GetElem(SqList * S, int i)
{
	if (NULL == S || i < 1 || i > S->length) return 0;
	return S->data[i - 1];
}

//按位取结点地址值
ElemType * GetAdd(SqList * S, int i)
{
	if (NULL == S || i < 1 || i > S->length) return NULL;
	return &S->data[i - 1];
}

//查找元素e在线性表中的位序
int LocateElem(SqList * S, ElemType e)
{
	if (NULL == S)	return 0;
	for (int i = 1; i <= S->length; ++i) {
		if (e == S->data[i - 1])	return i;
	}
	return 0;
}

//查找cur_e 之前的前驱结点，返回 pre_e
Status PriorElem(SqList * S, ElemType cur_e, ElemType ** pre_e)
{
	if (NULL == S || NULL == pre_e)	return ERROR;
	*pre_e = NULL;
	int i = LocateElem(S, cur_e);
	if (i > 1 && i <= ListLength(S))
		*pre_e = GetAdd(S, i - 1);
	return OK;
}

//查找cur_e 之前的后驱结点，返回 next_e
Status NextElem(SqList * S, ElemType cur_e, ElemType ** next_e)
{
	if (NULL == S || NULL == next_e)	return ERROR;
	*next_e = NULL;
	int i = LocateElem(S, cur_e);
	if (i > 0 && i < ListLength(S))
		*next_e = GetAdd(S, i + 1);
	return OK;
}

//按位插入线性表元素
//location 为位序 1<=laction<=SqList->length + 1 当laction=SqList->length + 1为尾插
Status ListInsert(SqList * S, int laction, ElemType data)
{
	if (NULL == S || S->length >= S->MAXSIZE)	return ERROR;
	if (laction < 1 || laction > S->length + 1)	return ERROR;

	for (int i = S->length; i >= laction; --i)
		S->data[i] = S->data[i - 1];

	S->data[laction - 1] = data;
	S->length++;
	return OK;
}

//按位删除线性表元素
//location 为位序 1<=laction<=SqList->length
Status ListDelete(SqList * S, int laction, ElemType * e)
{
	if (NULL == S || NULL == e || S->length == 0)	return ERROR;
	if (laction < 1 || laction > S->length)	return ERROR;

	*e = S->data[laction - 1];
	for (int i = laction; i < S->length; ++i)
		S->data[i - 1] = S->data[i];

	S->length--;
	return OK;
}

//遍历表中元素
void ListPrint(SqList * S)
{
	if (NULL == S)	return;
	for (int i = 0; i < S->length; ++i)
		printf("%p -> %d\n", &S->data[i], S->data[i]);
	putchar('\n');
}
