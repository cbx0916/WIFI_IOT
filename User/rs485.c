#include "rs485.h"
#include "stm8l15x_usart.h"
#define MAXLEN 80	//�����ֽ������

uint8_t USART2_RX_BUF[MAXLEN];
extern uint8_t USART2_RX_BUF[MAXLEN];  //���ջ��壬���MAXLEN�ֽ�
uint8_t USART2_RX_CNT=0;
extern uint8_t USART2_RX_CNT;         //�����ֽڼ�����
uint8_t flagFrame=0;            //֡������ɱ�־�����յ�һ֡������


uint8_t read_idx=0 ;
uint8_t read_len=0;
extern uint8_t read_idx;
extern uint8_t read_len;
      
//��ʼ��UART2
void RS485_Init(uint32_t bound)
{

    CLK_PeripheralClockConfig(CLK_Peripheral_USART2, ENABLE);
    //GPIO_Init (GPIOE,GPIO_Pin_4,GPIO_Mode_Out_PP_High_Fast);
    //GPIO_Init (GPIOE,GPIO_Pin_3,GPIO_Mode_In_PU_No_IT);
    GPIO_ExternalPullUpConfig(GPIOE, GPIO_Pin_4 | GPIO_Pin_3, ENABLE);
   // USART init
    USART_DeInit(USART2);  

    // ��ʼ������
    USART_Init(USART2,
                (uint32_t)2400,
                USART_WordLength_9b,
                USART_StopBits_1,
                USART_Parity_Even,
                USART_Mode_Rx | USART_Mode_Tx);  // �������д

    // ���ж�
    // һ����Ҫдʱ�ٿ�д�жϣ�����д�жϻ�ǳ�Ƶ��������ʼ����ִ���ж�
    // ���жϿ�����ҵ��
    USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);   

    /* Enable USART ʹ�� */
    USART_Cmd(USART2, ENABLE);
    enableInterrupts();
  
}
//������յ������ݳ��ȣ����ŵ�buf��
uint8_t Uart2Read(uint8_t *buf)
{
  
//  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//  uint8_t i;
//  if(len<USART2_RX_CNT) //ָ����ȡ���ȴ���ʵ�ʽ��ܵ����ݳ���ʱ
//  {
//    len = USART2_RX_CNT;//��ȡ��������Ϊʵ�ʽ��յ��ĳ���
//  }
//  for(i=0;i<len;i++)    //�������յ������ݵ�����ָ����
//  {
//    *buf=USART2_RX_BUF[i];//�����ݸ��Ƶ�buf��
//    buf++;
//  }
//  USART2_RX_CNT=0;      //���ռ���������
//  
//  return len;           //����ʵ�ʶ�ȡ����
    for(int i=0;i<sizeof(buf);i++)
    {
      buf[i]=0x00;
    }
  
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    uint8_t i;

    for(i=0;i<USART2_RX_CNT;i++)    //�������յ������ݵ�����ָ����
    {
      *buf=USART2_RX_BUF[i];//�����ݸ��Ƶ�buf��
      buf++;
    }
    i=USART2_RX_CNT;
    USART2_RX_CNT=0;      //���ռ���������
    
    return i;           //����ʵ�ʶ�ȡ����
  
//      // prepare send data
//    USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
//
//    // ��ʼ��������
//    read_idx = 0;
//    read_len = 6;
//
//    // ��ʼ���������жϣ�
//    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//    return read_len;
  
}

//����
void rs485_UartWrite(uint8_t *buf,uint8_t len)
{

//    uint8_t i = 0;
//    RS485_TX_EN_1;        //����ģʽ
//    delay_ms(3);
//    for(i=0;i<len;i++)
//    {
//      //USART_ClearITPendingBit(USART2, USART_FLAG_TC);
//      USART_SendData8(USART2,buf[i]);//ͨ��UART���͵������� SendData9��
//      //while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);//���ָ����UART��־λ������񣬷������ݿ�λ��־
//      while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
//      //while((USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET));//�ȴ�DRΪ��
//      //USART_ClearITPendingBit(USART2, USART_FLAG_TC);
//    }
//    RS485_TX_EN_0;        //����Ϊ����ģʽ

  
      RS485_TX_EN_1;        //����ģʽ
      delay_ms(3);
      while(*buf)
     {
       //USART_ClearITPendingBit(USART2, USART_FLAG_TC);
       USART_SendData8(USART2,*buf++);
       //while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
       while((USART_GetFlagStatus(USART2,USART_FLAG_TC))==RESET);
       //USART_ClearITPendingBit(USART2, USART_FLAG_TC);
     }
     RS485_TX_EN_0; 
  
  
   /*
   UART2_SR &= 0xBF;//���TC
   UART2_DR=data;
   while(!(UART2_SR & 0x40));//�ȴ��������(TC   0x80-TXE
   UART2_SR &= 0xBF;//���TC
   */
}

//�����������򣬼������֡�Ľ��գ����ȹ��ܺ�����������ѭ���е���
uint8_t* UartDriver()
{
  static uint8_t len;
  static uint8_t buf[MAXLEN];
  if(flagFrame)         //֡������ɱ�־�������յ�һ֡������
  {
    flagFrame=0;        //֡������ɱ�־����
    len = UartRead(buf,sizeof(buf));//�����յ������������������
        /*****�˴���ʼ���ݽ���*****/
    if((buf[0]==0x68)&&(buf[1]==0x45)&&(buf[2]==0x45)&&(buf[3]==0x68))//hEEh
    {
      rs485_UartWrite(buf,len);
      //led;
      LED_OFF;
    }
  }
  return buf;
}

//���ڽ��ռ��
void UartRxMoniter(uint8_t ms)
{
  static uint8_t USART2_RX_BKP=0;        //����USART2_RC_BKP��ʱ�洢ʫ�䳤����ʵ�ʳ��ȱȽ�
  static uint8_t idletmr = 0;           //������ʱ��
  if(USART2_RX_CNT>0)//���ռ�����������ʱ��������߿���ʱ��
  {
    if(USART2_RX_BKP!=USART2_RX_CNT)//���ռ������ı䣬���ս��յ�����ʱ��������м�ʱ
    {
      USART2_RX_BKP=USART2_RX_CNT;  //��ֵ��������ʵ�ʳ��ȸ�ֵ��USART_RX_BK
      idletmr=0;                  //�����ʱ������
    }
    else        //�����ռ�����δ�ı䣬�����߿���ʱ���ۼƿ���ʱ��
    {
      //�����һ֡�������֮ǰ�г���3.5���ֽ�ʱ���ͣ�٣������豸��ˢ�µ�ǰʱ�����Ϣ���ٶ���һ���ֽ���һ���µ�����֡�Ŀ�ʼ
      if(idletmr<5)     //����ʱ��С��1msʱ�������ۼ�
      {
        idletmr+=ms;
        if(idletmr>=5)  //����ʱ��ﵽ1msʱ�����ж�1֡�������
        {
          flagFrame=1;//���������״̬��֡������ϱ�־
        }
      }
    }
  }
  else
  {
    USART2_RX_BKP=0;
  }
}

int BCD2int(uint8_t m)
{
   int a=0,b=1;
   uint8_t n;
   while(m)
   {
      n=0xF&m;
      m=m>>4;
      a=a+b*n;
      b=b*10;
   }
   return a;
}

//1ms��ʱ
void TIM2_Init()
{
  TIM2_DeInit();//HSI 16M
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE); //ʹ��
  TIM2_TimeBaseInit(TIM2_Prescaler_16, TIM2_CounterMode_Up, 1000);
  TIM2_SetCounter(0);
  TIM2_ITConfig(TIM2_IT_Update, ENABLE);
  TIM2_ARRPreloadConfig(ENABLE);
  TIM2_Cmd(ENABLE);       //������ʹ�ܣ���ʼ����  
}