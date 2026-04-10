#ifndef __AT24C02__H_
#define __AT24C02__H_
void AT24C02_WriteByte(unsigned char Address, unsigned char Data);
unsigned char AT24C02_ReadByte(unsigned char Address);
#endif