#include <stdio.h>

int main() {
	char str[128];
	gets(str);
	
	int count = 0;
	int sum = 0;
	for(int i = 0; str[i] != '\0' && count < 5; i++)
	{
		if(str[i]>='0'&&str[i]<='9')
		{
			sum = sum * 10 + (str[i] - '0');
			count++;
		}
	}
	printf("数字为 %d\n", sum);
	
	return 0;
}

