#include "UART.h"
#include "bsp.h"
#define MAXLEN 80

uint8_t USART1_RX_BUF[MAXLEN];
extern uint8_t USART1_RX_BUF[MAXLEN];
uint8_t USART1_RX_CNT=0;
extern uint8_t USART1_RX_CNT;

//��ʼ��USART1
void USART1_Init(uint32_t bound)
{

//  //1����ʱ��ʹ�ܣ�GPIO ʱ��ʹ��  
//  CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
//
//  //2���ڸ�λ
//  USART_DeInit(USART1);
//  //3GPIO �˿�ģʽ����
//  GPIO_Init(GPIOA, GPIO_Pin_2, GPIO_Mode_Out_OD_Low_Fast);
//  GPIO_Init(GPIOA, GPIO_Pin_3, GPIO_Mode_In_PU_No_IT);
//  //4���ڲ�����ʼ��
//  USART_Init(USART1,(uint32_t)bound,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,(USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));
//  //5�����жϲ��ҳ�ʼ�� NVIC����������жϲ���Ҫ������裩
//  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
//  //6ʹ�ܴ���
//  //7��д�жϴ�����
//  ITC_SetSoftwarePriority(USART1_RX_IRQn,ITC_PriorityLevel_0);
//  enableInterrupts();
//  USART_Cmd(USART1, ENABLE);
  

    
    //GPIO_Init (GPIOA,GPIO_Pin_2,GPIO_Mode_Out_PP_High_Fast);
    //GPIO_Init (GPIOA,GPIO_Pin_3,GPIO_Mode_In_PU_No_IT);// GPIO_Mode_Out_OD_HiZ_Fast
    //GPIO_ExternalPullUpConfig(GPIOA, GPIO_Pin_2 | GPIO_Pin_3, ENABLE);
    
    GPIO_Init (GPIOA,GPIO_Pin_2,GPIO_Mode_Out_OD_HiZ_Fast);
    GPIO_Init (GPIOA,GPIO_Pin_3,GPIO_Mode_Out_OD_HiZ_Fast);// GPIO_Mode_Out_OD_HiZ_Fast
  
    //��ӳ��
    SYSCFG_REMAPDeInit();                                                            
    SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortA,ENABLE);

    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
    
    USART_DeInit(USART1);  
    // ��ʼ������
    USART_Init(USART1,
                (uint32_t)115200,
                USART_WordLength_8b,
                USART_StopBits_1,
                USART_Parity_No,
                USART_Mode_Rx | USART_Mode_Tx);  // �������д

    // ���ж�
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);   

    /* Enable USART ʹ�� */
    USART_Cmd(USART1, ENABLE);
    enableInterrupts();
}
//UART1����һ���ֽ�
void USART1_SendByte(uint8_t Data)
{
  USART_ClearITPendingBit(USART1, USART_FLAG_TC);
  while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
  USART_SendData8(USART1,Data);
  while((USART_GetFlagStatus(USART1,USART_FLAG_TC))==RESET);
  USART_ClearITPendingBit(USART1, USART_FLAG_TC);
}
//UART1����N���ֽ�
void UART1_SendNByte(uint8_t *pData, uint16_t Length)
{
  while(Length--)
  {
    USART1_SendByte(*pData);
    pData++;
  }
}

//UART1��ӡ�ַ���
void UART1_Printf(uint8_t *String)
{
  while((*String) != '\0')
  {
    //UART1_SendByte(*String);   
    USART1_SendByte(*String);
    String++;
  }
}

/*ϵͳprintf����ʵ��*/
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

    for(i=0;i<USART1_RX_CNT;i++)    //�������յ������ݵ�����ָ����
    {
      *buf=USART1_RX_BUF[i];//�����ݸ��Ƶ�buf��
      buf++;
    }
    i=USART1_RX_CNT;
    USART1_RX_CNT=0;      //���ռ���������
    
    return i;           //����ʵ�ʶ�ȡ����
  
}
