#ifndef __SINGLELIST_H__
#define __SINGLELIST_H__

#include <stdlib.h>
#include <stdbool.h>

// 元素类型定义
typedef int ElemType;

// 状态码定义
typedef enum {
	OK,
	ERROR
} Status;

// 单链表节点结构体
typedef struct Node {
	ElemType data;
	struct Node *next;
} Node, *LinkList;

/********** 单链表基础操作声明 **********/
// 初始化链表（带头结点）
Status InitList(LinkList *L);
// 获取第i个元素的值
Status GetElem(LinkList L, int i, ElemType *e);
// 获取第i个元素的节点地址
Status GetElemAd(LinkList L, int i, Node **e);
// 查找值为e的节点地址
Status LocateElem(LinkList L, ElemType e, Node **ep);
// 在第i个位置插入元素e
Status ListInsert(LinkList L, int i, ElemType e);
// 删除第i个元素，并用e返回其值
Status ListDelete(LinkList L, int i, ElemType *e);
// 头插法创建n个节点的链表
Status CreateList_H(LinkList *L, int n);
// 尾插法创建n个节点的链表
Status CreateList_R(LinkList *L, int n);
// 获取链表长度
int ListLength(LinkList L);
// 判断链表是否为空
bool ListEmpty(LinkList L);
// 打印链表
void ListPrint(LinkList L);
// 查找指定元素的前驱节点
Status PriorElem(LinkList L, ElemType cur_e, Node **pre_e);
// 查找指定元素的后继节点
Status NextElem(LinkList L, ElemType cur_e, Node **next_e);
// 清空链表（保留头结点）
Status ClearList(LinkList L);
// 销毁链表（释放所有节点）
Status DestroyList(LinkList *L);

/********** 扩展操作声明 **********/
// 在第i个节点**前面**插入元素
Status PriorInsert(LinkList L, int i, ElemType cur_e);
// 在第i个节点**后面**插入元素
Status NextInsert(LinkList L, int i, ElemType cur_e);
// 反转链表
Status ReverseList(LinkList L);
// 合并两个有序链表
Status MergeList(LinkList L1, LinkList L2);
// 链表向右旋转n个位置
Status RightRotate(LinkList L, int n);
// 判断链表是否有环
bool HasCycle(LinkList L);
// 找到环的入口节点
Node *FindCycle(LinkList L);
// 处理环（解开环）
Status HandleCycle(LinkList L);

#endif
