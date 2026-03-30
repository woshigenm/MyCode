#include <stdio.h>

/*
3高考真题第一问
输出样例
1 1 2 3 5
8 13 21 34 55
89 144 233 377 610
987 1597 2584 4181 6765
*/
void test_1() {
	int array[20] = {1, 1};
	int i;
	printf("%d %d ", array[0], array[1]);

	int count = 2;
	for (i = 2; i < 20; i++) {
		array[i] = array[i - 1] + array[i - 2];
		printf("%d ", array[i]);
		count++;
		if (count % 5 == 0) {
			putchar('\n');
		}
	}
}

/*
2高考真题第二问
输入输出样例
10
1 2 3 3 2 1 4 5 6 7
1 号候选人有 2 张选票
2 号候选人有 2 张选票
3 号候选人有 2 张选票
无效选票有 4 张
*/
void test_2() {
	int n,i,fan;
	
	int array[4] = {};
	printf("请输入总票数: ");
	scanf("%d", &n);
	
	printf("请投票(1,2,3)每张票之间空格分隔: ");
	for(i = 1; i<=n;i++)
	{
		scanf("%d", &fan);
		
		if(fan > 3 || fan < 0)
		{
			array[0]++;
		}else
		{
			array[fan]++;
		}
	}
	
	for(i = 1; i < 4; i++)
	{
		printf("%d 号候选人有 %d 张选票\n", i, array[i]);
	}
	
	printf("无效选票有 %d 张\n", array[0]);
}

int main() {
	test_2();
	return 0;
}
