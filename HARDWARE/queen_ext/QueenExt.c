/*******************************************************************************
 * File name:           queen.c
 * Descriptions:        ������غ���
 * Created date:        2016-11-22
 * Last modified Date:  2016-11-22
********************************************************************************/
#include <stdio.h>
#include "queenExt.h"
#include "string.h"
#include <stdlib.h>

// CircleQueueExt		 TxCAN_QueueExt;	/* CAN ���ͻ�����*/
/*********************************************************************************************************
** Functoin name:       InitCircleQueueExt
** Descriptions:        ��ʼ�����У�ʹ����ͷָ�����β
** input paraments:     �������    
** Returned values:     TRUE��ʼ���ɹ�������ʧ��
*********************************************************************************************************/
_Bool InitCircleQueueExt(CircleQueueExt *pCQ)  
{       
     if (pCQ == NULL)          
	 	return FALSE;      
	 else      
	 	{         
	 	  pCQ->front = 0;          
		  pCQ->rear = 0;
		  pCQ->free=QueueExtSIZE;
		  pCQ->atom = FALSE;   
		}  
	 return TRUE;  
}  
void ClearQueueExt(CircleQueueExt *pCQ)  //�����
{
    pCQ->front = 0;          
		pCQ->rear = 0;
	  pCQ->free=QueueExtSIZE;
}
/*********************************************************************************************************
** Functoin name:       IsQueueExtEmpty
** Descriptions:        �������Ƿ�Ϊ��
** input paraments:     ����ָ�� CircleQueueExt *pCQ
** Returned values:     TRUEΪ��
*********************************************************************************************************/
_Bool IsQueueExtEmpty(CircleQueueExt *pCQ) 
{      
      if (pCQ->front == pCQ->rear)         
				return TRUE;     
			else          
				return FALSE;  
}    
/*********************************************************************************************************
** Functoin name:       IsQueueExtFull
** Descriptions:        �������Ƿ�����
** input paraments:     ����ָ�� CircleQueueExt *pCQ
** Returned values:     TRUEΪ��
*********************************************************************************************************/
_Bool IsQueueExtFull(CircleQueueExt *pCQ) 
{     
   if ((pCQ->rear + 1) % QueueExtSIZE == pCQ->front)         
	 	return TRUE;     
	 else          
	 	return FALSE; 
}   
/*********************************************************************************************************
** Functoin name:       PushElement
** Descriptions:        ��Ԫ��ѹ�����
** input paraments:     ����ָ�� CircleQueueExt *pCQ�� Ҫѹ���ֵCanRxMsg dMsgData
** Returned values:     TRUEѹ����гɹ�������ʧ��
*********************************************************************************************************/
_Bool PushElementExt(CircleQueueExt *pCQ, RxMsgTypeDefExt dMsgData, unsigned char dir)
{  	
   if (IsQueueExtFull(pCQ)) 
	{
		return FALSE;
    //ClearQueueExt(pCQ);  //�����	
	}
	pCQ->atom = TRUE;

	if(dir == _REAR) 
    {
		pCQ->rear = (pCQ->rear + 1) % QueueExtSIZE;  
		mymemcpyExt(&(pCQ->circle_buffer[pCQ->rear]), &dMsgData, sizeof(RxMsgTypeDefExt));
		pCQ->free--;
	} 
	else if(dir == _FRONT) 
	{
		mymemcpyExt(&(pCQ->circle_buffer[pCQ->front]), &dMsgData, sizeof(RxMsgTypeDefExt));
		if(pCQ->front == 0) 
		{
			pCQ->front = (QueueExtSIZE - 1);
		} 
		else 
		{
			pCQ->front = (pCQ->front - 1);
		}
		pCQ->free--;
	} 
	else 
	{
		return FALSE;
	}
	
	pCQ->atom = FALSE;
	return TRUE;  
} 
/*********************************************************************************************************
** Functoin name:       PopElement
** Descriptions:        �����е�Ԫ��ȡ��
** input paraments:     ����ָ��CircleQueueExt *pCQ������ѹ�����еĽṹ��ָ��CanRxMsg *pMsgData
** Returned values:     TRUEΪ����ѹ���ɹ�������ʧ��
*********************************************************************************************************/
_Bool PopElementExt(CircleQueueExt *pCQ, RxMsgTypeDefExt *pMsgData)
{      
   if( (IsQueueExtEmpty(pCQ)) || (pCQ->atom == TRUE) )        
	 	return FALSE;       
	 pCQ->front = (pCQ->front + 1) % QueueExtSIZE;  	
	 mymemcpyExt(pMsgData, &(pCQ->circle_buffer[pCQ->front]), sizeof(RxMsgTypeDefExt)); 
	 pCQ->free++;
     
	 return TRUE;  
} 
/*********************************************************************************************************
** Functoin name:       mymemcpyExt
** Descriptions:        �����ݴ�Դ��ַ������Ŀ���ַ
** input paraments:     dest Ŀ�ĵ�ַ source Դ��ַ count ��������
** Returned values:     ��
*********************************************************************************************************/
void* mymemcpyExt(void* dest, void* source, int count)
{
	char *ret = (char *)dest;
	char *dest_t = ret;
	char *source_t = (char *)source;
	
	while (count--)
		*dest_t++ = *source_t++; 
	
	return ret;
}
