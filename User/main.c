#include "stm8l15x.h"
#include "UART.h"
#include "bsp.h"
#include <string.h>
#include "stdio.h"

#define MAXLEN 80
extern uint8_t USART2_RX_BUF[MAXLEN];  //���ջ��壬���MAXLEN�ֽ�
extern uint8_t USART2_RX_CNT;         //�����ֽڼ�����



int main( void )
{
  
  
  uint8_t buf[6] = {0x10,0x5B,0xFE,0x59,0x16};//��ȡˮ��ָ��
  uint8_t get_down[] = "get_down\r";
  uint8_t result[] = "result 2 1 0 ";
  
  //uint8_t set_model[] = "model plou.gateway.1998\r"; 
  
  uint8_t rs485_buf[MAXLEN]="\0"; 
  uint8_t wifi_buf[MAXLEN]="\0";
  
  BSP_Initializes();
  USART1_Init(115200);
  RS485_Init(2400);
  TIM4_Init();
  TIM2_Init();
  
  
  printf(get_down);
  while(1)
  {
    Uart1Read(wifi_buf);//��ȡwifiָ��
    
    //if(strcmp("down get_properties 2 1\r", "down get_properties 2 1\r")==0)
    if(strcmp(wifi_buf, "down get_properties 2 1\r")==0)//��ָ��Ϊ��ȡ����������2 1
    {
      
      LED_OFF;
      delay_ms(100);
      LED_ON;
      delay_ms(100);
      LED_OFF;
      delay_ms(100);
      LED_ON;
      
      rs485_UartWrite(buf,sizeof(buf));//��ˮ����ָ��
      delay_ms(500);     
      Uart2Read(rs485_buf);//��ȡˮ������
      delay_ms(500);
      
      //�����ݱ�ͷ��ȷ
      if((rs485_buf[0]==0x68)&&(rs485_buf[1]==0x45)&&(rs485_buf[74]==0x16))
      {
        LED_OFF;
        delay_ms(1000);
        //BCD��ת����
        float flow=0;
        flow+=BCD2int(rs485_buf[22])*0.01;
        flow+=BCD2int(rs485_buf[23]);
        flow+=BCD2int(rs485_buf[24])*100;
        flow+=BCD2int(rs485_buf[25])*10000;
        uint8_t dstr[12];
        sprintf(dstr,"%.2lf",flow);//������������2λС����ֵ��dstr�ַ��� 
        printf("%s%s\r",result,dstr);//��wifi����
      }
      
    }
      delay_ms(500);
      printf(get_down);
        
  }
  return 0;
}
