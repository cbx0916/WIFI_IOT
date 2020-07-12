#ifndef _BSP_H
#define _BSP_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "stm8l15x.h"


/* 宏定义 --------------------------------------------------------------------*/
#define LED_GPIO_PORT             GPIOE
#define LED_GPIO_PIN              GPIO_Pin_5
#define PWR485_GPIO_PORT          GPIOE
#define PWR485_GPIO_PIN           GPIO_Pin_7
#define EN485_GPIO_PORT           GPIOD
#define EN485_GPIO_PIN            GPIO_Pin_7

/* LED */
#define LED_ON                    GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN)
#define LED_OFF                   GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN)
#define LED_REVERSE               GPIO_ToggleBits(LED_GPIO_PORT, LED_GPIO_PIN)


/* 函数申明 ------------------------------------------------------------------*/
void CLK_Configuration(void);
void GPIO_Configuration(void);
void BSP_Initializes(void);

void TIM4_Init(void);
void delay_ms(uint16_t n);

#endif /* _BSP_H */