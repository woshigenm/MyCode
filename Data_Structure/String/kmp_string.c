#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int kmp(const char * const arr1, const char * const arr2);
int look_substr1(const char str1[], const char str2[]);
int look_substr2(const char str1[], const char str2[]);

int main() {
	char arr1[] = "ABCAAAAAAAAAAAAAAAAAABCDABABCDABCDABDE";
	char arr2[] = "ABCDABDADABCDABDAD";
	printf("%d\n", kmp(arr1, arr2));
	printf("%d\n", look_substr1(arr1, arr2));
	printf("%d\n", look_substr2(arr1, arr2));
	return 0;
}

int count1, count2, count3;
int kmp(const char * const arr1, const char * const arr2) {
	int x, y, m, cn;

	int * next = (int *)malloc(sizeof(int) * strlen(arr2));
	next[0] = -1;
	next[1] = 0;

	cn = 0;
	m = 2;
	while (m < strlen(arr2)) {
		if (arr2[m - 1] == arr2[cn]) {
			next[m++] = ++cn;
		} else if (cn > 0) {
			cn = next[cn];
		} else {
			next[m++] = 0;
		}
	}

	for (int i = 0; i < strlen(arr2); ++i)	printf("%d ", next[i]);
	putchar('\n');

	x = y = 0;
	while (x < strlen(arr1) && y < strlen(arr2)) {
		count1++;
		if (arr1[x] == arr2[y]) {
			x++;
			y++;
		} else if (y == 0) {
			x++;
		} else {
			y = next[y];
		}
	}

	free(next);
	printf("count1 -> %d\n", count1);
	return y == strlen(arr2) ? x - y : -1;
}

int look_substr2(const char str1[], const char str2[]) {
	int i = 0, j = 0;
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	while (i < len1 && j < len2) {
		count3++;
		if (str1[i] == str2[j]) {
			++j;
			i++;
		} else {
			i = i - j + 1;
			j = 0;
		}
	}

	printf("count3 -> %d\n", count3);
	if (j >= len2)	return i - j;
	NULL;
	return -1;
}

int look_substr1(const char str1[], const char str2[]) {
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);

	int i, j;
	for (i = 0; i <= len1 - len2; i++) {
		for (j = 0; j < len2; j++) {
			count2++;
			if (str2[j] != str1[i + j])
				break;
		}

		if (j == len2)	{
			printf("count2 -> %d\n", count2);
			return i;
		}
	}
	printf("count2 -> %d\n", count2);
	return -1;
}

