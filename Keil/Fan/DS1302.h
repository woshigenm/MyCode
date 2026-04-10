#ifndef __DS1302__H_
#define __DS1302__H_

#define SECOND		5
#define MINUTE		4
#define HOUR		3
#define DATE		2
#define MONTH		1
#define YEAR		0

extern char Time[];
void DS1302_GetTime(void);
void DS1302_SetTime(void);
void DS1302_Init(void);
unsigned char DEC_TO_BCD(unsigned char DEC_DATA);
unsigned char BCD_TO_DEC(unsigned char BCD_DATA);
void DS1302_WriteByte(unsigned char Command, unsigned char Byte);
unsigned char DS1302_ReadByte(unsigned char Command);
#endif