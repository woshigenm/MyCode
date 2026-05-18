#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FAILURE -1

typedef enum {
	OK, ERROR
} Status;

typedef struct UnionSet {
	char** UnionName;
	int* ParentIndex;
	int size;
}*UnionSet;

//代表结点ParentIndex数组内为负值，代表结点绝对值为集合数量
Status initunion(UnionSet * Union, char** EleName, int size)
{
	if (NULL == EleName || size <= 0)	return ERROR;
	
	*Union = (struct UnionSet *)malloc(sizeof(struct UnionSet));
	if (NULL == *Union)	return ERROR;
	
	(*Union)->ParentIndex = NULL;
	(*Union)->UnionName = NULL;
	(*Union)->size = 0;
	
	(*Union)->ParentIndex = (int*)malloc(sizeof(int) * size);
	if (NULL == (*Union)->ParentIndex)	goto cleanup;
	
	(*Union)->UnionName = (char**)calloc(size, sizeof(char*));
	if (NULL == (*Union)->UnionName)	goto cleanup;
	
	(*Union)->size = size;
	
	for (int i = 0; i < size; i++) {
		if (NULL == EleName[i])	goto cleanup;
		
		(*Union)->UnionName[i] = (char*)malloc(strlen(EleName[i]) + 1);
		if (NULL == (*Union)->UnionName[i])	goto cleanup;
		
		strcpy((*Union)->UnionName[i], EleName[i]);
		(*Union)->ParentIndex[i] = -1;
	}
	
	return OK;
	
	cleanup:
	if ((*Union)->UnionName != NULL) {
		for (int i = 0; i < (*Union)->size; i++) {
			free((*Union)->UnionName[i]);
		}
		free((*Union)->UnionName);
	}
	
	free((*Union)->ParentIndex);//free(NULL) c89/c99/c11支持
	
	free(*Union);
	*Union = NULL;
	
	return ERROR;
}

int find_index(UnionSet Union, char* target)
{
	for (int i = 0; i < Union->size; ++i) {
		if (!strcmp(target, Union->UnionName[i]))
			return i;
	}
	
	return FAILURE;
}

int find(UnionSet Union, char* target)
{
	if (NULL == target)	return FAILURE;
	
	int target_index = find_index(Union, target);
	if (target_index == FAILURE)
	{
		return FAILURE;
	}
	
	int root = target_index;
	while (Union->ParentIndex[root] >= 0)
	{
		root = Union->ParentIndex[root];
	}
	
	int curr = target_index;
	while (curr != root)
	{
		int next = Union->ParentIndex[curr];
		Union->ParentIndex[curr] = root;
		curr = next;
	}
	
	return root;
}

bool IsSameSet(UnionSet Union, char* target1, char* target2)
{
	if (NULL == target1 || NULL == target2)	return false;
	
	int root1 = find(Union, target1);
	int root2 = find(Union, target2);
	if (root1 == FAILURE || root2 == FAILURE)	return false;
	
	return root1 == root2;
}

Status MergeUnion(UnionSet Union, char* target1, char* target2)
{
	if (NULL == target1 || NULL == target2)	return ERROR;
	
	int target1_index = find(Union, target1);
	int target2_index = find(Union, target2);
	if (target1_index == FAILURE || target2_index == FAILURE)
	{
		return ERROR;
	}
	
	if (target1_index != target2_index)
	{
		if (Union->ParentIndex[target1_index] <= Union->ParentIndex[target2_index]) //target1_index 大
		{
			Union->ParentIndex[target1_index] += Union->ParentIndex[target2_index];
			Union->ParentIndex[target2_index] = target1_index;
		}
		else//target2_index 大
		{
			Union->ParentIndex[target2_index] += Union->ParentIndex[target1_index];
			Union->ParentIndex[target1_index] = target2_index;
		}
	}
	
	return OK;
}

static int find_helper(UnionSet Union, int index)
{
	if (Union->ParentIndex[index] < 0)
	{
		return index;
	}
	
	return Union->ParentIndex[index] = find_helper(Union, Union->ParentIndex[index]);
}

int find_recursive(UnionSet Union, char* target)
{
	if (NULL == target)	return FAILURE;
	
	int target_index = find_index(Union, target);
	if (target_index == FAILURE)
	{
		return FAILURE;
	}
	
	return find_helper(Union, target_index);
}

int main()
{
	UnionSet U1 = NULL;
	char* U1Name[] = { "A", "B", "C", "D", "E" };
	initunion(&U1, U1Name, sizeof(U1Name) / sizeof(U1Name[0]));
	
	int rootA = find(U1, "A");
	if (rootA != FAILURE) {
		printf("A's root: %s\n", U1->UnionName[rootA]);
	}
	
	printf("Is A and B same set (before merge)? %s\n", IsSameSet(U1, "A", "B") == true ? "true" : "false");
	MergeUnion(U1, "A", "B");
	MergeUnion(U1, "A", "C");
	MergeUnion(U1, "A", "D");
	printf("Is A and D same set (after merge)? %s\n", IsSameSet(U1, "A", "D") == true ? "true" : "false");
	
	return 0;
}

