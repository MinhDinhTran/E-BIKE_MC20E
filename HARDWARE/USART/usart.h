#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f0xx_hal.h"

#define  USART2_BUFFER_SIZE  120
//����1���ͻس�����
//#define UART_SendLR() UART_SendString("\r\n")
extern uint8_t Rx_len,flagUsartRx;
extern uint8_t ReceiveBuff[255];
/* Private variables ---------------------------------------------------------*/
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart1;

void UART_SendString(uint8_t* s);     //���͵�ǰ�ַ�
void UART_Data(uint8_t byte);         //���͵�ǰ����
void UartData_process(void);          //���յ������ݴ���
//void trace(char* buf, int len);
void uart2_send(uint8_t * pData,uint16_t Size);
void uart1_send(uint8_t * pData,uint16_t Size);
void uart2_process(void);

extern char usart2_recv_buffer[USART2_BUFFER_SIZE];
extern short usart2_recv_buffer_index;
#endif


