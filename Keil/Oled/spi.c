#include "spi.h"

void spi_read_write(unsigned char datas)
{
  unsigned char i;
  for(i=0; i<8; i++)
  {
    SPI_MOSI = (datas << i) & 0x80;
    SPI_SCK = 0;
    SPI_SCK = 1;
  }
}
