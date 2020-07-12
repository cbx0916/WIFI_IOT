#include "UART.h"
#include "bsp.h"
#define MAXLEN 80

uint8_t USART1_RX_BUF[MAXLEN];
extern uint8_t USART1_RX_BUF[MAXLEN];
uint8_t USART1_RX_CNT=0;
extern uint8_t USART1_RX_CNT;

//初始化USART1
void USART1_Init(uint32_t bound)
{

//  //1串口时钟使能，GPIO 时钟使能  
//  CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
//
//  //2串口复位
//  USART_DeInit(USART1);
//  //3GPIO 端口模式设置
//  GPIO_Init(GPIOA, GPIO_Pin_2, GPIO_Mode_Out_OD_Low_Fast);
//  GPIO_Init(GPIOA, GPIO_Pin_3, GPIO_Mode_In_PU_No_IT);
//  //4串口参数初始化
//  USART_Init(USART1,(uint32_t)bound,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,(USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));
//  //5开启中断并且初始化 NVIC（如果开启中断才需要这个步骤）
//  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
//  //6使能串口
//  //7编写中断处理函数
//  ITC_SetSoftwarePriority(USART1_RX_IRQn,ITC_PriorityLevel_0);
//  enableInterrupts();
//  USART_Cmd(USART1, ENABLE);
  

    
    //GPIO_Init (GPIOA,GPIO_Pin_2,GPIO_Mode_Out_PP_High_Fast);
    //GPIO_Init (GPIOA,GPIO_Pin_3,GPIO_Mode_In_PU_No_IT);// GPIO_Mode_Out_OD_HiZ_Fast
    //GPIO_ExternalPullUpConfig(GPIOA, GPIO_Pin_2 | GPIO_Pin_3, ENABLE);
    
    GPIO_Init (GPIOA,GPIO_Pin_2,GPIO_Mode_Out_OD_HiZ_Fast);
    GPIO_Init (GPIOA,GPIO_Pin_3,GPIO_Mode_Out_OD_HiZ_Fast);// GPIO_Mode_Out_OD_HiZ_Fast
  
    //重映射
    SYSCFG_REMAPDeInit();                                                            
    SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortA,ENABLE);

    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
    
    USART_DeInit(USART1);  
    // 初始化参数
    USART_Init(USART1,
                (uint32_t)115200,
                USART_WordLength_8b,
                USART_StopBits_1,
                USART_Parity_No,
                USART_Mode_Rx | USART_Mode_Tx);  // 允许读和写

    // 开中断
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);   

    /* Enable USART 使能 */
    USART_Cmd(USART1, ENABLE);
    enableInterrupts();
}
//UART1发送一个字节
void USART1_SendByte(uint8_t Data)
{
  USART_ClearITPendingBit(USART1, USART_FLAG_TC);
  while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
  USART_SendData8(USART1,Data);
  while((USART_GetFlagStatus(USART1,USART_FLAG_TC))==RESET);
  USART_ClearITPendingBit(USART1, USART_FLAG_TC);
}
//UART1发送N个字节
void UART1_SendNByte(uint8_t *pData, uint16_t Length)
{
  while(Length--)
  {
    USART1_SendByte(*pData);
    pData++;
  }
}

//UART1打印字符串
void UART1_Printf(uint8_t *String)
{
  while((*String) != '\0')
  {
    //UART1_SendByte(*String);   
    USART1_SendByte(*String);
    String++;
  }
}

/*系统printf函数实现*/
int putchar(int c)
{
  if('\n' == (char)c)
  {
    USART_SendData8(USART1, '\r');
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
  }
  USART_SendData8(USART1, c);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
  
    
  return (c);
}



    
uint8_t Uart1Read(uint8_t *buf)
{
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    uint8_t i;

    for(i=0;i<USART1_RX_CNT;i++)    //拷贝接收到的数据到接收指针中
    {
      *buf=USART1_RX_BUF[i];//将数据复制到buf中
      buf++;
    }
    i=USART1_RX_CNT;
    USART1_RX_CNT=0;      //接收计数器清零
    
    return i;           //返回实际读取长度
  
}
