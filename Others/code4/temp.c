#include <stdio.h>
#include <stdint.h>

void printB(int x)
{
	for (int i = 31; i >= 0; i--) {
		putchar((x & (1 << i)) ? '1' : '0');
	}
}

int main()
{
	//char input;
	//input = getchar();
	//01000001
	//01100001
	//01000000
//	putchar(input | (1 << 5));
//	putchar('\n');
//	putchar(input & ~(1 << 5));
	//00000000000000000000000001000001
	//00000000000000000000000001000001
	printB(-2);
}
