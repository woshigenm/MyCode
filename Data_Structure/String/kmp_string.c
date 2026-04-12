#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*generatePtr)(const char*, int *);
int kmp(const char * const arr1, const char * const arr2, generatePtr dosomething);
int BF_DOUBLE(const char str1[], const char str2[]);
int BF_BACK(const char str1[], const char str2[]);
void generateNextval(const char* arr, int* nextval);
void generateNext(const char* arr, int* next);

int main()
{
	char arr1[] = "AAAAAAAAAAAAAAAAC";
	char arr2[] = "AAAAAAAAAAAAAAAAB";
	size_t len1 = strlen(arr1);

	printf("主串: %s\n", arr1);
	printf("模式: %s\n", arr2);
	printf("模式长度 -> %td\n", len1);
	printf("\nKmp_Next: \n");
	printf("kmp_Next 返回值: %d\n", kmp(arr1, arr2, generateNext));

	printf("\nKmp_NextVal: \n");
	printf("kmp_NextVal 返回值: %d\n\n", kmp(arr1, arr2, generateNextval));

	printf("BF(双循环) 返回值: %d\n\n", BF_DOUBLE(arr1, arr2));
	printf("BF(回溯) 返回值: %d\n", BF_BACK(arr1, arr2));
	return 0;
}

void generateNextval(const char* arr, int* nextval)
{
	if (NULL == arr || NULL == nextval)	return;
	nextval[0] = -1;

	int i = 0, j = -1, len = strlen(arr);
	while (i < len - 1) {
		if (j == -1 || arr[i] == arr[j]) {
			++i, ++j;
			if (arr[i] == arr[j])
				nextval[i] = nextval[j];
			else {
				nextval[i] = j;
			}
		} else {
			j = nextval[j];
		}
	}

	printf("nextval: ");
	for (int i = 0; i < len; i++) {
		printf("%2d ", nextval[i]);
	}

	putchar('\n');
}

void generateNext(const char* arr, int* next)
{
	if (NULL == arr || NULL == next)	return;
	next[0] = -1;

	int i = 0, j = -1, len = strlen(arr);
	while (i < len - 1) {
		if (j == -1 || arr[i] == arr[j]) {
			next[++i] = ++j;
		} else {
			j = next[j];
		}
	}

	printf("next: ");
	for (int i = 0; i < len; ++i)	{
		printf("%2d ", next[i]);
	}

	putchar('\n');
}

int kmp_count;
int kmp(const char * const arr1, const char * const arr2, generatePtr dosomething)
{
	if (NULL == arr1 || NULL == arr2)	return -1;
	int * next = (int *)malloc(sizeof(int) * strlen(arr2));
	if (NULL == next)	return -1;

	dosomething(arr2, next);

	int i = 0, j = 0;
	int arr1_len = strlen(arr1), arr2_len = strlen(arr2);
	while (i < arr1_len && j < arr2_len) {
		kmp_count++;
		if (j == -1 || arr1[i] == arr2[j]) {
			i++;
			j++;
		} else {
			j = next[j];
		}
	}

	free(next);
	printf("kmp_count -> %d\n", kmp_count);
	kmp_count = 0;
	return j >= arr2_len ? i - j : -1;
}

int BF_BACK_count;
int BF_BACK(const char str1[], const char str2[])
{
	int i = 0, j = 0;
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	while (i < len1 && j < len2) {
		BF_BACK_count++;
		if (str1[i] == str2[j]) {
			++j;
			i++;
		} else {
			i = i - j + 1;
			j = 0;
		}
	}

	printf("BF_BACK -> %d\n", BF_BACK_count);
	if (j >= len2)	return i - j;
	return -1;
}

int BF_DOUBLE_count;
int BF_DOUBLE(const char str1[], const char str2[])
{
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);

	int i, j;
	for (i = 0; i <= len1 - len2; i++) {
		for (j = 0; j < len2; j++) {
			BF_DOUBLE_count++;
			if (str2[j] != str1[i + j])
				break;
		}

		if (j == len2)	{
			printf("BF_DOUBLE -> %d\n", BF_DOUBLE_count);
			return i;
		}
	}

	printf("BF_DOUBLE -> %d\n", BF_DOUBLE_count);
	return -1;
}

