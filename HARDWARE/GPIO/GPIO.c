#include "gpio.h"
#include <stdlib.h>
#include "exti.h"


#define true  1
#define false 0	

uint8_t batlock_status = 0,motorlock_status = 0;
uint8_t flag_lock = 0, flag_startlock = 0, flag_startunlock = 0, f_start_batlock = 0, f_start_motorlock = 0;
uint8_t flag_delay_lock, flag_delay_unlock, flag_batlock, flag_motorlock, flag_motorlock2,flag_alarm=1;
uint8_t flag_delay500ms, flag_delay900ms, flag_delay10ms, flag_delay4s,flag_delay8s; 
uint8_t f_motorlock;
uint8_t flag_tangze_unlock = 0,flag_tangze_lock = 0, flag_battery_lock = 0;
extern uint16_t tim14_delay900ms, tim14_delay500ms, tim14_delay10ms, tim14_delay4s;
uint8_t gsm_led_flag = 0;//0 ��1 ������2������˸
uint8_t gsm_led_count=0, gsm_led_on_off = 0;
//��������
void tangze_lock_bike(void)
{
    if (flag_tangze_lock) {
             if (!flag_startlock) {
                  flag_startlock = 1;
                    tangze_A_on;
                  tangze_B_off;
                  tim14_delay900ms = 0;
                  flag_delay900ms = 1;
                  flag_lock = 1;
             }
             if (flag_delay_lock) {
                    flag_delay_lock = 0;
                  flag_lock = 0;
                 flag_delay900ms = 0;
                tangze_A_off;
                  tangze_B_off;
                 flag_startlock = 0;
                 flag_tangze_lock = 0;
            }
    }
      
}
//�������
void tangze_unlock_bike(void)
{
    if (flag_tangze_unlock) {
         if (!flag_startunlock) {
                flag_startunlock = 1;
                tangze_A_off;
              tangze_B_on;
              tim14_delay900ms = 0;
              flag_delay900ms = 1;
              flag_lock = 2;
         }
         if (flag_delay_unlock) {
              flag_lock = 0;
                flag_delay_unlock = 0;
              flag_delay900ms = 0;
              tangze_A_off;
              tangze_B_off;
              flag_startunlock = 0;
              flag_tangze_unlock = 0;
         }
     }
}
/*tangze_unlock_bike�tangze_lock_bike��������ʱ��û�е��Ƿ���Ϊtrue,��ʱ����˷���Ϊfalse*/	
_Bool get_tangze_lock_status(void)
{
		if (flag_lock == 1 || flag_lock == 2) {
				return true;
		}
		else 
			  return false;
}	

//�����
void battery_lock(void)
{
  if (flag_battery_lock) {
        if (!f_start_batlock) {
            f_start_batlock = 1;
            battery_B_on;
            tim14_delay500ms = 0;
            flag_delay500ms = 1;
        }
        if (flag_batlock) {
            flag_batlock = 0;
            battery_B_off;
            flag_delay500ms = 0;
            flag_battery_lock = 0;
            f_start_batlock = 0;
        }
   }
}
//�������
void motor_lock_bike(void)
{
		if (!f_start_motorlock) {
			f_start_motorlock = 1;
			ACC_on;
			flag_delay10ms = 1;
			tim14_delay10ms = 0;
		}
		if (flag_motorlock) {
			flag_motorlock = 0;
			motor_A_on;
			flag_delay4s = 1;
			flag_delay10ms = 0;
			tim14_delay10ms = 0;
		}
		if (flag_motorlock2) {
			flag_motorlock2 = 0;
			flag_delay4s = 0;
			motor_A_off;
			ACC_off;
			f_start_motorlock = 0;
            f_motorlock = 0;
		}
}
_Bool get_open_motor_status(void)
{
	if (flag_delay4s == 1)
		return true;
	else 
		return false;
}
//��λϵͳ
void reset_system(void)
{
		HAL_NVIC_SystemReset();
}
/*PB5����*/
void open_electric_door(void)
{
    ACC_on;
}
/*PB5����*/
void close_electric_door(void)
{
    ACC_off;
}

void gsm_led_process(void)
{
	if(gsm_led_flag ==2)	//������˸
	{
		gsm_led_count++;
		if(gsm_led_on_off && gsm_led_count>=3)	//��100ms
		{
			gsm_led_off;
			gsm_led_on_off = 0;
			gsm_led_count = 0;
		}
		else if(!gsm_led_on_off && gsm_led_count >=27)	//��900ms
		{
			gsm_led_on;
			gsm_led_on_off = 1;
			gsm_led_count = 0;
		}
	}
	else if(gsm_led_flag ==1)
	{
		if(gsm_led_on_off==0)
			gsm_led_on;
	}
	else 
	{
		if(gsm_led_on_off==1)
			gsm_led_off;
	}
}


