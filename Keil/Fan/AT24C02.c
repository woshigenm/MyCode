#include <REGX52.H>
#include "IIC.h"

void AT24C02_WriteByte(unsigned char Address, unsigned char Data)
{
	IIC_START();
	
	IIC_SendByte(0xA0);
	IIC_ReviceACK();
	
	IIC_SendByte(Address);
	IIC_ReviceACK();
	
	IIC_SendByte(Data);
	IIC_ReviceACK();
	
	IIC_STOP();
}

unsigned char AT24C02_ReadByte(unsigned char Address)
{
	unsigned char Data = 0x00;
	
	IIC_START();
	
	IIC_SendByte(0xA0);
	IIC_ReviceACK();
	
	IIC_SendByte(Address);
	IIC_ReviceACK();
	
	IIC_START();
	
	IIC_SendByte(0xA1);
	IIC_ReviceACK();
	
	Data=IIC_ReviceByte();
	IIC_SendACK(1);
	
	IIC_STOP();
	
	return Data;
}