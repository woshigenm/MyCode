#ifndef __DELAY_H__
#define __DELAY_H__

#include <REGX52.H>
	
#define CRYSTAL_FREQUENCY   11.0592
#define FS                  (1 / (CRYSTAL_FREQUENCY / 12))

void delay_ms(unsigned int t);

#endif
