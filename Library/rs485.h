#ifndef _rs485_H
#define _rs485_H

#include "stm8l15x.h"
#include "bsp.h"

//ģʽ����
#define RS485_TX_EN_1	GPIO_SetBits(EN485_GPIO_PORT, EN485_GPIO_PIN)	//485ģʽ����.0:���գ�1:����.
#define RS485_TX_EN_0	GPIO_ResetBits(EN485_GPIO_PORT, EN485_GPIO_PIN)
														 
void RS485_Init(uint32_t bound);

uint8_t Uart2Read(uint8_t *buf);
void rs485_UartWrite(uint8_t *buf ,uint8_t len);

uint8_t* UartDriver(void);
int BCD2int(uint8_t m);
void TIM2_Init(void);

#endif
