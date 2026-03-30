#include <REGX52.H>
#include "AT24C02.H"
#include "IIC.H"

#define AT24C02_ADDRESS	0xA0
void AT24C02_WriteByte(unsigned char WordAddress, unsigned char Data)
{
	IIC_Start();
	
	IIC_SendByte(AT24C02_ADDRESS);
	IIC_ReceiveAck();
	
	IIC_SendByte(WordAddress);
	IIC_ReceiveAck();
	
	IIC_SendByte(Data);
	IIC_ReceiveAck();
	
	IIC_Over();
}

unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char ReadByte;
	
	IIC_Start();
	
	IIC_SendByte(AT24C02_ADDRESS);
	IIC_ReceiveAck();
	
	IIC_SendByte(WordAddress);
	IIC_ReceiveAck();
	
	IIC_Start();
	IIC_SendByte(AT24C02_ADDRESS | 0x01);
	IIC_ReceiveAck();
	
	ReadByte = IIC_ReceiveByte();
	IIC_SendAck(1);
	
	IIC_Over();
	
	return ReadByte;
}