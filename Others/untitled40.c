//【倒序输出字符串】输入任意一个字符串str(字符串可能有空格)，倒序存放在str中，按如下格式输入输出。
#include <stdio.h>
#include <string.h>

#define SIZE 128

int main() {
	char arr[SIZE];

	gets(arr);

//	int len = strlen(arr);
//	for(int i = 0; i < len / 2; i++)
//	{
//		char temp = arr[i];
//		arr[i] = arr[len - i - 1];
//		arr[len - i - 1] = temp;
//	}

//	puts(arr);

	puts(strrev(arr));

	return 0;
}
