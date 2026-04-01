#ifndef __CSLINKLIST_H__
#define __CSLINKLIST_H__

#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	ERROR, OK
} Status;

typedef struct CSNode {
	ElemType data;
	struct CSNode * next;
} CSNode, *CSLinkList;

Status InitList(CSLinkList * L);
Status ListInsert(CSLinkList L, int i, ElemType e);
bool IsEmpty(CSLinkList L);
Status ListDelete(CSLinkList L, int i, ElemType * e);
int ListLength(CSLinkList L);
void ListPrint(CSLinkList  L);
Status ClearList(CSLinkList L);
Status DestroyList(CSLinkList * L);

#endif
