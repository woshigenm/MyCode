#ifndef _DS1302_H
#define _DS1302_H
extern unsigned char SetTime[];
unsigned char BcdToDec(unsigned char Bcd_Data);
unsigned char DecToBcd(unsigned char Dec_Data);
void DS1302_Init();
void DS1302_WriteByte(unsigned char Command, unsigned char Data);
unsigned char DS1302_ReadByte(unsigned char Command);
#endif