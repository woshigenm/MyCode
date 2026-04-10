#ifndef __ONE_WIRE__H_
#define __ONE_WIRE__H_
unsigned char ONEWIRE_Init(void);
void OneWire_SendBit(unsigned char Bit);
unsigned char OneWire_ReceiveBit(void);
void ONEWIRE_SendByte(unsigned char Byte);
unsigned char ONEWIRE_ReviceByte();
#endif