#include <stdio.h>

int main()
{
	//【鸡兔同笼】一个圈里有鸡和兔子，共有头35个，腿94个，问：鸡兔各多少？分别输出每一种可能
	int ji, tu;
	//按鸡的脚分
	for (ji = 1; ji <= 35; ji++) {
		tu = 35 - ji;
		if (ji * 2 + tu * 4 == 94) {
			printf("鸡有%d只,兔有%d只\n", ji, tu);
		}
	}
	return 0;
}
