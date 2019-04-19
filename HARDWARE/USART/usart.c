#include "usart.h"	  
#include "stm32f0xx_hal.h"
#include <stdio.h> 
#include "queen.h"
#include <string.h>
#include <stdlib.h>
#include "bluetooth.h"
#include "Control_interface.h"

#ifdef __GNUC__  
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf 
     set to 'Yes') calls __io_putchar() */  
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)  
#else  
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)  
#endif /* __GNUC__ */  
  
/** 
  * @brief  Retargets the C library printf function to the USART. 
  * @param  None 
  * @retval None 
  */  
PUTCHAR_PROTOTYPE  
{  
  /* Place your implementation of fputc here */
  /* Loop until the end of transmission */  
   while(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_TC) == RESET){}   
  /* e.g. write a character to the USART */  
    huart2.Instance->TDR = (uint8_t) ch;  

  return ch;  
}  

char usart2_recv_buffer[USART2_BUFFER_SIZE] = {0};
short usart2_recv_buffer_index = 0;

/*******************************************************************************
* ������  : UART2_Data
* ����    : USART2����һ���ֽ�
* ����    : byte һ���ֽ�
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/

void uart1_send(uint8_t* pData, uint16_t Size)
{
	HAL_UART_Transmit(&huart1, pData, Size, 1000);
	while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC)!=SET); 
}

void uart2_send(uint8_t* pData, uint16_t Size)
{
	HAL_UART_Transmit(&huart2, pData, Size, 1000);
	while(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_TC)!=SET); 	
}

void uart2_process(void)
{
	  RxMsgTypeDef Uart2_Rxbuf;
	  if (PopElement(&RxUart2_Queue,&Uart2_Rxbuf) == TRUE)  //
  	 {
		usart2_recv_buffer[usart2_recv_buffer_index] = Uart2_Rxbuf.Data[0]; //�����յ����ַ����浽������
		usart2_recv_buffer_index++;
		if(usart2_recv_buffer_index > 125)       														//���������,������ָ��ָ�򻺴���׵�ַ
		{
			usart2_recv_buffer_index = 0;
		}
	}
	else
	{   
		 if (usart2_recv_buffer_index > 0)
		{
			if(parse_control_cmd(usart2_recv_buffer,usart2_recv_buffer_index))
			{
				usart2_recv_buffer_index = 0;
				memset(usart2_recv_buffer, 0, strlen(usart2_recv_buffer));
			}
		}
	}
}

