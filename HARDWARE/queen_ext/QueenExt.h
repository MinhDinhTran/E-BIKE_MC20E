#ifndef __QUEENEXT_h
#define __QUEENEXT_h

#include <stdio.h>
#include "stm32f0xx_hal.h"
#include "IoT_Hub.h"
#define TRUE		1
#define FALSE		0
#define _FRONT		0
#define _REAR		1

#define ON  1		/*�ߵ�ƽ*/
#define OFF 0		/*�͵�ƽ*/

#define QueueExtSIZE     5	//20    //������еĴ�С

typedef int DataType;

typedef struct  
{      
	RxMsgTypeDefExt circle_buffer[QueueExtSIZE]; //
	unsigned char atom;	// ��    
	int front; //ָ���ͷ�������������ָ�Ŀռ䲻���Ԫ��      
	int rear; //ָ���β��������������һ��Ԫ��
	uint16_t free;   //ͳ�ƻ������������  
}CircleQueueExt; 



_Bool InitCircleQueueExt(CircleQueueExt *pCQ);
_Bool IsQueueExtEmpty(CircleQueueExt *pCQ);
_Bool IsQueueExtFull(CircleQueueExt *pCQ);
_Bool PushElementExt(CircleQueueExt *pCQ, RxMsgTypeDefExt dMsgData, unsigned char dir);
_Bool PopElementExt(CircleQueueExt *pCQ, RxMsgTypeDefExt *pMsgData);
void* mymemcpyExt(void* dest, void* source, int count);

#endif
