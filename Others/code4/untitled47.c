//【字符加密】编程实现，输入任意一个字母（不分大小写），
//将字母循环后移5个位置后输出，如’a’变成’f’，’w’变成’b’，’W’变成‘B’，输入输出格式如下。
#include <stdio.h>

#define SIZE 26

#define FANXIAOCHAO 5

int main()
{
	char input;
	input = getchar();
	
	if((input >= 'A' && input <= 'Z' - FANXIAOCHAO) || (input >= 'a' && input <= 'z' - FANXIAOCHAO))
	{
		input += FANXIAOCHAO;
	}else if((input >= 'Z' - FANXIAOCHAO && input <= 'Z') || (input >= 'z' - FANXIAOCHAO && input <= 'z'))
	{
		input -= SIZE - FANXIAOCHAO;
	}
	
	putchar(input);
	
	return 0;
}
