#include <REGX52.H>
#include "Delay.h"
#include "MatrixKey.h"

unsigned char MatrixKey(void)
{
	static const unsigned char Key[4][4] = {
		1,2,3,4,
		5,6,7,8,
		9,10,11,12,
		13,14,15,16
	};
	
	unsigned char i, j;
	for(i = 0; i < 4; ++i)
	{
		P1 = 0xFF;
		P1 &= ~(0x01 << i);
		for(j = 0; j < 4; ++j)
		{
			if(!(P1 & (0x01 << (j + 4))))
			{
				Delay(5);
				while(!(P1 & (0x01 << (j + 4))));
				return Key[i][j];
			}
		}
	}
	
	return 0;
}