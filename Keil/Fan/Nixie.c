#include <REGX52.H>
#include "Nixie.h"
#include "Delay.h"

#define NIXIE_SEG P0
#define NIXIE_DIG P2

unsigned char Nixie_Buf[] = {10, 10, 11, 10, 10, 11, 10, 10};

const unsigned char Nixie_Number[] = {
	0x3F,
	0x06,
	0x5B,
	0x4F,
	0x66,
	0x6D,
	0x7D,
	0x07,
	0x7F,
	0x6F,
	0x00,
	0x40
};

void Nixie_SetBuf(unsigned char Location, Number)
{
	Nixie_Buf[Location] = Number;
}


void Nixie(unsigned char Position, unsigned char Number)
{
	NIXIE_SEG = 0x00;
	NIXIE_DIG = (Position << 2);
	NIXIE_SEG = Nixie_Number[Number];
}

void Nixie_Loop(void)
{
	static unsigned char i;
	Nixie(i, Nixie_Buf[i]);
	i++;
	i %= 8;
}