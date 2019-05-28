#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__
#include "stm32f0xx_hal.h"

#define MAX_GT_DEV_ID_BYTE_LEN 		8
#define MAX_GT_VER_STR_LEN 			16
#define MAX_GT_IMEI_LEN (16) 
#define MAX_GT_SEND_LEN 256

#define PACKET_FRAME_LEN (sizeof(pkg_head_struct) + sizeof(pkg_tail_struct))

typedef enum
{
	EN_INIT_STATE = 0,
	EN_CONNECT_STATE,
	EN_LOGING_STATE,
	EN_CONNECTED_STATE,	
}work_state;
typedef enum
{	
    EN_GT_LT_GPS = 0,
    EN_GT_LT_CELL,
    EN_GT_LT_END
} GT_LOC_TYPE_EN;

typedef enum
{
    EN_GT_GS_A = 1,	
    EN_GT_GS_V,
    EN_GT_GS_INV
} GT_GPS_STATE_EN;

typedef enum
{
    EN_GT_EAST = 0,
    EN_GT_SOUTH,
    EN_GT_WEST,
    EN_GT_NORTH,
    EN_GT_INV
} GT_ORIENTATION_EN;

typedef enum
{
    EN_GT_GM_N = 0,
    EN_GT_GM_A,
    EN_GT_GM_D,
    EN_GT_GM_E,
    EN_GT_GM_INV
} GT_GPS_MODE_EN;

typedef enum
{
	EN_GT_PT_BASE = 0,
	EN_GT_PT_LOGIN,
	EN_GT_PT_GPS,
	EN_GT_PT_STATUS,	
	EN_GT_PT_HB,
	EN_GT_PT_ALARM,	
	EN_GT_PT_DEV_DATA,	
	EN_GT_PT_CONTROL,
	EN_GT_PT_GIVE_BACK,
	EN_GT_PT_LBS,
	
	EN_GT_PT_SRV_DATA = 0x20,

        EN_GT_PT_END
} GT_PROT_TYPE_EN;

typedef enum
{
	EN_GT_DT_ADMIN_NUM = 0x00,
	EN_GT_DT_PWD = 0x01,
	EN_GT_DT_USER = 0x02,
	
	EN_GT_DT_UP_INTV = 0x03,
	EN_GT_DT_HB_INTV = 0x04,
	EN_GT_DT_SMS_ALARM_INTV = 0x05,
	
	EN_GT_DT_TEMP_THR = 0x06,
	EN_GT_DT_VIBR_THR = 0x07,
	EN_GT_DT_SPEED_THR = 0x08,
	
	EN_GT_DT_LANG = 0x09,
	EN_GT_DT_TIME_ZONE = 0x0a,
	
	EN_GT_DT_ALARM_SWITCH = 0x0b,
	EN_GT_DT_SMS_ALARM_SWITCH = 0x0c,
	
	EN_GT_DT_LOC = 0x0d,
	EN_GT_DT_IGNORE_ALARM = 0x0e,
	EN_GT_DT_LOG_LEVEL = 0x0f,
	
	EN_GT_DT_SET_TIME = 0x10,
	EN_GT_DT_SHUTDOWN = 0x12,
	EN_GT_DT_RESTORE = 0x13,
	EN_GT_DT_SMS = 0x14,

	EN_GT_DT_DEFENCE = 0x16,
	EN_GT_DT_SERVER = 0x17,
	EN_GT_DT_APN = 0x18,
	EN_GT_DT_SMS_CENTER = 0x19,
	EN_GT_DT_VER = 0x1A,

	EN_GT_DT_PWR_OIL_SWITCH = 0x20,
	EN_GT_DT_IO = 0x21,
	EN_GT_DT_IMSI = 0x22,
	EN_GT_DT_BT_ADDR = 0x23,
	
	EN_GT_CT_END
} GT_DATA_TYPE_EN;

typedef enum
{
	EN_GT_SWT_OFF = 0,
	EN_GT_SWT_ON,
	EN_GT_SWT_END
} GT_SWITCH_VALUE_EN;

typedef enum
{
	EN_GT_AT_PWR_LOW = 0,
	EN_GT_AT_PWR_OFF = 1,
	EN_GT_AT_VIBR = 2,
	EN_GT_AT_OIL_PWR = 3,
	EN_GT_AT_SPEED = 6,
	EN_GT_AT_END
} GT_ALARM_TYPE_EN;

typedef struct 
{
    uint16_t nYear;
    uint8_t nMonth;
    uint8_t nDay;
    uint8_t nHour;
    uint8_t nMin;
    uint8_t nSec;
} GPSDATETIME;
typedef struct
{
	uint8_t sat_num[32];
	uint8_t sat_db[32];
}GPSGSV;

typedef struct 
{
	GPSDATETIME dt;
	uint8_t state;
	double latitude;
	uint8_t NS;
	double longitude;
	uint8_t EW;
	double speed;
	double angle;
	double magnetic_value;
	uint8_t magnetic_ind;
	uint8_t mode;	//A ���� D ��� E���� N ������Ч

	uint8_t sat_uesd;	//��������
	double altitude;	//����
	double hdop;	//����

	uint8_t sat_view;	//�ɼ�����
	uint8_t type;	//��λ����1=δ��λ2=2D��λ3=3D��λ
	GPSGSV gsv;
}gps_info_struct;

typedef struct
{
	double lat;
	double lon;
}lat_lon_struct;

typedef enum
{
	AT_UP_RMC=0x01,
	AT_UP_GGA,
	AT_UP_LOGIN,
	AT_UP_VER,
	AT_UP_IMSI,
	AT_UP_BT_ADDR,
	AT_UP_GPS,
	AT_UP_ALARM,
	AT_UP_EBIKE,
	AT_UP_HB,
	AT_UP_CSQ,
	AT_UP_GIVEBACK,
}AT_UPLOAD_TYPE;

#pragma pack (1)	//ǿ���ֽڶ���
typedef struct 
{
	uint16_t start;     	//��ʼλ
	uint16_t crc;		//crcУ��
	uint8_t pack_len;	//������	---- ���ݳ���
	uint8_t prot_type;	//Э������
	uint16_t sn;	 		//�����к�
	uint8_t datetime[6];	//��ʱ��
}pkg_head_struct;

typedef struct 
{	
	uint16_t	stop;
}pkg_tail_struct;

typedef struct 
{
	uint8_t pwr_low_ind:1;
	uint8_t pwr_off_ind:1;
	uint8_t vibr_ind:1;
	uint8_t oil_pwr_ind:1;
	uint8_t sos_ind:1;
	uint8_t temp_ind:1;
	uint8_t speed_ind:1;
	uint8_t fence_ind:1;
	
	uint8_t pwr_level;
	uint8_t vibr_value;
	int8_t temp;
	uint16_t speed;
}alarm_struct;

typedef struct 
{	
	uint8_t pwr_low:1;//�͵籨������
	uint8_t pwr_off:1;//�ϵ�澯����
	uint8_t vibr:1;   //�𶯸澯����
	uint8_t oil_pwr:1;//���͵�澯����
	uint8_t sos:1;	 //sos�澯����
	uint8_t temp:1;   //�¶ȸ澯����
	uint8_t speed:1;  //���ٸ澯����
	uint8_t fence:1;
}switch_struct;


/********* 0x01 ��½��****************/
typedef struct 
{
	uint8_t   dev_id[MAX_GT_DEV_ID_BYTE_LEN];	//�豸id 15λIMEIת���ɵ�8λ�ֽ���
	uint8_t   dev_type;					//�豸����
	uint32_t auth_code;					//��֤��
}login_pkg_struct;

/********* 0x02 GPS ��****************/
typedef struct 
{	
	uint8_t lat_ind:1;	//0 ��γ 1 ��γ
	uint8_t long_ind:1;	//0  ����1����
	uint8_t mode:2;   	//0 ʵʱ 1 ��� 2 ���� 3 ��Ч �������ʵʱ����ֻ��߹��㣬˵��gps�Ѿ��ɹ���λ��
}gps_property_struct;

typedef struct 
{
	uint8_t loc_type;       	//��λ����
	uint8_t reserv_satnum;	//ǰ��λgps�������� + ����λ������
	gps_property_struct property;		//gps��������
	uint32_t latitude;		//γ��
	uint32_t longitude;		//����
	uint16_t speed;			//�ٶ�
	uint16_t course;			//����

	uint8_t reserv_sigstren;	//ǰ4bit��վ���ݱ������� ��4bit��վ�ź�ǿ��0-15
	uint16_t mcc;			//mcc
	uint8_t  mnc;			//mnc
	uint16_t lac_sid;		//lac
	uint16_t cellid_nid;		//cellid
	uint16_t bid;		    //�ݱ���
}gps_pkg_struct;

/********* 0x03 status ��****************/
typedef struct 
{	
	uint8_t oil_pwr_state:1;		//���͵�״̬ 0 �͵��ͨ 1 ���Ͷϵ�
	uint8_t sos_state:1;			//sos ״̬ 0 ��sos  1 ��sos
	uint8_t volt_level:3;        //��ѹ�ȼ� 0-6
	
	uint8_t temp;				//���϶��¶ȣ���δʵ��
}status_pkg_struct;

/********* 0x04 hb ��****************/
//������������
/********* 0x05 �澯 ��****************/
typedef struct 
{	
	uint8_t type;			//�澯����
	uint8_t value_len;		//ֵ�ĳ�������
	uint8_t value[6];	//�澯ֵ
}alarm_pkg_struct;

typedef  struct
{
	//ϵͳ����
	int8_t 	ver[MAX_GT_VER_STR_LEN];
	int8_t  dev_type;
	
	//��������
	int8_t vibr2_thr;	//�����𶯱���
	uint8_t vibr_thr;	
	uint16_t speed_thr;

	int16_t time_zone; //����24ʱ��	
	switch_struct alarm_switch;		//��������
	int8_t defence; 					//0 ���� 1���
} config_struct;

/********* 0x06 ���� ��****************/
typedef struct 
{	
	uint8_t type;			//��������
	uint8_t value_len;		//������������ ����
	uint8_t value[16];	//��������ֵ
}data_pkg_struct;

/****************************0x07��ȡ���������ݰ�**************************/
typedef struct
{
	uint8_t addr;		//0x1a �綯����������0x1b���վ��������0x1c��Ƭ�������ǿ���
	uint8_t value_len;
	uint8_t value[64];
}ebike_pkg_struct;


typedef struct 
{
	uint8_t datetime[6];
	uint8_t state;
	uint32_t latitude;
	uint8_t lat_ind;
	uint32_t longitude;
	uint8_t long_ind;
	uint16_t speed;
	uint16_t course;
	uint16_t magnetic_value;
	uint8_t magnetic_ind;
	uint8_t mode;//A ���� D ��� E���� N ������Ч

	uint8_t sat_uesed;
	uint16_t msl_altitude;
	uint16_t hdop;
}gps_data_struct;

/****************************0x08�������ݰ�******************************/
typedef struct
{
	uint8_t reserv_satnum;	//ǰ��λgps�������� + ����λ������
	gps_property_struct property;		//gps��������
	uint32_t latitude;		//γ��
	uint32_t longitude;		//����
	uint16_t speed;			//�ٶ�
	uint16_t course;			//����
}giveback_cell_struct;

typedef struct
{
	uint8_t lock_state;
	uint8_t gps_data_num;	//max 5
	giveback_cell_struct gps_array[5];
}give_back_pkg_struct;
/****************************0x09��վ���ݰ�******************************/
typedef struct
{
	uint16_t mcc;
	uint8_t mnc;
	uint16_t lac;
	uint16_t cellid;
	uint8_t sig;
}lbs_cell_struct;
typedef struct
{
	lbs_cell_struct service;
	uint8_t nbr_num;
	lbs_cell_struct nbr[6];
}lbs_pkg_struct;

typedef struct
{
	uint8_t lat[4];
	uint8_t lon[4];
}lbs_gps_struct;
#pragma pack ()//ǿ���ֽڶ���


extern void upload_login_package(void);
uint8_t kfd_format_cb_to_buffer(GT_PROT_TYPE_EN prot_type, uint8_t *context,uint8_t context_len);
void push_interval_package_process(void);
uint8_t protocol_parse(unsigned char *pBuf, int len);
void hex_convert_str(uint8_t *in,uint8_t len, uint8_t *out);
void str_convert_hex(char* in, int len, unsigned char* out);
uint16_t get_crc16(uint8_t* bytes, uint16_t len);
void upload_give_back_package(uint8_t gate);
void PopATcmd(void);


//void convert_gps_data_for_protocol(gps_info_struct* gps_data, gps_data_struct* kfd_gps_data);

#endif
