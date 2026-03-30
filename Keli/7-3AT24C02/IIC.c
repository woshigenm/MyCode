#include <REGX52.H>
#include "IIC.H"

sbit IIC_SCL = P2^1;
sbit IIC_SDA = P2^0;

void IIC_Start(void)
{
	IIC_SDA = 1;
	IIC_SCL = 1;
	IIC_SDA = 0;
	IIC_SCL = 0;
}

void IIC_Over(void)
{
	IIC_SDA = 0;
	IIC_SCL = 1;
	IIC_SDA = 1;
}

void IIC_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0; i < 8; ++i)
	{
		IIC_SDA = (0x80 >> i) & Byte;
		IIC_SCL = 1;
		IIC_SCL = 0;
	}
}

unsigned char IIC_ReceiveByte(void)
{
	unsigned char i, Byte = 0;
	IIC_SDA = 1;
	for(i = 0; i < 8; ++i)
	{
		IIC_SCL = 1;
		if(IIC_SDA)
		{
			Byte |= (0x80 >> i);
		}
		IIC_SCL = 0;
	}
	
	return Byte;
}

//AckBit -> 0 发送应答 1 接受应答
void IIC_SendAck(bit AckBit)
{
	IIC_SDA = AckBit;
	IIC_SCL = 1;
	IIC_SCL = 0;
}

unsigned char IIC_ReceiveAck(void)
{
	unsigned char AckBit = 0;
	IIC_SDA = 1;
	IIC_SCL = 1;
	
	if(IIC_SDA)	AckBit = 1;
	IIC_SCL = 0;
	
	return AckBit;
}