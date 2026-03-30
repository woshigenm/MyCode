#include <stdio.h>

int main() {
	char str[128];
	gets(str);
	//f1a1n4x5i1a4o
	int sum = 0;
	int j = 1;
	for(int i = 0; str[i] != '\0'; i++)
	{
		if(str[i]>='0'&&str[i]<='9')
		{
			sum = sum + (str[i] - '0') * j;
			j *= 10;
		}
	}
	
	printf("数字为 %d\n", sum);
	
	return 0;
}

