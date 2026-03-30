#ifndef _DS1302_H
#define _DS1302_H

// 时间项索引定义
#define SECONDS 5
#define MINUTES 4
#define HOUR    3
#define DATE    2
#define MONTH   1
#define YEAR    0

	extern char Time[];
	void ReadTime();
	void SetTime();
	unsigned char BcdToDec(unsigned char Bcd_Data);
	unsigned char DecToBcd(unsigned char Dec_Data);
	void DS1302_Init();
	void DS1302_WriteByte(unsigned char Command, unsigned char Data);
	unsigned char DS1302_ReadByte(unsigned char Command);
#endif