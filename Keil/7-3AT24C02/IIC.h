#ifndef __IIC_H__
#define __IIC_H__
void IIC_Start(void);
void IIC_Over(void);
void IIC_SendByte(unsigned char Byte);
void IIC_SendAck(bit AckBit);
unsigned char IIC_ReceiveByte(void);
unsigned char IIC_ReceiveAck(void);
#endif