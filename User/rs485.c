#include "rs485.h"
#include "stm8l15x_usart.h"
#define MAXLEN 80	//接受字节最多数

uint8_t USART2_RX_BUF[MAXLEN];
extern uint8_t USART2_RX_BUF[MAXLEN];  //接收缓冲，最大MAXLEN字节
uint8_t USART2_RX_CNT=0;
extern uint8_t USART2_RX_CNT;         //接受字节计数器
uint8_t flagFrame=0;            //帧接收完成标志，即收到一帧新数据


uint8_t read_idx=0 ;
uint8_t read_len=0;
extern uint8_t read_idx;
extern uint8_t read_len;
      
//初始化UART2
void RS485_Init(uint32_t bound)
{

    CLK_PeripheralClockConfig(CLK_Peripheral_USART2, ENABLE);
    //GPIO_Init (GPIOE,GPIO_Pin_4,GPIO_Mode_Out_PP_High_Fast);
    //GPIO_Init (GPIOE,GPIO_Pin_3,GPIO_Mode_In_PU_No_IT);
    GPIO_ExternalPullUpConfig(GPIOE, GPIO_Pin_4 | GPIO_Pin_3, ENABLE);
   // USART init
    USART_DeInit(USART2);  

    // 初始化参数
    USART_Init(USART2,
                (uint32_t)2400,
                USART_WordLength_9b,
                USART_StopBits_1,
                USART_Parity_Even,
                USART_Mode_Rx | USART_Mode_Tx);  // 允许读和写

    // 开中断
    // 一般需要写时再开写中断，否则写中断会非常频繁以至于始终在执行中断
    // 读中断看具体业务
    USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);   

    /* Enable USART 使能 */
    USART_Cmd(USART2, ENABLE);
    enableInterrupts();
  
}
//计算接收到的数据长度，并放到buf中
uint8_t Uart2Read(uint8_t *buf)
{
  
//  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//  uint8_t i;
//  if(len<USART2_RX_CNT) //指定读取长度大于实际接受的数据长度时
//  {
//    len = USART2_RX_CNT;//读取长度设置为实际接收到的长度
//  }
//  for(i=0;i<len;i++)    //拷贝接收到的数据到接收指针中
//  {
//    *buf=USART2_RX_BUF[i];//将数据复制到buf中
//    buf++;
//  }
//  USART2_RX_CNT=0;      //接收计数器清零
//  
//  return len;           //返回实际读取长度
    for(int i=0;i<sizeof(buf);i++)
    {
      buf[i]=0x00;
    }
  
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    uint8_t i;

    for(i=0;i<USART2_RX_CNT;i++)    //拷贝接收到的数据到接收指针中
    {
      *buf=USART2_RX_BUF[i];//将数据复制到buf中
      buf++;
    }
    i=USART2_RX_CNT;
    USART2_RX_CNT=0;      //接收计数器清零
    
    return i;           //返回实际读取长度
  
//      // prepare send data
//    USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
//
//    // 初始化读缓冲
//    read_idx = 0;
//    read_len = 6;
//
//    // 开始读（开读中断）
//    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//    return read_len;
  
}

//发送
void rs485_UartWrite(uint8_t *buf,uint8_t len)
{

//    uint8_t i = 0;
//    RS485_TX_EN_1;        //发送模式
//    delay_ms(3);
//    for(i=0;i<len;i++)
//    {
//      //USART_ClearITPendingBit(USART2, USART_FLAG_TC);
//      USART_SendData8(USART2,buf[i]);//通过UART发送单个数据 SendData9？
//      //while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);//检查指定的UART标志位设置与否，发送数据空位标志
//      while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
//      //while((USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET));//等待DR为空
//      //USART_ClearITPendingBit(USART2, USART_FLAG_TC);
//    }
//    RS485_TX_EN_0;        //设置为接收模式

  
      RS485_TX_EN_1;        //发送模式
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
   UART2_SR &= 0xBF;//清空TC
   UART2_DR=data;
   while(!(UART2_SR & 0x40));//等待发送完成(TC   0x80-TXE
   UART2_SR &= 0xBF;//清空TC
   */
}

//串口驱动程序，检测数据帧的接收，调度功能函数，需在主循环中调用
uint8_t* UartDriver()
{
  static uint8_t len;
  static uint8_t buf[MAXLEN];
  if(flagFrame)         //帧接收完成标志，即接收到一帧新数据
  {
    flagFrame=0;        //帧接收完成标志清零
    len = UartRead(buf,sizeof(buf));//将接收到的命令读到缓冲区中
        /*****此处开始数据解析*****/
    if((buf[0]==0x68)&&(buf[1]==0x45)&&(buf[2]==0x45)&&(buf[3]==0x68))//hEEh
    {
      rs485_UartWrite(buf,len);
      //led;
      LED_OFF;
    }
  }
  return buf;
}

//串口接收监控
void UartRxMoniter(uint8_t ms)
{
  static uint8_t USART2_RX_BKP=0;        //定义USART2_RC_BKP暂时存储诗句长度与实际长度比较
  static uint8_t idletmr = 0;           //定义监控时间
  if(USART2_RX_CNT>0)//接收计数器大于零时，监控总线空闲时间
  {
    if(USART2_RX_BKP!=USART2_RX_CNT)//接收计数器改变，即刚接收到数据时，清零空闲计时
    {
      USART2_RX_BKP=USART2_RX_CNT;  //赋值操作，将实际长度赋值给USART_RX_BK
      idletmr=0;                  //将监控时间清零
    }
    else        //即接收计数器未改变，即总线空闲时，累计空闲时间
    {
      //如果在一帧数据完成之前有超过3.5个字节时间的停顿，接收设备将刷新当前时间的消息并假定下一个字节是一个新的数据帧的开始
      if(idletmr<5)     //空闲时间小于1ms时，持续累加
      {
        idletmr+=ms;
        if(idletmr>=5)  //空闲时间达到1ms时，即判定1帧接收完毕
        {
          flagFrame=1;//设置命令到达状态，帧接收完毕标志
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

//1ms定时
void TIM2_Init()
{
  TIM2_DeInit();//HSI 16M
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE); //使能
  TIM2_TimeBaseInit(TIM2_Prescaler_16, TIM2_CounterMode_Up, 1000);
  TIM2_SetCounter(0);
  TIM2_ITConfig(TIM2_IT_Update, ENABLE);
  TIM2_ARRPreloadConfig(ENABLE);
  TIM2_Cmd(ENABLE);       //计数器使能，开始计数  
}