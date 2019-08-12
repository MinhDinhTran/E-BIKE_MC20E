#include "adc.h"
float adc_param=0;
 
uint16_t get_bat_vol(void)
{
   	uint8_t t;
   	uint32_t ADvol = 0, batvol_10mv;
	float bat_vol,ave_vol;
	 
   	ADvol=0;
	for(t = 0; t < 64; t++) 
	{              	//���òɼ�����
      		ADvol += adc_val[t];     						//�ɼ�����ADֵ 
   	}
	 ave_vol = ADvol / 64;
	 bat_vol = (ave_vol*adc_param)/4095;   		//�ó���ص�ѹֵ
	 batvol_10mv = (uint32_t)(bat_vol*100);	//+50; //��ѹ�Ŵ�100��	//��0.5v����������ѹ�����

         return batvol_10mv;                   
}

