#ifndef __OLED_H__
#define __OLED_H__

#include "spi.h"
#include "delay.h"

#define OLED_WIDTH  128
#define OLED_HEIGHT 64
	
// typedef struct __OLED {
//   unsigned char x;
// } OLED;

void oled_reset(void);
void oled_send_data(unsigned char datas);
void oled_send_command(unsigned char command);
void oled_set_position(unsigned char x, unsigned char y);
void oled_init(void);
void oled_clear(void);
void oled_full(void);


#endif // __OLED_H__
