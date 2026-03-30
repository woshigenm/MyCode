#ifndef __ONEWIRE__H_
#define __ONEWIRE__H_
	bit OneWire_Init(void);
	void OneWire_SendBit(bit Data);
	bit OneWire_ReceiveBit(void);
	unsigned char OneWire_ReceiveByte(void);
	void OneWire_SendByte(unsigned char Byte);
#endif