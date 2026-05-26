#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

typedef enum {
	OK, ERROR
}Status;

typedef struct HaffmanNode {
	int parent;
	int leftChild, rightChild;
	int weight;
}HaffmanNode;

typedef struct HaffmanTree
{
	struct HaffmanNode* Data;
	int size;
	int length;
} *HaffmanTree;

Status InitHaffmanTree(HaffmanTree* HT, int weight[], int size)
{
	if (NULL == HT|| size <= 0)	return  ERROR;
	
	*HT = (HaffmanTree)malloc(sizeof(struct HaffmanTree));
	if (NULL == *HT)	return ERROR;
	
	(*HT)->Data = (struct HaffmanNode*)malloc(sizeof(struct HaffmanNode) * (2 * size - 1));
	if (NULL == (*HT)->Data)
	{
		free(*HT);
		*HT = NULL;
		return ERROR;
	}
	
	(*HT)->size = 2 * size - 1;
	(*HT)->length = size;
	
	for (int i = 0; i < 2 * size - 1; ++i)
	{
		(*HT)->Data[i].weight = i < size ? weight[i] : INT_MAX;
		(*HT)->Data[i].parent = (*HT)->Data[i].leftChild = (*HT)->Data[i].rightChild = -1;
	}
	
	return OK;
}

int MinIndex(HaffmanTree HT, bool * visited, int limits)
{
	int minIdx = -1;
	int min = INT_MAX;
	for (int i = 0; i < limits; ++i)
	{
		if (!visited[i] && HT->Data[i].weight < min)
		{
			minIdx = i;
			min = HT->Data[i].weight;
		}
	}
	
	if (minIdx != -1) {
		visited[minIdx] = true;
	}
	
	return minIdx;
}

Status BuildHaffmanTree(HaffmanTree HT)
{
	bool* visited = (bool*)calloc(HT->size, sizeof(bool));
	if (!visited)	return ERROR;
	
	for (int i = HT->length; i < HT->size; ++i)
	{
		int LeftMinChild = MinIndex(HT, visited, i);
		int RightMinChild = MinIndex(HT, visited, i);
		
		if (LeftMinChild == -1 || RightMinChild == -1) {
			free(visited);
			return ERROR;
		}
		
		HT->Data[LeftMinChild].parent = i;
		HT->Data[RightMinChild].parent = i;
		
		HT->Data[i].weight = HT->Data[LeftMinChild].weight + HT->Data[RightMinChild].weight;
		HT->Data[i].leftChild = LeftMinChild;
		HT->Data[i].rightChild = RightMinChild;
		
	}
	
	free(visited);
	return OK;
}

void PrintHaffmanTree(HaffmanTree HT) // not travel
{
	printf("I\tP\tL\tR\tW\n");
	for (int i = 0; i < HT->size; ++i)
	{
		printf("%-4d\t%-4d\t%-4d\t%-4d\t%-4d\n", i, HT->Data[i].parent, HT->Data[i].leftChild, HT->Data[i].rightChild, HT->Data[i].weight);
	}
	
	putchar('\n');
}

Status DestroyHaffmanTree(HaffmanTree* HT)
{
	if (NULL == HT || NULL == *HT)	return ERROR;
	
	free((*HT)->Data);
	free(*HT);
	*HT = NULL;
	return OK;
}

void reverse(int array[], int size)
{
	for (int i = 0; i < size / 2; ++i)
	{
		int temp = array[i];
		array[i] = array[size - i - 1];
		array[size - i - 1] = temp;
	}
}

inline static int FindIndex(char **name, int size, char * target)
{
	if (!name || !target)	return -1;
	
	for (int i = 0; i < size; ++i)
	{
		if (!strcmp(name[i], target))
			return i;
	}
	return -1;
}

Status HaffmanTreeCode(HaffmanTree HT, char** names, int nameSize, char* target)
{
	if (!names || !target)	return ERROR;
	
	int* Path = (int*)malloc(sizeof(int)*HT->length);
	if (!Path)	return ERROR;
	
	int index = FindIndex(names, nameSize, target);
	if (index == -1) {
		free(Path);
		return ERROR;
	}
	
	int cnt = 0;
	int current = index;
	int parent = HT->Data[current].parent;
	while (parent != -1)
	{
		if (HT->Data[parent].leftChild == current)
		{
			Path[cnt] = 1;
		}
		else if(HT->Data[parent].rightChild == current)
		{
			Path[cnt] = 0;
		}
		
		current = parent;
		parent = HT->Data[parent].parent;
		cnt++;
	}
	
	reverse(Path, cnt);
	
	printf("%s ", target);
	for (int i = 0; i < cnt; ++i)
	{
		printf("%d", Path[i]);
	}
	putchar('\n');
	
	free(Path);
	return OK;
}

Status GenerateHaffmanCodeTable(HaffmanTree HT, char** codeTable)
{
	char* temp = (char*)malloc(sizeof(char) * (HT->length + 1));
	if (!temp) return ERROR;
	
	for (int i = 0; i < HT->length; ++i)
	{
		int cnt = 0;
		int current = i;
		int parent = HT->Data[current].parent;
		
		while (parent != -1)
		{
			if (HT->Data[parent].leftChild == current)
				temp[cnt] = '1';
			else
				temp[cnt] = '0';
			
			current = parent;
			parent = HT->Data[current].parent;
			cnt++;
		}
		
		codeTable[i] = (char*)malloc(sizeof(char) * (cnt + 1));
		if (!codeTable[i]) {
			for (int j = 0; j < i; ++j) {
				free(codeTable[j]);
			}
			free(temp);
			return ERROR;
		}
		
		codeTable[i][cnt] = '\0';
		for (int j = 0; j < cnt; ++j) {
			codeTable[i][j] = temp[cnt - j - 1];
		}
	}
	
	free(temp);
	return OK;
}

Status HaffmanTreeDecode(HaffmanTree HT, char** names, int nameSize, char* target)
{
	if (!HT || !target) return ERROR;
	
	int currentIdx = HT->size - 1;
	for (int i = 0; target[i]; ++i)
	{
		if (target[i] == '1')
			currentIdx = HT->Data[currentIdx].leftChild;
		else if (target[i] == '0')
			currentIdx = HT->Data[currentIdx].rightChild;
		else
		{
			printf("\n遇到非法字符 '%c'，解码终止\n", target[i]);
			return ERROR;
		}
		
		if (currentIdx == -1)
		{
			printf("\n编码无效，解码失败\n");
			return ERROR;
		}
		
		if (currentIdx < HT->length)
		{
			if (currentIdx < nameSize)
				printf("%s ", names[currentIdx]);
			else
			{
				printf("\n索引越界，解码失败\n");
				return ERROR;
			}
			
			currentIdx = HT->size - 1;
		}
	}
	
	if (currentIdx != HT->size - 1)
	{
		printf("\n[警告] 编码未消耗完或编码不完整，最后一个字符可能缺失\n");
		return ERROR;
	}
	
	putchar('\n');
	return OK;
}


int main()
{
	HaffmanTree HT1 = NULL;
	
	char* String1[] = { "A", "B", "C", "D", "E", "F" };
	int weight1[] = { 1, 4, 3, 4, 2, 2 };
	int size1 = sizeof(weight1) / sizeof(weight1[0]);
	
	if (InitHaffmanTree(&HT1, weight1, size1) != OK)
	{
		printf("HT1 初始化失败\n");
		return -1;
	}
	
	BuildHaffmanTree(HT1);
	PrintHaffmanTree(HT1);
	
	HaffmanTreeCode(HT1, String1, size1, "A");
	HaffmanTreeCode(HT1, String1, size1, "F");
	HaffmanTreeCode(HT1, String1, size1, "B");
	printf("\n");
	
	char* codeTable1[6];
	if (GenerateHaffmanCodeTable(HT1, codeTable1) == OK)
	{
		for (int i = 0; i < size1; ++i)
		{
			printf("%s : %s\n", String1[i], codeTable1[i]);
			free(codeTable1[i]);
		}
	}
	else
	{
		printf("HT1 生成编码表失败\n");
	}
	
	HaffmanTreeDecode(HT1, String1, size1, "00001111");
	
	printf("\n");
	DestroyHaffmanTree(&HT1);
	return 0;
}

