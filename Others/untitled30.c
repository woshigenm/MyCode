/*
【百钱买百鸡】鸡翁一值钱五，鸡母一值钱三，鸡雏三值钱一，百钱买百鸡，
编写程序求翁、母、雏各几何，分别输出每一种可能，以及共有多少种买法，输入输出形式如下。
*/
#include <stdio.h>

#define SIZE 100

int main() {
	int gongji, muji, xiaoji;

	int counter = 0;
	for (gongji = 0; gongji <= SIZE / 5; gongji++) {
		for (muji = 0; muji <= SIZE / 3; muji++) {
			xiaoji = SIZE - gongji - muji;

			if (15 * gongji + 9 * muji + xiaoji == 3 * SIZE) {
				printf("公鸡有%d只,母鸡有%d只,小鸡有%d只\n", gongji, muji, xiaoji);
				counter++;
			}
		}
	}

	printf("共有%d种买法\n", counter);
	return 0;
}
