

/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/stm8l15x_it.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_it.h"
#include "rs485.h"
#define MAXLEN 80	//接受字节最多数

extern uint8_t USART1_RX_BUF[MAXLEN];
extern uint8_t USART1_RX_CNT;
//bool read_finish_flag = FALSE;
extern bool read_finish_flag;

extern uint8_t USART2_RX_BUF[MAXLEN];  //接收缓冲，最大MAXLEN字节
//int8_t USART2_RX_CNT=0;
extern uint8_t USART2_RX_CNT;         //接受字节计数器

extern uint8_t read_idx;
extern uint8_t read_len;
//extern uint8_t USART2_TX;  

/** @addtogroup STM8L15x_StdPeriph_Template
  * @{
  */
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

#ifdef _COSMIC_
/**
  * @brief Dummy interrupt routine
  * @par Parameters:
  * None
  * @retval 
  * None
*/
INTERRUPT_HANDLER(NonHandledInterrupt,0)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
#endif

/**
  * @brief TRAP interrupt routine
  * @par Parameters:
  * None
  * @retval 
  * None
*/
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief FLASH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(FLASH_IRQHandler,1)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief DMA1 channel0 and channel1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(DMA1_CHANNEL0_1_IRQHandler,2)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief DMA1 channel2 and channel3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(DMA1_CHANNEL2_3_IRQHandler,3)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief RTC / CSS_LSE Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(RTC_CSSLSE_IRQHandler,4)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief External IT PORTE/F and PVD Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIE_F_PVD_IRQHandler,5)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PORTB / PORTG Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIB_G_IRQHandler,6)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PORTD /PORTH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTID_H_IRQHandler,7)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN0 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI0_IRQHandler,8)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI1_IRQHandler,9)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN2 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI2_IRQHandler,10)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI3_IRQHandler,11)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN4 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI4_IRQHandler,12)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN5 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI5_IRQHandler,13)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN6 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI6_IRQHandler,14)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN7 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI7_IRQHandler,15)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief LCD /AES Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(LCD_AES_IRQHandler,16)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief CLK switch/CSS/TIM1 break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SWITCH_CSS_BREAK_DAC_IRQHandler,17)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief ADC1/Comparator Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(ADC1_COMP_IRQHandler,18)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief TIM2 Update/Overflow/Trigger/Break /USART2 TX Interrupt routine.
  * @param  None
  * @retval None
  */

INTERRUPT_HANDLER(TIM2_UPD_OVF_TRG_BRK_USART2_TX_IRQHandler,19)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  
  if( USART_GetITStatus(USART2, USART_IT_TXE) == SET  )
  {
//      // 发送1字节
//      USART_SendData8(USART2, writ_buffer[writ_idx++]);
//      USART_ClearITPendingBit(USART2, USART_IT_TC);
//
//      // 等待缓冲数据全部写出后，关写中断
//      if( writ_idx == writ_len ) {
//          USART_ITConfig(USART2, USART_IT_TC, DISABLE);
//          // 你的处理
//      }  
  }
  
  else
  {
    //UartRxMoniter(1);
    TIM2_ClearITPendingBit(TIM2_IT_Update); 
  }
}

/**
  * @brief Timer2 Capture/Compare / USART2 RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_CC_USART2_RX_IRQHandler,20)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  //LED_OFF;
  uint8_t res=0;
  if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)//接收到新数据
  {
    res = USART_ReceiveData8(USART2);//读取接收到的数据USART->DR
    if(USART2_RX_CNT<sizeof(USART2_RX_BUF))//一次只能只收到MAXLEN个字节，人为设定，可以更大，但浪费时间
    {
      USART2_RX_BUF[USART2_RX_CNT]=res;//记录接收到的值
      USART2_RX_CNT++;//使收数据增加1
    }
    //LED
  }
  
  
//    uint8_t temp = 0;
//
//    // 读1字节，存入读缓区
//    temp = USART_ReceiveData8(USART2);
//    USART2_RX_BUF[USART2_RX_CNT++] = temp;
//
//    // 等待全部读完后（如果有设定读长度的话）关读中断
//    // 这里根据具体业务，可以不关中断一直接受数据
//    if( USART2_RX_CNT == read_len ) {
//        USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
//    }
  
}


/**
  * @brief Timer3 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQHandler,21)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief Timer3 Capture/Compare /USART3 RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_CC_USART3_RX_IRQHandler,22)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief TIM1 Update/Overflow/Trigger/Commutation Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_COM_IRQHandler,23)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief TIM1 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_CC_IRQHandler,24)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief TIM4 Update/Overflow/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM4_UPD_OVF_TRG_IRQHandler,25)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief SPI1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SPI1_IRQHandler,26)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */		
}

/**
  * @brief USART1 TX / TIM5 Update/Overflow/Trigger/Break Interrupt  routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(USART1_TX_TIM5_UPD_OVF_TRG_BRK_IRQHandler,27)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 
  //USART_ITConfig(USART1, USART_IT_TC, DISABLE);
  //USART_ClearITPendingBit(USART1, USART_IT_TC);

}

/**
  * @brief USART1 RX / Timer5 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(USART1_RX_TIM5_CC_IRQHandler,28)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */

//  if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
//  {
//    if(USART_ReceiveData8(USART1)!='\r')
//    {
//      USART1_RX_BUF[USART1_RX_CNT] = USART_ReceiveData8(USART1);
//      USART1_RX_CNT++;
//    }
//    else
//    {
//      //接收完成标志位置1
//      read_finish_flag = TRUE;
//      USART1_RX_CNT=0;
//    }
//    USART_ClearITPendingBit(USART1,USART_FLAG_RXNE);
//    USART_ClearITPendingBit(USART1,USART_FLAG_TC);
//  }
  
  uint8_t res=0;
  if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)//接收到新数据
  {
    res = USART_ReceiveData8(USART1);//读取接收到的数据USART->DR
    if(USART1_RX_CNT<sizeof(USART1_RX_BUF))//一次只能只收到MAXLEN个字节，人为设定，可以更大，但浪费时间
    {
      USART1_RX_BUF[USART1_RX_CNT]=res;//记录接收到的值
      USART1_RX_CNT++;//使收数据增加1
    }
    //LED
  }
  
//    uint8_t temp = 0;
//    // 读1字节，存入读缓区
//    temp = USART_ReceiveData8(USART1);
//    USART1_RX_BUF[USART1_RX_CNT++] = temp;
//
//    if( USART1_RX_CNT == '\r' ) {
//        USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
//    }
  

    
  
//    uint8_t res=0;  
//    uint8_t des=0; 
//    res=USART_ReceiveData9(USART1);
//    des=USART_ReceiveData8(USART1);
//    // 读1字节，存入读缓区
//    USART1_RX_BUF[USART1_RX_CNT++] = res;
//    USART1_RX_BUF[USART1_RX_CNT++] = des;
//    
//    if( USART_ReceiveData9(USART1) == '\r' ) {
//        USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
//    }
//    if( USART_ReceiveData9(USART1) == 0x0d ) {
//        USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
//    }
//    if( USART1_RX_CNT == 10 ) {
//        USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
//    }
   
/*
  1.wifi发过来的信息格式不同
  2.接受不能用temp=USART_Receive8                    
*/

}
/**
  * @brief I2C1 / SPI2 Interrupt routine.
  * @param  None
  * @retval None
  */
 
INTERRUPT_HANDLER(I2C1_SPI2_IRQHandler,29)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/