#ifndef __QUEEN_h
#define __QUEEN_h

#include <stdio.h>
#include "stm32f0xx_hal.h"

#define TRUE		1
#define FALSE		0
#define _FRONT		0
#define _REAR		1

#define ON  1		/*�ߵ�ƽ*/
#define OFF 0		/*�͵�ƽ*/

#define QUEUESIZE     200    //������еĴ�С
#define BUFFER_SIZE   50  //���建������Ĵ�С 

typedef int DataType;
//typedef char bool;
typedef struct
{
	//uint8_t Len;              //���ݳ���
	uint8_t Data[1];        //����
}RxMsgTypeDef;
typedef struct  
{      
	RxMsgTypeDef circle_buffer[QUEUESIZE]; //
	unsigned char atom;	// ��    
	int front; //ָ���ͷ�������������ָ�Ŀռ䲻���Ԫ��      
	int rear; //ָ���β��������������һ��Ԫ��
	uint16_t free;   //ͳ�ƻ������������  
}CircleQueue; 
typedef struct
{
   uint8_t circle_buffer[BUFFER_SIZE]; //
   uint8_t atom;                // ��
   uint8_t front;               //ָ���ͷ�������������ָ�Ŀռ䲻���Ԫ�� 
   uint8_t rear;                //ָ���β��������������һ��Ԫ�� 
}Circle_buffer;

// extern CircleQueue		 TxCAN_Queue;
extern CircleQueue		 RxUart1_Queue;		/* ����1���ջ�����*/
extern CircleQueue		 RxUart2_Queue;		/* ����2���ջ�����*/
extern Circle_buffer buffer;
extern RxMsgTypeDef Uart1_buf, Uart2_buf;

_Bool InitCircleQueue(CircleQueue *pCQ);
_Bool IsQueueEmpty(CircleQueue *pCQ);
_Bool IsQueueFull(CircleQueue *pCQ);
_Bool PushElement(CircleQueue *pCQ, RxMsgTypeDef dMsgData, unsigned char dir);
_Bool PopElement(CircleQueue *pCQ, RxMsgTypeDef *pMsgData);
//bool GetHeadElement(CircleQueue *pCQ, CanRxMsgTypeDef *pMsgData);
void* mymemcpy(void* dest, void* source, int count);
uint8_t bufferPop(uint8_t* _buf);
void bufferPush(const uint8_t _buf);
void bufferInit(void);


#endif
