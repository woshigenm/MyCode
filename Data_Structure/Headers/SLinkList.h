#ifndef __SLINKLIST_H__
#define __SLINKLIST_H__

#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	OK, ERROR
} Status;

#define MAXSIZES 64
typedef struct SNode {
	ElemType data;
	int cur;
} SNode, SLinkList[MAXSIZES];

Status InitList(SLinkList space);
int Malloc_SSL(SLinkList space);
int ListLength(SLinkList space);
Status ListInsert(SLinkList space, int i, ElemType e);
void Free_SSL(SLinkList space, int i);
Status ListDelete(SLinkList space, int i, ElemType * e);
void ListPrint(SLinkList space);
Status GetStaticElem(SLinkList space, int i, ElemType *e);
int LocateElem(SLinkList space, ElemType e);
void ClearList(SLinkList L);

#endif
