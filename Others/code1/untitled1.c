#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 50

#define DEFAULT_MOVE 3

//字符串倒置函数
void rev_str(char * str, int str_size);

//字符串位移函数
void move_str(char * str, int str_size, int move_size, bool flag);

//字符串加密函数
void jiami_str(char * str, int str_size);

//字符串解密函数
void jiemi_str(char * str, int str_size);

//字母大小写转换函数
void case_str(char * str, int str_size);

int main()
{
	char arr[SIZE];

	gets(arr);

	//加密字符串
	//jiami_str(arr, strlen(arr));
	//puts(arr);

	//解密字符串
	jiemi_str(arr, strlen(arr));
	puts(arr);

	return 0;
}

/*
str: 要移动字符的字符串
str_size: 字符串的长度
move_size: 移动位数
flag: flag为true时向左移, flag为flase向右移动
*/
void move_str(char * str, int str_size, int move_size, bool flag)
{
	int i;
	for (i = 0; i < str_size; i++) {
		if (flag) {
			if (str[i] >= 'A' && str[i] <= 'Z') {
				str[i] = 'Z' + (str[i] - 'Z' - move_size) % 26;
			} else if (str[i] >= 'a' && str[i] <= 'z') {
				str[i] = 'z' + (str[i] - 'z' - move_size) % 26;
			}
		} else {
			if (str[i] >= 'A' && str[i] <= 'Z') {
				str[i] = 'A' + (str[i] - 'A' + move_size) % 26;
			} else if (str[i] >= 'a' && str[i] <= 'z') {
				str[i] = 'a' + (str[i] - 'a' + move_size) % 26;
			}
		}
	}
}

/*
str: 要倒置的字符串
str_size: 字符串的长度
*/
void rev_str(char * str, int str_size)
{
	int i, tmp;
	for (i = 0; i < str_size / 2; i++) {
		tmp = str[i];
		str[i] = str[str_size - i - 1];
		str[str_size - i - 1] = tmp;
	}
}

/*
str: 要大小写转换的字符串
str_size: 字符串的长度
*/
void case_str(char * str, int str_size)
{
	int i;

	for (i = 0; i < str_size; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = str[i] + 32;
		} else if (str[i] >= 'a' && str[i] <= 'z') {
			str[i] = str[i] - 32;
		}
	}
}

/*
str: 要加密的字符串
str_size: 字符串的长度
*/
void jiami_str(char * str, int str_size)
{
	move_str(str, str_size, DEFAULT_MOVE, true);

	rev_str(str, str_size);

	case_str(str, str_size);
}

/*
str: 要解密的字符串
str_size: 字符串的长度
*/
void jiemi_str(char * str, int str_size)
{
	move_str(str, str_size, DEFAULT_MOVE, false);

	rev_str(str, str_size);

	case_str(str, str_size);
}
