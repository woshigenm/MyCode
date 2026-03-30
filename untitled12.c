#include <stdio.h>

int main()
{
	for(int i = 1; i <= 9; i++)
	{
		for(int j = 9; j > i; j--)
			putchar(' ');
		
		for(int k = 1; k <= 2 * i - 1; k++)
			putchar('0' + i);
		
		putchar('\n');
	}
	return 0;
}
