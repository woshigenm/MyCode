#include <REGX52.H>

sbit TTP229_SCL = P1 ^ 0;
sbit TTP229_SDO = P1 ^ 1;

unsigned char TTP229_ReadByte(void)
{
	unsigned char Data = 0x00, i;

	for (i = 1; i <= 8; i++) {
		TTP229_SCL = 0;
		if (!TTP229_SDO) {
			Data = i;
		}
		TTP229_SCL = 1;
	}

	return Data;
}