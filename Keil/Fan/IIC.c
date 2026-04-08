#include <REGX52.H>

sbit SDA = P2^0;
sbit SCL = P2^1;

void IIC_START(void)
{
	SDA = 1;
	SCL = 1;
	SDA = 0;
	SCL = 0;
}

void IIC_STOP(void)
{
	SDA = 0;
	SCL = 1;
	SDA = 1;
}

void IIC_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0; i < 8; ++i)
	{
		SDA = Byte & (0x80 >> i);
		SCL = 1;
		SCL = 0;
	}
}

void IIC_SendACK(bit ACK)
{
	SDA = ACK;
	SCL = 1;
	SCL = 0;
}

bit IIC_ReviceACK()
{
	bit ACK;
	SDA = 1;
	SCL = 1;
	ACK = SDA;
	SCL = 0;
	return ACK;
}

unsigned char IIC_ReviceByte(void)
{
	unsigned char i, Data = 0x00;
	SDA = 1;
	
	for(i = 0; i< 8;i++)
	{
		SCL = 0;
		SCL = 1;
		Data = (SDA) | (Data << 1);
		//if(SDA) Data |= (0x80 >> i);
	}
	
	return Data;
}