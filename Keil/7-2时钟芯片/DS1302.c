#include <REGX52.H>
#include "DS1302.H"

#define DS1302_SECONDS_WADDR 	0x80
#define DS1302_MINUTES_WADDR 	0x82
#define DS1302_HOUR_WADDR 	 	0x84
#define DS1302_DATE_WADDR 	 	0x86
#define DS1302_MONTH_WADDR 		0x88
#define DS1302_DAY_WADDR 		0x8A
#define DS1302_YEAR_WADDR 		0x8C
#define DS1302_WP_WADDR 		0x8E

sbit DS1302_CE = P3 ^ 5;
sbit DS1302_IO = P3 ^ 4;
sbit DS1302_SCLK = P3 ^ 6;

unsigned char Command[] = {DS1302_YEAR_WADDR, DS1302_MONTH_WADDR, DS1302_DATE_WADDR, DS1302_HOUR_WADDR, DS1302_MINUTES_WADDR, DS1302_SECONDS_WADDR};
void DS1302_Init()
{
	unsigned char sec;

	DS1302_WriteByte(DS1302_WP_WADDR, 0x00);

	for (sec = 0; sec < sizeof(Command); ++sec) {
		DS1302_WriteByte(Command[sec], DecToBcd(Time[sec]));
	}

	DS1302_WriteByte(DS1302_WP_WADDR, 0x80);
}

unsigned char DecToBcd(unsigned char Dec_Data)
{
	return ((Dec_Data / 10) << 4) | (Dec_Data % 10);
}

unsigned char BcdToDec(unsigned char Bcd_Data)
{
	return (Bcd_Data >> 4) * 10 + (Bcd_Data & 0x0F);
}

void DS1302_WriteByte(unsigned char Command, unsigned char Data)
{
	unsigned char i;

	DS1302_CE = 0;
	DS1302_SCLK = 0;
	DS1302_CE = 1;

	for (i = 0; i < 8; ++i) {
		DS1302_IO = Command & (1 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}

	for (i = 0; i < 8; ++i) {
		DS1302_IO = Data & (1 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}

	DS1302_CE = 0;
}

unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i, Read_Data = 0;

	DS1302_CE = 0;
	DS1302_SCLK = 0;
	DS1302_CE = 1;

	for (i = 0; i < 8; ++i) {
		DS1302_IO = Command & (1 << i);
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
	}

	DS1302_IO = 1;

	for (i = 0; i < 8; ++i) {
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		if (DS1302_IO) Read_Data |= 1 << i;
	}

	DS1302_CE = 0;
	DS1302_IO = 0;

	return Read_Data;
}

void SetTime()
{
	DS1302_WriteByte(0x8E, 0x00);

	DS1302_WriteByte(DS1302_SECONDS_WADDR, DecToBcd(Time[SECONDS])); // 秒 (清除CH位)
	DS1302_WriteByte(DS1302_MINUTES_WADDR, DecToBcd(Time[MINUTES]));       // 分
	DS1302_WriteByte(DS1302_HOUR_WADDR, DecToBcd(Time[HOUR]));           // 时
	DS1302_WriteByte(DS1302_DATE_WADDR, DecToBcd(Time[DATE]));          // 日
	DS1302_WriteByte(DS1302_MONTH_WADDR, DecToBcd(Time[MONTH]));          // 月
	DS1302_WriteByte(DS1302_YEAR_WADDR, DecToBcd(Time[YEAR]));           // 年

	DS1302_WriteByte(0x8E, 0x80);
}

void ReadTime()
{
	Time[SECONDS] = BcdToDec(DS1302_ReadByte(0x81));
	Time[MINUTES] = BcdToDec(DS1302_ReadByte(0x83));
	Time[HOUR] = BcdToDec(DS1302_ReadByte(0x85));
	Time[DATE] = BcdToDec(DS1302_ReadByte(0x87));
	Time[MONTH] = BcdToDec(DS1302_ReadByte(0x89));
	Time[YEAR] = BcdToDec(DS1302_ReadByte(0x8D));
}