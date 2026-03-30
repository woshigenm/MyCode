#include <stdio.h>

int main()
{
	for(int red = 1; red <= 3; red++)
	{
		for(int white = 1; white <= 7; white++)
		{
			for(int black = 0; black <= 4; black++)
			{
				if(red + white + black == 8)
				{
					printf("red -> %d white -> %d black -> %d\n", red, white, black);
				}
			}
		}
	}
	return 0;
}

