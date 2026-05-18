#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
	OK, ERROR
} Status;

typedef struct Heap {
	int* heap_array;
	int size;
}*Heap;

#define BIG 1
#define SMALL 0
#define MODIFY_FUNCTION BIG

void swap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

Status InitHeap(Heap* heap, int* elem_array, int size)
{
	if (NULL == heap || NULL == elem_array || size <= 0)	return ERROR;
	
	*heap = (Heap)malloc(sizeof(struct Heap));
	if (NULL == *heap)	return ERROR;
	
	(*heap)->size = size;
	(*heap)->heap_array = (int*)malloc(sizeof(int) * size);
	if (NULL == (*heap)->heap_array)
	{
		free(*heap);
		*heap = NULL;
		
		return ERROR;
	}
	
	for (int i = 0; i < size; ++i)
	{
		(*heap)->heap_array[i] = elem_array[i];
	}
	
	return OK;
}

//向上调整
Status HeapInsert(Heap heap, int index)
{
	if (index >= heap->size)	return ERROR;//不存在该节点
	int parent = (index - 1) / 2;
	
	//大根堆
#if MODIFY_FUNCTION == BIG
	while (index > 0 && heap->heap_array[index] > heap->heap_array[parent])
	{
		swap(&heap->heap_array[index], &heap->heap_array[parent]);
		index = parent;
		parent = (index - 1) / 2;
	}
#else
	while (index > 0 && heap->heap_array[index] < heap->heap_array[parent])
	{
		swap(&heap->heap_array[index], &heap->heap_array[parent]);
		index = parent;
		parent = (index - 1) / 2;
	}
#endif
	return OK;
}

//向下调整
Status Heapify(Heap heap, int index)
{
	if (index >= heap->size)	return ERROR;
	int first_children = 2 * index + 1;
	
#if MODIFY_FUNCTION == BIG
	while (first_children < heap->size)
	{
		int left_or_right = first_children + 1 < heap->size && heap->heap_array[first_children + 1] > heap->heap_array[first_children] ? first_children + 1 : first_children;
		
		int max_index = heap->heap_array[index] > heap->heap_array[left_or_right] ? index : left_or_right; // 最大的下标
		if (max_index == index)	break;
		
		swap(&heap->heap_array[index], &heap->heap_array[max_index]);
		
		index = left_or_right;
		first_children = 2 * index + 1;
	}
#else
	while (first_children < heap->size)
	{
		int left_or_right = first_children + 1< heap->size && heap->heap_array[first_children + 1] < heap->heap_array[first_children] ? first_children + 1: first_children;
		
		int min_index = heap->heap_array[index] < heap->heap_array[left_or_right] ? index : left_or_right; // 最小的下标
		if (min_index == index)	break;
		
		swap(&heap->heap_array[index], &heap->heap_array[min_index]);
		
		index = left_or_right;
		first_children = 2 * index + 1;
	}
#endif
	
	return OK;
}

Status BuildHeap(Heap heap)
{
	for (int i = (heap->size - 1) / 2; i >= 0; --i)
	{
		Heapify(heap, i);
	}
	
	return OK;
}

Status HeapSort(Heap heap)
{
	BuildHeap(heap);
	while (heap->size > 1)
	{
		swap(&heap->heap_array[0], &heap->heap_array[--heap->size]);
		Heapify(heap, 0);
	}
	
	return OK;
}

#define SIZE 10
int main()
{
	Heap myheap;
	int array[SIZE] = {1,9,8,7,2,3,4,5,6,10};
	if (InitHeap(&myheap, array, SIZE) == ERROR)	return -1;
	
	BuildHeap(myheap);
	
	for (int i = 0; i < myheap->size; i++)
	{
		printf("%d ", myheap->heap_array[i]);
	}
	
	HeapSort(myheap);
	putchar('\n');
	
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", myheap->heap_array[i]);
	}
	
	return 0;
}

