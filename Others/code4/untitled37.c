//【成绩等级输出】按下列要求用switch-case语句编写程序：输入任意0-100范围内的一个分数，输出等级。[0-70）“不合格”；
//[70-80）”合格”；[80-90)”良好”；[90-100]”优秀”，如果输入的数据不在【0,100】，输出“输入错误”，输入输出格式如下。

#include <stdio.h>

int main()
{
	float score;
	scanf("%f", &score);

	switch ((int)score / 10)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			printf("不合格\n");
			break;
		case 7:
			printf("合格\n");
			break;
		case 8:
			printf("良好\n");
			break;
		case 9:

		case 10:
			printf("优秀\n");
			break;
		default:
			printf("输入错误\n");

	}
	return 0;
}
