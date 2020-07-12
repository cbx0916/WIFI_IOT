#include "bsp.h"

void CLK_Configuration(void)
{
  CLK_HSICmd(ENABLE);
  CLK_SYSCLKSourceSwitchCmd(ENABLE);
  CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);//高速内部时钟 16M
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
}

void GPIO_Configuration(void)
{
  //LED,PWR485,EN485 推挽输出低电平 高速
  GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PIN, GPIO_Mode_Out_PP_Low_Fast);
  //GPIO_Init(PWR485_GPIO_PORT, (GPIO_Pin_TypeDef)PWR485_GPIO_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(EN485_GPIO_PORT, (GPIO_Pin_TypeDef)EN485_GPIO_PIN, GPIO_Mode_Out_PP_Low_Fast);
  
//#if 0 
//  /* 系统时钟输出 */
//  GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_FAST);
//  CLK_CCOCmd(ENABLE);
//#endif
}

void BSP_Initializes(void)
{
  CLK_Configuration();
  GPIO_Configuration();
}

void TIM4_Init()
{
  TIM4_DeInit();//HSI 16M
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE); //使能
  TIM4_TimeBaseInit(TIM4_Prescaler_2 , 79);//1M
  TIM4_ClearFlag(TIM4_FLAG_Update);
  //TIM4_SetCounter(0);
  //TIM4_ITConfig(TIM4_IT_Update, ENABLE);
  //TIM4_ARRPreloadConfig(ENABLE);

}
void delay_10us(uint16_t n)
{
  TIM4_Cmd(ENABLE); //启动定时器
  //TIM4_SetCounter(0);
  
  while(n--)
  {

    while(RESET == TIM4_GetFlagStatus(TIM4_FLAG_Update));

    TIM4_ClearFlag(TIM4_FLAG_Update);

  }
  TIM4_Cmd(ENABLE); //关闭定时器

}
void delay_ms(uint16_t n)
{
  while(n--)
  {
    delay_10us(100);
  }
}

