#include "voice.h"

#define VOICE_DATA_H HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET)
#define VOICE_DATA_L HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET)
#define VOICE_RST_H  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET)
#define VOICE_RST_L  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET)


extern TIM_HandleTypeDef htim1;
uint16_t delay_nus;

void delay_us(uint32_t n_us);

//��������
void voice_play(uint8_t plusenum)
{
	uint8_t i;
	if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7))
		return;
	VOICE_RST_H;
	delay_us(660);
	VOICE_RST_L;
	delay_us(660);
	
	for (i = 0; i < plusenum; i++)
	{
		VOICE_DATA_H;
		delay_us(330);
		VOICE_DATA_L;
		delay_us(330);
	}
}
//��ʱ����ѯʵ����ʱn_us,
void delay_us(uint32_t n_us)  
{  
		uint16_t differ = 0xffff - n_us - 5;
		HAL_TIM_Base_Start(&htim1);
	  __HAL_TIM_SET_COUNTER(&htim1,differ);
	  while(differ < 0xffff-5)
    {
			 differ = __HAL_TIM_GET_COUNTER(&htim1);
		}
		HAL_TIM_Base_Stop(&htim1);
}  





