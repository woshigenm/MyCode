#ifndef __LCD__H_
#define __LCD__H_
	void LCD_Init(void);
	void LCD_ShowChar(unsigned char Line, unsigned char Column, unsigned char Char);
	void LCD_ClearScreen(void);
	void LCD_ShowString(unsigned char Line, unsigned char Column, unsigned char * Char);
	void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Num, unsigned char Length);
	void LCD_ShowSignedNum(unsigned char Line, unsigned char Column, int Num, unsigned char Length);
	void LCD_ShowBinNum(unsigned char Line, unsigned char Column, int Num, unsigned char Length);
	void LCD_ShowHexNum(unsigned char Line, unsigned char Column, int Num, unsigned char Length);
#endif