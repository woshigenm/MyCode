#include <stdio.h>

int main()
{
	int i, j, k;
	
	for(i = 1; i <= 9; i++)
	{
		for(j = 9; j > i; j--)
			putchar(' ');
		
		for(k = 1; k <= 2 * i - 1; k++)
			putchar('*');
		putchar('\n');
	}
	return 0;
}
