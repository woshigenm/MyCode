#include <REGX52.H>

#define DS1302_SECOND		0x80
#define DS1302_MINUTE		0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_DAY			0x8A
#define DS1302_YEAR			0x8C
#define DS1302_WP			0x8E

sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

char Time[] = {25, 8, 28, 15, 0, 0};

unsigned char Time_Index[] = {
	DS1302_YEAR,DS1302_MONTH,DS1302_DATE,
	DS1302_HOUR,DS1302_MINUTE,DS1302_SECOND
};

unsigned char BCD_TO_DEC(unsigned char BCD_DATA)
{
	return ((BCD_DATA / 16) * 10) + (BCD_DATA % 16);
}

unsigned char DEC_TO_BCD(unsigned char DEC_DATA)
{
	return ((DEC_DATA / 10) * 16) + (DEC_DATA % 10);
}

void DS1302_WriteByte(unsigned char Command, unsigned char Byte)
{
	unsigned char i;
	
	DS1302_CE = 1;
	for(i = 0; i < 8; ++i)
	{
		DS1302_IO = Command & (0x01 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	
	for(i = 0; i < 8; ++i)
	{
		DS1302_IO = Byte & (0x01 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	
	DS1302_CE = 0;
}

unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i, Data = 0x00;
	Command |= 0x01;
	
	DS1302_CE = 1;
	for(i = 0; i < 8; ++i)
	{
		DS1302_IO = Command & (0x01 << i);
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
	}
	
	for(i = 0; i < 8; ++i)
	{
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		if(DS1302_IO)	Data |= (0x01 << i);
	}
	
	DS1302_CE = 0;
	DS1302_IO = 0;
	return Data;
}

void DS1302_Init(void)
{
	unsigned char i;
	
	DS1302_CE = 0;
	DS1302_SCLK = 0;
	
	DS1302_WriteByte(DS1302_WP, 0x00);
	
	for(i = 0; i < 8; ++i)
	{
		DS1302_WriteByte(Time_Index[i], DEC_TO_BCD(Time[i]));
	}
	
	DS1302_WriteByte(DS1302_WP, 0x80);
}

void DS1302_SetTime(void)
{
	unsigned char i;
	DS1302_WriteByte(DS1302_WP, 0x00);
	
	for(i = 0; i < sizeof(Time_Index); ++i)
	{
		DS1302_WriteByte(Time_Index[i], DEC_TO_BCD(Time[i]));
	}
	
	DS1302_WriteByte(DS1302_WP, 0x80);
}

void DS1302_GetTime(void)
{
	unsigned char i;
	for(i = 0; i < sizeof(Time_Index); ++i)
	{
		Time[i] = BCD_TO_DEC(DS1302_ReadByte(Time_Index[i]));
	}
}
