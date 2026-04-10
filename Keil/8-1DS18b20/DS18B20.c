#include <REGX52.H>
#include "ONEWIRE.H"

void DS18B20_ConvertT(void)
{
	ONEWIRE_Init();
	ONEWIRE_SendByte(0xCC);
	ONEWIRE_SendByte(0x44);
}

float DS18B20_ReadT(void)
{
	unsigned char LSB, MSB;
	float T;

	ONEWIRE_Init();
	ONEWIRE_SendByte(0xCC);
	ONEWIRE_SendByte(0xBE);

	LSB = ONEWIRE_ReviceByte();
	MSB = ONEWIRE_ReviceByte();
	T = (MSB << 8 | LSB) / 16.0;
	return T;
}