#include <REGX52.H>
#include "Delay.h"

#define ROW 4

unsigned char Key(void)
{
	unsigned char i;
	for(i = 0; i < ROW; ++i)
	{
		if(!(P3 & (1 << i)))
		{
			Delay(5);
			if(!(P3 & (1 << i)))
			{
				while(!(P3 & (1 << i)));
				return i + 1;
			}
		}
	}
	
	return 0;
}