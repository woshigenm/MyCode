#include <REGX52.H>
#include "ONEWIRE.H"

sbit OneWire_DQ = P3^7;

unsigned char ONEWIRE_Init(void)
{
	unsigned char data i, AckBit;
	
	OneWire_DQ = 1;
	OneWire_DQ = 0;
	i = 227;while (--i);//500us
	
	OneWire_DQ = 1;
	i = 25;while (--i);// 60us
	
	AckBit=OneWire_DQ;
	i = 247;while (--i);		//Delay 500us
	return AckBit;
}

unsigned char OneWire_ReceiveBit(void)
{
	unsigned char i;
	unsigned char Bit;
	OneWire_DQ=0;
	i = 2;while (--i);			//Delay 5us
	OneWire_DQ=1;
	i = 2;while (--i);			//Delay 5us
	Bit=OneWire_DQ;
	i = 24;while (--i);			//Delay 50us
	return Bit;
}

void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	OneWire_DQ=0;
	i = 4;while (--i);			//Delay 10us
	OneWire_DQ=Bit;
	i = 24;while (--i);			//Delay 50us
	OneWire_DQ=1;
}

void ONEWIRE_SendByte(unsigned char Byte)

{
	unsigned char i;
	for(i = 0; i < 8; ++i)
	{
		OneWire_SendBit(Byte & (0x01 << i));
	}
}

unsigned char ONEWIRE_ReviceByte()
{
	unsigned char i, Byte = 0x00;
	for(i = 0; i < 8; ++i)
	{
		if(OneWire_ReceiveBit())
		{
			Byte |= (0x01 << i);
		}
	}
	
	return Byte;
}