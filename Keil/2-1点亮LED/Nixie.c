#include <REGX52.H>
#include "Delay.h"

//0-9
const unsigned char Number[] =
{
	0x3F, 0x06, 0x5B, 0x4F, 0x66,
	0x6F, 0x7D, 0x07, 0x7F, 0x67
};

//Postion = 0 ~ 7
void Nixie(unsigned char Postion, unsigned char Num)
{
	if(Postion > 7)
		return;
	
	P2 = (Postion << 2);
	
	P0 = Number[Num];
	Delay(1);
	P0 = 0x00;
}