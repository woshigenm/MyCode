/*
【小球弹跳次数】一个小球从100米的高处落下，每次弹起的高度都是前一次的3/4,
求小球经过的路程小于590米时最多着地次数，输入输出形式如下。
*/

#include <stdio.h>

int main() {
	//路程
	float sum_all = 0.0;
	float fanxiachao = 100.0;
	sum_all = fanxiachao;

	int count = 0;
	while(sum_all < 590.0) {
		fanxiachao *= 0.75;
		sum_all += fanxiachao * 2;
		printf("%d -> 经过的路程 %.2f\n", count, sum_all);
		count++;
	}
	printf("小球落地次数最多是%d次", count);
	return 0;
}
