#ifndef _UART_H__
#define _UART_H__


#include "stm8l15x.h"

void USART1_Init(uint32_t bound);
//void USART_ACK(void);


void USART1_SendByte(uint8_t Data);
void USART1_SendNByte(uint8_t *pData, uint16_t Length);
void USART1_Printf(uint8_t *String);
int putchar(int c);
uint8_t Uart1Read(uint8_t *buf);
void UART2_Printf(uint8_t *String);
#endif