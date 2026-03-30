#ifndef __LCD1602__H_
#define __LCD1602__H_
	void LCD_Init(void);
	void LCD_WriteCommand(unsigned char Command);
	void LCD_WriteData(unsigned char Data);
	void LCD_SetCursor(unsigned char Line,unsigned char Column);
	void LCD_ShowChar(unsigned char Line,unsigned char Column, unsigned char Char);
	void LCD_ShowNum(unsigned char Line,unsigned char Column, unsigned char Num, unsigned char Length);
	void LCD_ShowString(unsigned char Line,unsigned char Column, unsigned char * String);
#endif