#include <REGX52.H>
#include "Delay.h"

unsigned char Key(void)
{
	unsigned char i;
	for(i = 0; i < 4; ++i)
	{
		if(!(P3 & (1 << i)))
		{
			Delay(10);
			if(!(P3 & (1 << i)))
			{
				while(!(P3 & (1 << i)));
				
				return i + 1;
			}
		}
	}
	
	return 0;
}