#include <stdio.h>

// 查找数组中唯一出现一次的元素（其他元素均出现两次）
int findUnique(int arr[], int size)
{
	int result = 0;
	for (int i = 0; i < size; i++) {
		result ^= arr[i];  // 异或运算：相同元素抵消，最终结果为唯一元素
	}
	return result;
}

int main()
{
	int arr1[] = {2, 3, 2, 4, 4};
	int size1 = sizeof(arr1) / sizeof(arr1[0]);
	printf("唯一元素: %d\n", findUnique(arr1, size1));  // 输出: 3

	int arr2[] = {10, 20, 30, 20, 10};
	int size2 = sizeof(arr2) / sizeof(arr2[0]);
	printf("唯一元素: %d\n", findUnique(arr2, size2));  // 输出: 30

	return 0;
}

