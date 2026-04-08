
#line 1 "main.c" /0
  
#line 1 "D:\Keil_v5\C51\Inc\Atmel\REGX51.H" /0






 
 
 
 
 


 
 sfr P0      = 0x80;
 sfr SP      = 0x81;
 sfr DPL     = 0x82;
 sfr DPH     = 0x83;
 sfr PCON    = 0x87;
 sfr TCON    = 0x88;
 sfr TMOD    = 0x89;
 sfr TL0     = 0x8A;
 sfr TL1     = 0x8B;
 sfr TH0     = 0x8C;
 sfr TH1     = 0x8D;
 sfr P1      = 0x90;
 sfr SCON    = 0x98;
 sfr SBUF    = 0x99;
 sfr P2      = 0xA0;
 sfr IE      = 0xA8;
 sfr P3      = 0xB0;
 sfr IP      = 0xB8;
 sfr PSW     = 0xD0;
 sfr ACC     = 0xE0;
 sfr B       = 0xF0;
 


 
 sbit P0_0 = 0x80;
 sbit P0_1 = 0x81;
 sbit P0_2 = 0x82;
 sbit P0_3 = 0x83;
 sbit P0_4 = 0x84;
 sbit P0_5 = 0x85;
 sbit P0_6 = 0x86;
 sbit P0_7 = 0x87;
 


 
 
 
 
 
 
 
 
 
 
 


 
 sbit IT0  = 0x88;
 sbit IE0  = 0x89;
 sbit IT1  = 0x8A;
 sbit IE1  = 0x8B;
 sbit TR0  = 0x8C;
 sbit TF0  = 0x8D;
 sbit TR1  = 0x8E;
 sbit TF1  = 0x8F;
 


 
 
 
 
 
 
 
 
 
 
 
 
 


 
 sbit P1_0 = 0x90;
 sbit P1_1 = 0x91;
 sbit P1_2 = 0x92;
 sbit P1_3 = 0x93;
 sbit P1_4 = 0x94;
 sbit P1_5 = 0x95;
 sbit P1_6 = 0x96;
 sbit P1_7 = 0x97;
 


 
 sbit RI   = 0x98;
 sbit TI   = 0x99;
 sbit RB8  = 0x9A;
 sbit TB8  = 0x9B;
 sbit REN  = 0x9C;
 sbit SM2  = 0x9D;
 sbit SM1  = 0x9E;
 sbit SM0  = 0x9F;
 


 
 sbit P2_0 = 0xA0;
 sbit P2_1 = 0xA1;
 sbit P2_2 = 0xA2;
 sbit P2_3 = 0xA3;
 sbit P2_4 = 0xA4;
 sbit P2_5 = 0xA5;
 sbit P2_6 = 0xA6;
 sbit P2_7 = 0xA7;
 


 
 sbit EX0  = 0xA8;        
 sbit ET0  = 0xA9;        
 sbit EX1  = 0xAA;        
 sbit ET1  = 0xAB;        
 sbit ES   = 0xAC;        
 sbit ET2  = 0xAD;        
 
 sbit EA   = 0xAF;        
 


 
 sbit P3_0 = 0xB0;
 sbit P3_1 = 0xB1;
 sbit P3_2 = 0xB2;
 sbit P3_3 = 0xB3;
 sbit P3_4 = 0xB4;
 sbit P3_5 = 0xB5;
 sbit P3_6 = 0xB6;
 sbit P3_7 = 0xB7;
 
 sbit RXD  = 0xB0;        
 sbit TXD  = 0xB1;        
 sbit INT0 = 0xB2;        
 sbit INT1 = 0xB3;        
 sbit T0   = 0xB4;        
 sbit T1   = 0xB5;        
 sbit WR   = 0xB6;        
 sbit RD   = 0xB7;        
 


 
 sbit PX0  = 0xB8;
 sbit PT0  = 0xB9;
 sbit PX1  = 0xBA;
 sbit PT1  = 0xBB;
 sbit PS   = 0xBC;
 sbit PT2  = 0xBD;
 


 
 sbit P    = 0xD0;
 sbit F1   = 0xD1;
 sbit OV   = 0xD2;
 sbit RS0  = 0xD3;
 sbit RS1  = 0xD4;
 sbit F0   = 0xD5;
 sbit AC   = 0xD6;
 sbit CY   = 0xD7;
 



 
 
 
 
 
 
 
 
 
 
#line 1 "main.c" /0
 
  
#line 1 "D:\Keil_v5\C51\Inc\INTRINS.H" /0






 
 
 
 
 
 #pragma SAVE
 
 
#line 15 "D:\Keil_v5\C51\Inc\INTRINS.H" /1
 
 
 
#line 18 "D:\Keil_v5\C51\Inc\INTRINS.H" /0
 
 extern void          _nop_     (void);
 extern bit           _testbit_ (bit);
 extern unsigned char _cror_    (unsigned char, unsigned char);
 extern unsigned int  _iror_    (unsigned int,  unsigned char);
 extern unsigned long _lror_    (unsigned long, unsigned char);
 extern unsigned char _crol_    (unsigned char, unsigned char);
 extern unsigned int  _irol_    (unsigned int,  unsigned char);
 extern unsigned long _lrol_    (unsigned long, unsigned char);
 extern unsigned char _chkfloat_(float);
 
#line 29 "D:\Keil_v5\C51\Inc\INTRINS.H" /1
 
 
 
#line 32 "D:\Keil_v5\C51\Inc\INTRINS.H" /0
 
 extern void          _push_    (unsigned char _sfr);
 extern void          _pop_     (unsigned char _sfr);
 
 
 #pragma RESTORE
 
 
 
#line 2 "main.c" /0
 
  
#line 1 "D:\Keil_v5\C51\Inc\STRING.H" /0







 
 
 
 
 
 
 
 typedef unsigned int size_t;
 
 
 
 
 
 
 #pragma SAVE
 #pragma REGPARMS
 extern char  *strcat  (char *s1, const char *s2);
 extern char  *strncat (char *s1, const char *s2, size_t n);
 
 extern char   strcmp  (const char *s1, const char *s2);
 extern char   strncmp (const char *s1, const char *s2, size_t n);
 
 extern char  *strcpy  (char *s1, const char *s2);
 extern char  *strncpy (char *s1, const char *s2, size_t n);
 
 extern size_t strlen  (const char *);
 
 extern char  *strchr  (const char *s, char c);
 extern int    strpos  (const char *s, char c);
 extern char  *strrchr (const char *s, char c);
 extern int    strrpos (const char *s, char c);
 
 extern size_t strspn  (const char *s, const char *set);
 extern size_t strcspn (const char *s, const char *set);
 extern char  *strpbrk (const char *s, const char *set);
 extern char  *strrpbrk(const char *s, const char *set);
 extern char  *strstr  (const char *s, const char *sub);
 extern char  *strtok  (char *str, const char *set);
 
 extern char   memcmp  (const void *s1, const void *s2, size_t n);
 extern void  *memcpy  (void *s1, const void *s2, size_t n);
 extern void  *memchr  (const void *s, char val, size_t n);
 extern void  *memccpy (void *s1, const void *s2, char val, size_t n);
 extern void  *memmove (void *s1, const void *s2, size_t n);
 extern void  *memset  (void *s, char val, size_t n);
 #pragma RESTORE
 
 
#line 3 "main.c" /0
 
  
#line 1 "LCD1602.H" /0
 
 
 
 
 void LCD_Init();
 void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char);
 void LCD_ShowString(unsigned char Line,unsigned char Column,char *String);
 void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
 void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);
 void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
 void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
 void LCD_ClearManual(unsigned char line);
 
 
#line 4 "main.c" /0
 
  
#line 1 "timer0.h" /0
 
 
 
 void Timer0_Init();
 
 
#line 5 "main.c" /0
 
  
#line 1 "Buzzer.h" /0
 
 
 
 void Buzzer(unsigned int xms);
 
 
#line 6 "main.c" /0
 
  
#line 1 "Delay.h" /0
 
 
 void Delay(unsigned int xms);
 
#line 7 "main.c" /0
 
  
#line 1 "MatrixKey.h" /0
 
 
 
 enum KeyValues {
 KEY_1 = 1,
 KEY_2,
 KEY_3,
 KEY_4,
 KEY_5,
 KEY_6,
 KEY_7,
 KEY_8,
 KEY_9,
 KEY_10,
 KEY_11,
 KEY_12,
 KEY_13,
 KEY_14,
 KEY_15,
 KEY_16
 };
 
 unsigned char MatrixKey();
 
#line 8 "main.c" /0
 
  
#line 1 "Nixie.h" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 void Nixie(unsigned char Postion, unsigned char Num);
 
 
#line 9 "main.c" /0
 
 
 
 
 
 
 
 unsigned char MatrixKey();
 void Delay(unsigned int xms);
 void Init_PassWord();
 void DisplayPasswordScreen();
 void Show_Time();
 void Buzzer(unsigned int xms);
 
 
 unsigned char GetKey = 0;
 unsigned char hour = 0, minute = 0, second = 0;
 char * PassWord = "1145141919810";
 char InputPassWord[13 + 1];
 bit timer_mode = 0;          
 bit timer_running = 0;        
 
 void main() {
 unsigned char Current_Row = 1;
 unsigned char Current_Char = 0;
 
 
 LCD_Init();
 Timer0_Init();
 DisplayPasswordScreen();
 
 while(1) {
 GetKey = MatrixKey();
 
 
 if(GetKey == KEY_13) {
 timer_mode = !timer_mode;
 
 LCD_ClearManual(2);
 if(timer_mode) {
 
 LCD_ShowString(1, 1, "TIMER:");
 timer_running = 1;
 } else {
 
 DisplayPasswordScreen();
 timer_running = 0;  
 Current_Row = 1;
 Current_Char = 0;
 }
 }
 
 
 if(timer_mode) {
 
 switch(GetKey) {
 case KEY_11:
 
 timer_running = !timer_running;
 LCD_ShowString(2, 13, timer_running ? "RUN " : "PAUS");
 break;
 
 case KEY_12:
 
 hour = minute = second = 0;
 Show_Time();
 break;
 }
 } else {
 
 switch(GetKey) {
 case KEY_1:
 case KEY_2:
 case KEY_3:
 case KEY_4:
 case KEY_5:
 case KEY_6:
 case KEY_7:
 case KEY_8:
 case KEY_9:
 case KEY_10:
 if(Current_Char < 13) {
 LCD_ShowNum(2, Current_Row++, (GetKey == 10) ? 0 : GetKey, 1);
 InputPassWord[Current_Char++] = ((GetKey == 10) ? 0 : GetKey) + '0';
 
 Buzzer(100);
 
 if(Current_Char == 13) {
 InputPassWord[Current_Char] = '\0';
 }
 }
 break;
 
 case KEY_11:
 if(Current_Row > 1 && Current_Char > 0) {
 --Current_Row;
 --Current_Char;
 }
 LCD_ShowChar(2, Current_Row, '*');
 InputPassWord[Current_Char] = '\0';
 break;
 
 case KEY_12:
 LCD_ClearManual(1);
 if(!strcmp(InputPassWord, PassWord)) {
 LCD_ShowString(2, 1, "CORRECT");
 } else {
 LCD_ShowString(2, 1, "ERROR");
 }
 
 Buzzer(100);
 Delay(500);
 Buzzer(100);
 
 LCD_ClearManual(1);
 Init_PassWord();
 Current_Row = 1;
 Current_Char = 0;
 break;
 }
 }
 
 
 if(GetKey >= KEY_1 && GetKey <= KEY_16) {
 LCD_ShowNum(1, 15, GetKey, 2);
 }
 }
 }
 


 
 void DisplayPasswordScreen() {
 LCD_ShowString(1, 1, "PASSWORD:");
 Init_PassWord();
 }
 


 
 void Init_PassWord() {
 unsigned char i;
 for(i = 1; i <= 13; ++i) {
 LCD_ShowChar(2, i, '*');
 }
 memset(InputPassWord, 0, sizeof(InputPassWord));
 }
 


 
 void Show_Time()
 {
 LCD_ShowNum(2, 1, hour, 2);
 LCD_ShowChar(2, 3, ':');
 LCD_ShowNum(2, 4, minute, 2);
 LCD_ShowChar(2, 6, ':');
 LCD_ShowNum(2, 7, second, 2);
 }
 
 
 void Time_Loop()
 {
 
 if(timer_running) {
 if(++second >= 60) {
 second = 0;
 ++minute;
 }
 
 if(minute >= 60) {
 minute = 0;
 ++hour;
 }
 
 if(hour >= 24) {
 hour = 0;
 }
 
 
 Show_Time();
 }
 }


 
 void Timer0_Rountine() interrupt 1 {
 static unsigned int second_count = 0;
 
 
 TH0 = 0xFC;
 TL0 = 0x17;
 
 if(++second_count >= 1000) {
 second_count = 0;
 
 Time_Loop();
 }
 }
