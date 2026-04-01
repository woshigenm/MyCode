#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include <stdlib.h>
#include <stdbool.h>

typedef enum {
	OK, ERROR
} Status;

typedef int ElemType;
typedef struct {
	int *data;
	int MAXSIZE;
	int length;
} SqList;

Status InitList(SqList ** S, int n) ;
Status DestroyList(SqList ** S);
Status IncreaseList(SqList * S, int len);
Status ClearList(SqList * S);
bool ListEmpty(SqList * S);
int ListLength(SqList * S);
int GetElem(SqList * S, int i);
ElemType * GetAdd(SqList * S, int i);
int LocateElem(SqList * S, ElemType e);
Status PriorElem(SqList * S, ElemType cur_e, ElemType ** pre_e);
Status NextElem(SqList * S, ElemType cur_e, ElemType ** next_e);
Status ListInsert(SqList * S, int laction, ElemType data);
Status ListDelete(SqList * S, int laction, ElemType * e);
void ListPrint(SqList * S);

#endif
