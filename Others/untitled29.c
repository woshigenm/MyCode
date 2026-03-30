/*
【字符串中同形整数】输入任意一个字符串，以回车结束，把其中数字字符转换为同形整数m输出（如果数字超过5位，只取前5位数字转换）。
例如：输入as12d56AB 转换为后m是1256，输入输出形式如下。
*/

#include <stdio.h>

#define SIZE 128

int main()
{
	char arr[SIZE];
	gets(arr);
	
	int sum = 0;
	
	for(int i = 0; arr[i] != '\0'; i++)
	{
		if(arr[i] >= '0' && arr[i] <= '9')
		{
			sum = sum * 10 + (arr[i] - '0');
		}
		
		if(sum / 10000 != 0)
		{
			break;
		}
	}
	
	printf("m = %d\n", sum);
	
	return 0;
}
