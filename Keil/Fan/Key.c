#include <REGX52.H>
#include "Delay.h"

unsigned char Keys;

unsigned char Key(void)
{
	unsigned char KeyNumber = 0;
	if(!P3_1){Delay(10);while(!P3_1);Delay(10);KeyNumber = 1;}
	if(!P3_0){Delay(10);while(!P3_0);Delay(10);KeyNumber = 2;}
	if(!P3_2){Delay(10);while(!P3_2);Delay(10);KeyNumber = 3;}
	if(!P3_3){Delay(10);while(!P3_3);Delay(10);KeyNumber = 4;}
	
	return KeyNumber;
}

unsigned char GetKey(void)
{
	unsigned char tmp;
	tmp = Keys;
	Keys = 0;
	return tmp;
}

unsigned char Key_State(void)
{
	unsigned char KeyNumber = 0;
	if(!P3_1){KeyNumber = 1;}
	if(!P3_0){KeyNumber = 2;}
	if(!P3_2){KeyNumber = 3;}
	if(!P3_3){KeyNumber = 4;}
	
	return KeyNumber;
}

void Key_Loop(void)
{
	static unsigned char Last, Now;
	Last = Now;
	Now = Key_State();
	
	if(Last == 1 && !Now)	Keys = 1;
	if(Last == 2 && !Now)	Keys = 2;
	if(Last == 3 && !Now)	Keys = 3;
	if(Last == 4 && !Now)	Keys = 4;
}