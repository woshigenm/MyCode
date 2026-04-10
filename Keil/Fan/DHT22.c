#include <REGX52.H>
#include "Delay.h"

sbit DHT22_DQ = P1 ^ 2;

void DHT22_Start(void)
{
	unsigned char timeout;
	DHT22_DQ = 1;
	DHT22_DQ = 0;
	Delay(1);
	DHT22_DQ = 1;
	timeout = 0;
	while (DHT22_DQ && ++timeout <= 25);
}

bit DHT22_Check_Response(void)
{
	unsigned char timeout;
	if (DHT22_DQ == 0) {
		timeout = 0;
		while (!DHT22_DQ && ++timeout <= 80);
		if (timeout > 80)	return 0;

		if (DHT22_DQ == 1) {
			timeout = 0;
			while (DHT22_DQ && ++timeout <= 80);
			if (timeout > 80)	return 0;

			return 1;
		}
	}

	return 0;
}

bit DHT22_ReadBit(void)
{
	unsigned char timeout, i;
	bit ACK = 0;

	timeout = 0;
	while (!DHT22_DQ && ++timeout <= 50);

	if (DHT22_DQ) {
		i = 11;
		while (--i);//30us
		if (DHT22_DQ) {
			ACK = 1;
			i = 15;
			while (--i);//40us
		}
	}

	return ACK;
}

unsigned char DHT22_ReadByte(void)
{
	unsigned char Byte = 0x00, i;

	for (i = 0; i < 8; ++i) {
		Byte <<= 1;
		Byte |=  DHT22_ReadBit();
	}

	return Byte;
}

bit DHT22_ReadData(float * Temp, float * Humi)
{
	unsigned char Data[5], sum = 0x00;

	DHT22_Start();
	if (DHT22_Check_Response()) {
		Data[0] = DHT22_ReadByte();
		Data[1] = DHT22_ReadByte();
		Data[2] = DHT22_ReadByte();
		Data[3] = DHT22_ReadByte();
		Data[4] = DHT22_ReadByte();

		sum = Data[0] + Data[1] + Data[2] + Data[3];
		if (sum == Data[4]) {
			*Temp = (((unsigned int)Data[2] << 8) | Data[3]) / 10.0F;
			*Humi = (((unsigned int)Data[0] << 8) | Data[1]) / 10.0F;
		}

		return 1;
	}

	return 0;
}