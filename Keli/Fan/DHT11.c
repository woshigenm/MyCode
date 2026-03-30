#include <REGX52.H>
#include "Delay.h"

sbit DHT11_DQ = P1^3;

void DHT11_Start(void)
{
	unsigned char timeout;
	DHT11_DQ = 1;
	DHT11_DQ = 0;
	Delay(20);
	DHT11_DQ = 1;
	timeout = 0;
	while(DHT11_DQ && ++timeout <= 40);
}

bit DHT11_Check_Response(void)
{
	unsigned char timeout;
	if(!DHT11_DQ)
	{
		timeout = 0;
		while(!DHT11_DQ && ++timeout <= 80);
		if(timeout > 80)	return 0;
		
		if(DHT11_DQ)
		{
			timeout = 0;
			while(DHT11_DQ && ++timeout <= 80);
			if(timeout > 80)	return 0;
			
			return 1;
		}
	}
	
	return 0;
}

bit DHT11_ReadBit(void)
{
	unsigned char timeout, i;
	bit ACK = 0;
	
	timeout = 0;
	while(!DHT11_DQ && ++timeout <= 50);
	
	if(DHT11_DQ)
	{
		i = 11;while (--i);//30us
		if(DHT11_DQ)
		{
			ACK = 1;
			i = 15;while (--i);//40us
		}
	}
	
	return ACK;
}

unsigned char DHT11_ReadByte(void)
{
	unsigned char i, Byte = 0x00;
	for(i = 0; i < 8; ++i)
	{
		Byte <<= 1;
		Byte |= DHT11_ReadBit();
	}
	
	return Byte;
}

bit DHT11_ReadData(unsigned char * Temp, unsigned char * Humi)
{
	unsigned char Data[5], sum = 0x00;
	DHT11_Start();
	if(DHT11_Check_Response())
	{
		Data[0] = DHT11_ReadByte();
		Data[1] = DHT11_ReadByte();
		Data[2] = DHT11_ReadByte();
		Data[3] = DHT11_ReadByte();
		Data[4] = DHT11_ReadByte();
		
		sum = Data[0] + Data[1] + Data[2] + Data[3];
		if(sum == Data[4])
		{
			*Temp = Data[2];
			*Humi = Data[0];
			
			return 1;
		}
	}
	
	return 0;
}
