#include <stdio.h>
#include <string.h>

int main()
{
	char arr[128];
	scanf("%s", arr);
	
	int size = strlen(arr);
	
	for(int i = 0; i < size / 2; i++)
	{
		char temp = arr[i];
		arr[i] = arr[size - i - 1];
		arr[size - i - 1] = temp;
	}
	
	printf("%s\n", arr);
	
	return 0;
}
