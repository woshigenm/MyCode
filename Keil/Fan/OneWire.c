#include <REGX52.H>
#include "Delay.h"

sbit OneWire_DQ = P3 ^ 7;

bit OneWire_Init(void)
{
	unsigned char data i;
	bit ACK;


	OneWire_DQ = 0;
	i = 227;
	while (--i);
	OneWire_DQ = 1;
	i = 20;
	while (--i);
	ACK = OneWire_DQ;
	i = 227;
	while (--i);
	return ACK;
}

void OneWire_SendBit(bit Data)
{
	unsigned char data i;

	OneWire_DQ = 0;
	if (Data) {
		i = 3;
		while (--i);
	} else {
		i = 25;
		while (--i);
	}

	OneWire_DQ = 1;
	i = 25;
	while (--i);
}

bit OneWire_ReceiveBit(void)
{
	bit Data;
	unsigned char data i;
	OneWire_DQ = 0;
	i = 2;
	while (--i);
	OneWire_DQ = 1;
	i = 2;
	while (--i);
	Data = OneWire_DQ;
	i = 20;
	while (--i);
	return Data;
}

unsigned char OneWire_ReceiveByte(void)
{
	unsigned char Byte = 0x00, i;

	for (i = 0; i < 8; ++i) {
		if (OneWire_ReceiveBit())	Byte |= (0x01 << i);
	}

	return Byte;
}

void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;

	for (i = 0; i < 8; ++i) {
		OneWire_SendBit(Byte & (0x01 << i));
	}

}