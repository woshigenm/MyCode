#include <stdio.h>
#include <string.h>

#define SIZE 128

int main()
{
	char array[SIZE];

	gets(array);

	char * end;

	end = array + strlen(array) - 1;

	int i;
	for (i = 0; array[i] != '\0'; i++, end--) {
		if (array[i] != *end) {
			break;
		}
	}

	if (array[i] == '\0') {
		printf("yes\n");
	} else {
		printf("no\n");
	}

//	for(start = array; start < end ; start++, end--)
//	{
//			if(*start != *end)
//			{
//				break;
//			}
//	}
//
//	if(start == end)
//	{
//		printf("yes\n");
//	}else{
//		printf("no\n");
//	}
	return 0;
}
