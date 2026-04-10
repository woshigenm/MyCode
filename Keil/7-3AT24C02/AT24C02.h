#ifndef __AT24C02_H__
#define __AT24C02_H__
unsigned char AT24C02_ReadByte(unsigned char WordAddress);
void AT24C02_WriteByte(unsigned char WordAddress, unsigned char Data);
#endif