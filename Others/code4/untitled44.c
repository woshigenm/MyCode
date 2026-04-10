//【数组中的最值】 某学校举行演讲比赛，输入10个评委给甲同学的打分（分数0-100）,
//去掉最高分和最低分，最后求出该同学的演讲平均分(保留两位小数),按下列样例输入输出。

#include <stdio.h>

#define SIZE 10

int main()
{
	float array[SIZE];
	int i;

	for (i = 0; i < SIZE; i++)
		scanf("%f", &array[i]);

	float max, min, sum;
	max = min = array[0];
	sum = array[0];

	for (i = 1; i < SIZE; i++) {
		if (array[i] > max)
			max = array[i];
		if (array[i] < min)
			min = array[i];
		sum += array[i];
	}

	printf("去掉最高分%.2f分\n去掉最低分%.2f分\n该同学平均分是%.2f\n", max, min, (sum - max - min) / (SIZE - 2));
	return 0;
}
