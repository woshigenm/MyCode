#ifndef __IIC__H_
#define __IIC__H_
void IIC_START(void);
void IIC_STOP(void);
void IIC_SendByte(unsigned char Byte);
unsigned char IIC_ReviceByte(void);
void IIC_SendACK(bit ACK);
bit IIC_ReviceACK(void);
#endif