#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef enum { OK, ERROR } Status;
typedef enum { DIRECTED, UNDIRECTED } GraphDirection;

#define FAILURE -1
#define INF INT32_MAX

// ==================== 图结构定义 ====================
typedef struct Graph {
	char** names;      // 顶点名称数组
	int** edges;      // 邻接矩阵
	int     vertexNum;  // 顶点数
	int     edgeNum;    // 边数
	GraphDirection direction;
}*Graph;

Status InitGraph(Graph* G, char** names, int vNum, GraphDirection direction)
{
	if (NULL == G || NULL == names || vNum < 0) return ERROR;

	*G = (Graph)malloc(sizeof(struct Graph));
	if (NULL == *G) goto cleanup;

	(*G)->edges = NULL;
	(*G)->names = NULL;
	(*G)->vertexNum = vNum;
	(*G)->direction = direction;
	(*G)->edgeNum = 0;

	(*G)->names = (char**)calloc(vNum, sizeof(char*));
	if (NULL == (*G)->names) goto cleanup;

	(*G)->edges = (int**)calloc(vNum, sizeof(int*));
	if (NULL == (*G)->edges) goto cleanup;

	for (int i = 0; i < vNum; ++i) {
		if (NULL == names[i]) goto cleanup;

		(*G)->names[i] = (char*)malloc(strlen(names[i]) + 1);
		if (NULL == (*G)->names[i]) goto cleanup;
		strcpy((*G)->names[i], names[i]);

		(*G)->edges[i] = (int*)malloc(sizeof(int) * vNum);
		if (NULL == (*G)->edges[i]) goto cleanup;

		for (int j = 0; j < vNum; ++j) (*G)->edges[i][j] = INF;
	}
	return OK;

cleanup:
	if (NULL != *G) {
		if (NULL != (*G)->names) {
			for (int i = 0; i < vNum; ++i) free((*G)->names[i]);
			free((*G)->names);
		}
		if (NULL != (*G)->edges) {
			for (int i = 0; i < vNum; ++i) free((*G)->edges[i]);
			free((*G)->edges);
		}
		free(*G);
		*G = NULL;
	}
	return ERROR;
}

inline static int FindVertexIndex(Graph G, char* name)
{
	for (int i = 0; i < G->vertexNum; ++i) {
		if (strcmp(G->names[i], name) == 0) return i;
	}
	return FAILURE;
}

Status AddWeightedEdge(Graph G, char* fromVertex, char* toVertex, int weight)
{
	if (NULL == fromVertex || NULL == toVertex) return ERROR;

	int fromIdx = FindVertexIndex(G, fromVertex);
	int toIdx = FindVertexIndex(G, toVertex);
	if (fromIdx == FAILURE || toIdx == FAILURE) return ERROR;

	if (G->edges[fromIdx][toIdx] == INF) G->edgeNum++;

	G->edges[fromIdx][toIdx] = weight;
	if (G->direction == UNDIRECTED) {
		G->edges[toIdx][fromIdx] = weight;
	}
	return OK;
}

Status AddEdge(Graph G, char* fromVertex, char* toVertex)
{
	return AddWeightedEdge(G, fromVertex, toVertex, 1);
}

Status DestroyGraph(Graph* G)
{
	if (NULL == G || NULL == *G) return ERROR;

	for (int i = 0; i < (*G)->vertexNum; ++i) {
		free((*G)->names[i]);
		free((*G)->edges[i]);
	}
	free((*G)->names);
	free((*G)->edges);

	free(*G);
	*G = NULL;
	return OK;
}

// 专门为 Kruskal 统计无向图真实边数 (不重复计算)
inline static int CountUndirectedEdges(Graph G)
{
	int count = 0;
	for (int i = 0; i < G->vertexNum; ++i) {
		for (int j = i + 1; j < G->vertexNum; ++j) {
			if (G->edges[i][j] != INF) count++;
		}
	}
	return count;
}

void PrintGraphMatrix(Graph G)
{
	for (int i = 0; i < G->vertexNum; ++i) {
		for (int j = 0; j < G->vertexNum; ++j) {
			if (G->edges[i][j] == INF) printf("INF\t");
			else printf("%d\t", G->edges[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');
}

int GetOutDegree(Graph G, int* degreeArray)
{
	if (NULL == degreeArray || G->direction != DIRECTED) return FAILURE;

	int edgeCnt = 0;
	memset(degreeArray, 0, sizeof(int) * G->vertexNum);

	for (int i = 0; i < G->vertexNum; ++i) {
		for (int j = 0; j < G->vertexNum; ++j) {
			if (G->edges[i][j] != INF) {
				degreeArray[i]++;
				edgeCnt++;
			}
		}
	}
	return edgeCnt;
}

int GetInDegree(Graph G, int* degreeArray)
{
	if (NULL == degreeArray || G->direction != DIRECTED) return FAILURE;

	int edgeCnt = 0;
	memset(degreeArray, 0, sizeof(int) * G->vertexNum);

	for (int i = 0; i < G->vertexNum; ++i) {
		for (int j = 0; j < G->vertexNum; ++j) {
			if (G->edges[j][i] != INF) {
				degreeArray[i]++;
				edgeCnt++;
			}
		}
	}
	return edgeCnt;
}

int GetDegree(Graph G, int* degreeArray)
{
	if (NULL == degreeArray) return FAILURE;

	memset(degreeArray, 0, sizeof(int) * G->vertexNum);

	int edgeCnt = 0;
	if (G->direction == DIRECTED) {
		for (int i = 0; i < G->vertexNum; ++i) {
			for (int j = 0; j < G->vertexNum; ++j) {
				if (G->edges[i][j] != INF) {
					degreeArray[i]++; // 出度
					degreeArray[j]++; // 入度
					edgeCnt++;
				}
			}
		}
		return edgeCnt;
	}

	for (int i = 0; i < G->vertexNum; ++i) {
		for (int j = i; j < G->vertexNum; ++j) { // j 从 i 开始遍历上三角含对角线
			if (G->edges[i][j] != INF) {
				if (i == j) {
					degreeArray[i] += 2; // 自环度数加2
				} else {
					degreeArray[i]++;
					degreeArray[j]++; // 两端度数各加1
				}
				edgeCnt++;
			}
		}
	}
	return edgeCnt;
}


// ==================== 最小堆定义 ====================
typedef struct EdgeInfo {
	char* from;
	char* to;
	int   weight;
} EdgeInfo;

typedef struct MinHeap {
	EdgeInfo* data;
	int       size;
	int       capacity;
}*MinHeap;

void SwapEdge(EdgeInfo* a, EdgeInfo* b)
{
	EdgeInfo temp = *a;
	*a = *b;
	*b = temp;
}

Status InitMinHeap(MinHeap* heap, int capacity)
{
	if (NULL == heap || capacity <= 0) return ERROR;
	*heap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
	if (NULL == *heap) return ERROR;

	(*heap)->size = 0;
	(*heap)->capacity = capacity;
	(*heap)->data = (EdgeInfo*)malloc(sizeof(struct EdgeInfo) * capacity);
	if (NULL == (*heap)->data) {
		free(*heap);
		*heap = NULL;
		return ERROR;
	}
	return OK;
}

Status InsertHeap(MinHeap heap, EdgeInfo edge)
{
	if (heap->size >= heap->capacity) return ERROR;

	int idx = heap->size;
	heap->data[idx] = edge;
	heap->size++;

	int parent = (idx - 1) / 2;
	while (idx > 0 && heap->data[idx].weight < heap->data[parent].weight) {
		SwapEdge(&heap->data[idx], &heap->data[parent]);
		idx = parent;
		parent = (idx - 1) / 2;
	}
	return OK;
}

Status ExtractMin(MinHeap heap, EdgeInfo* outEdge)
{
	if (heap->size <= 0) return ERROR;

	*outEdge = heap->data[0];
	heap->size--;

	if (heap->size > 0) {
		heap->data[0] = heap->data[heap->size];
		// Heapify down
		int idx = 0;
		int leftChild = 2 * idx + 1;
		while (leftChild < heap->size) {
			int rightChild = leftChild + 1;
			int minChild = (rightChild < heap->size && heap->data[rightChild].weight < heap->data[leftChild].weight)
			               ? rightChild : leftChild;

			if (heap->data[idx].weight <= heap->data[minChild].weight) break;

			SwapEdge(&heap->data[idx], &heap->data[minChild]);
			idx = minChild;
			leftChild = 2 * idx + 1;
		}
	}
	return OK;
}

Status DestroyMinHeap(MinHeap* heap)
{
	if (NULL == heap || NULL == *heap) return ERROR;
	for (int i = 0; i < (*heap)->size; i++) {
		free((*heap)->data[i].from);
		free((*heap)->data[i].to);
	}
	free((*heap)->data);
	free(*heap);
	*heap = NULL;
	return OK;
}


// ==================== 并查集定义 ====================
typedef struct DisjointSet {
	char** names;
	int* parent;
	int    size;
}*DisjointSet;

Status InitDisjointSet(DisjointSet* ds, char** names, int size)
{
	if (NULL == names || size <= 0) return ERROR;

	*ds = (DisjointSet)malloc(sizeof(struct DisjointSet));
	if (NULL == *ds) return ERROR;

	(*ds)->parent = (int*)malloc(sizeof(int) * size);
	if (NULL == (*ds)->parent) goto cleanup;

	(*ds)->names = (char**)calloc(size, sizeof(char*));
	if (NULL == (*ds)->names) goto cleanup;

	(*ds)->size = size;

	for (int i = 0; i < size; i++) {
		if (NULL == names[i]) goto cleanup;

		(*ds)->names[i] = (char*)malloc(strlen(names[i]) + 1);
		if (NULL == (*ds)->names[i]) goto cleanup;
		strcpy((*ds)->names[i], names[i]);

		(*ds)->parent[i] = -1; // 根节点，集合大小为1
	}
	return OK;

cleanup:
	if ((*ds)->names != NULL) {
		for (int i = 0; i < (*ds)->size; i++) free((*ds)->names[i]);
		free((*ds)->names);
	}
	free((*ds)->parent);
	free(*ds);
	*ds = NULL;
	return ERROR;
}

int FindSetIndex(DisjointSet ds, char* name)
{
	for (int i = 0; i < ds->size; ++i) {
		if (strcmp(name, ds->names[i]) == 0) return i;
	}
	return FAILURE;
}

// 路径压缩寻找根节点
int FindRoot(DisjointSet ds, char* name)
{
	if (NULL == name) return FAILURE;

	int idx = FindSetIndex(ds, name);
	if (idx == FAILURE) return FAILURE;

	int root = idx;
	while (ds->parent[root] >= 0) {
		root = ds->parent[root];
	}

	// 路径压缩
	int curr = idx;
	while (curr != root) {
		int next = ds->parent[curr];
		ds->parent[curr] = root;
		curr = next;
	}
	return root;
}

// 按大小合并
Status UnionSets(DisjointSet ds, char* name1, char* name2)
{
	if (NULL == name1 || NULL == name2) return ERROR;

	int root1 = FindRoot(ds, name1);
	int root2 = FindRoot(ds, name2);
	if (root1 == FAILURE || root2 == FAILURE) return ERROR;

	if (root1 != root2) {
		if (ds->parent[root1] <= ds->parent[root2]) { // root1 集合更大
			ds->parent[root1] += ds->parent[root2];
			ds->parent[root2] = root1;
		} else {
			ds->parent[root2] += ds->parent[root1];
			ds->parent[root1] = root2;
		}
	}
	return OK;
}

Status DestroyDisjointSet(DisjointSet* ds)
{
	if (NULL == ds || NULL == *ds) return ERROR;

	if (NULL != (*ds)->names) {
		for (int i = 0; i < (*ds)->size; ++i) free((*ds)->names[i]);
		free((*ds)->names);
	}
	free((*ds)->parent);

	free(*ds);
	*ds = NULL;
	return OK;
}


// ==================== 核心算法 ====================
Status PrimMST(Graph G, char* startVertex)
{
	if (NULL == startVertex) return ERROR;

	bool* visited = (bool*)calloc(G->vertexNum, sizeof(bool));
	if (!visited) return ERROR;

	MinHeap heap;
	if (InitMinHeap(&heap, G->vertexNum * G->vertexNum) != OK) {
		free(visited);
		return ERROR;
	}

	int targetIdx = FindVertexIndex(G, startVertex);
	if (FAILURE == targetIdx) {
		free(visited);
		DestroyMinHeap(&heap);
		return ERROR;
	}

	int mstEdgeCount = 0;
	visited[targetIdx] = true;

	// 将起点的所有邻边入堆
	for (int i = 0; i < G->vertexNum; i++) {
		if (G->edges[targetIdx][i] != INF && !visited[i]) {
			EdgeInfo edge = {
				.from = (char*)malloc(strlen(G->names[targetIdx]) + 1),
				.to = (char*)malloc(strlen(G->names[i]) + 1),
				.weight = G->edges[targetIdx][i]
			};
			if (!edge.from || !edge.to) {
				free(edge.from);
				free(edge.to);
				goto CLEANUP;
			}
			strcpy(edge.from, G->names[targetIdx]);
			strcpy(edge.to, G->names[i]);
			InsertHeap(heap, edge);
		}
	}

	while (heap->size > 0 && mstEdgeCount < G->vertexNum - 1) {
		EdgeInfo minEdge;
		if (ExtractMin(heap, &minEdge) != OK) break;

		targetIdx = FindVertexIndex(G, minEdge.to);

		if (visited[targetIdx]) { // 过期边过滤
			free(minEdge.from);
			free(minEdge.to);
			continue;
		}

		printf("%s %s %d\n", minEdge.from, minEdge.to, minEdge.weight);
		free(minEdge.from);
		free(minEdge.to);

		visited[targetIdx] = true;
		mstEdgeCount++;

		for (int i = 0; i < G->vertexNum; i++) {
			if (G->edges[targetIdx][i] != INF && !visited[i]) {
				EdgeInfo edge = {
					.from = (char*)malloc(strlen(G->names[targetIdx]) + 1),
					.to = (char*)malloc(strlen(G->names[i]) + 1),
					.weight = G->edges[targetIdx][i]
				};
				if (!edge.from || !edge.to) {
					free(edge.from);
					free(edge.to);
					goto CLEANUP;
				}
				strcpy(edge.from, G->names[targetIdx]);
				strcpy(edge.to, G->names[i]);
				InsertHeap(heap, edge);
			}
		}
	}

CLEANUP:
	DestroyMinHeap(&heap);
	free(visited);
	putchar('\n');

	return (mstEdgeCount == G->vertexNum - 1) ? OK : ERROR;
}

Status KruskalMST(Graph G)
{
	EdgeInfo* edgeList = NULL;
	DisjointSet ds = NULL;

	int edgeCount = CountUndirectedEdges(G);
	if (edgeCount <= 0) return ERROR;

	edgeList = (EdgeInfo*)calloc(edgeCount, sizeof(EdgeInfo));
	if (NULL == edgeList) goto CLEANUP;

	int validEdgeCount = 0;
	// 收集边并插入排序
	for (int i = 0; i < G->vertexNum; ++i) {
		for (int j = i + 1; j < G->vertexNum; ++j) {
			if (G->edges[i][j] != INF) {
				edgeList[validEdgeCount].weight = G->edges[i][j];
				edgeList[validEdgeCount].from = (char*)malloc(strlen(G->names[i]) + 1);
				edgeList[validEdgeCount].to = (char*)malloc(strlen(G->names[j]) + 1);

				if (!edgeList[validEdgeCount].from || !edgeList[validEdgeCount].to) {
					goto CLEANUP;
				}

				strcpy(edgeList[validEdgeCount].from, G->names[i]);
				strcpy(edgeList[validEdgeCount].to, G->names[j]);

				// 插入排序
				int k = validEdgeCount - 1;
				EdgeInfo tmp = edgeList[validEdgeCount];
				while (k >= 0 && edgeList[k].weight > tmp.weight) {
					edgeList[k + 1] = edgeList[k];
					k--;
				}
				edgeList[k + 1] = tmp;
				validEdgeCount++;
			}
		}
	}

	InitDisjointSet(&ds, G->names, G->vertexNum);

	int edgeIdx = 0;
	int mstEdgeCount = 0;

	while (edgeIdx < validEdgeCount && mstEdgeCount < G->vertexNum - 1) {
		int root1 = FindRoot(ds, edgeList[edgeIdx].from);
		int root2 = FindRoot(ds, edgeList[edgeIdx].to);

		if (root1 != root2) {
			printf("%s %s %d\n", edgeList[edgeIdx].from, edgeList[edgeIdx].to, edgeList[edgeIdx].weight);
			UnionSets(ds, edgeList[edgeIdx].from, edgeList[edgeIdx].to);
			mstEdgeCount++;
		}
		edgeIdx++;
	}

CLEANUP:
	if (NULL != edgeList) {
		for (int i = 0; i < validEdgeCount; i++) {
			free(edgeList[i].from);
			free(edgeList[i].to);
		}
		free(edgeList);
	}

	if (ds) DestroyDisjointSet(&ds);
	putchar('\n');

	return (mstEdgeCount == G->vertexNum - 1) ? OK : ERROR;
}

int main()
{
	Graph G;
	char* vertexNames[] = { "A", "B", "C", "D", "E", "F" };
	int vNum = sizeof(vertexNames) / sizeof(*vertexNames);
	InitGraph(&G, vertexNames, vNum, UNDIRECTED);

	AddWeightedEdge(G, "A", "B", 1);
	AddWeightedEdge(G, "A", "C", 1);
	AddWeightedEdge(G, "A", "D", 1);
	AddWeightedEdge(G, "B", "C", 2);
	AddWeightedEdge(G, "B", "E", 7);
	AddWeightedEdge(G, "B", "F", 4);
	AddWeightedEdge(G, "C", "D", 4);
	AddWeightedEdge(G, "C", "E", 3);
	AddWeightedEdge(G, "D", "E", 2);
	AddWeightedEdge(G, "E", "F", 6);

	PrintGraphMatrix(G);

	printf("--- Prim MST ---\n");
	PrimMST(G, "E");

	printf("--- Kruskal MST ---\n");
	KruskalMST(G);

	DestroyGraph(&G);
	return 0;
}

