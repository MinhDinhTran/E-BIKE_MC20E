#ifndef __IOT_HUB_H__
#define __IOT_HUB_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stm32f0xx_hal.h"
#include "usart.h"

#define BUFLEN 512

typedef struct
{
	char imsi[16];
	char imei[16];
}dev_struct;

typedef enum
{
	AT_INIT,
	AT_CONNECTING,
	AT_CONNECTED,
	AT_CLOSE,
}AT_CMD_STATE;

#define __DEBUG__ 
#ifdef __DEBUG__
// #define IOT_DEBUG(format, ...) printf("File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)
#define IOT_DEBUG(format, ...) printf(format"\r\n", ##__VA_ARGS__)
#else
#define IOT_DEBUG(format, ...)
#endif

#define __DEBUG_LEVEL__ 
#ifdef __DEBUG_LEVEL__

#define D_FATAL 1
#define D_ALARM 2
#define D_ERROR 3
#define D_WARN  4
#define D_INFO  5
#define D_DEBUG 6

#define D_INFOR_LEVEL D_DEBUG

#define Logln(level, format, ...) do { \
    if (level <= D_INFOR_LEVEL) { \
        printf(format"\r\n", ##__VA_ARGS__); \
    } \
} while(0)

#define Log(level, format, ...) do { \
    if (level <= D_INFOR_LEVEL) { \
        printf(format, ##__VA_ARGS__); \
    } \
} while(0)

#else
#define Log(level, format, ...)
#endif

#define MODULE_BUFFER_SIZE  1024

extern char module_recv_buffer[MODULE_BUFFER_SIZE];
extern short module_recv_buffer_index;

typedef void (*parseFun)(void*,int);

typedef enum{
	AT_ATI,
	AT_ATE0,
	AT_IPR,
	AT_W,
	AT_CPIN,
	AT_CREG,
	AT_CSQ,
	AT_GSN,
	AT_CIMI,
	AT_QIMODE,
	AT_QICSP,
	AT_QIREGAPP,
	AT_QIACT,
	AT_COPS,
	AT_QIMUX,
	AT_QIDNSIP,
	AT_QIOPEN,
	AT_QISEND,
	AT_QRECV,
	AT_QICLOSE,
	AT_QPING,
	AT_QGPS_ON,
	AT_QGPS_OFF,
	AT_QGPS_RMC,
	AT_QGPS_GSV,
	AT_BT_ON,
	AT_BT_OFF,
	AT_BT_ADDR,
	AT_BT_NAME,
	AT_BT_Q_NAME,	
	AT_BT_VISB,
	
	AT_QBTGATSREG,
	AT_QBTGATSS,
	AT_QBTGATSC,
	AT_QBTGATSD,
	AT_QBTGATSST,
	AT_QBTGATSRSP,
	AT_QBTGATSIND,
	AT_QBTGATSDISC,

	ATA,
	AT_TEST,

	AT_MAX,
}AT_CMD;

typedef struct
{
	AT_CMD cmd;
	char cmd_txt[64];
	char cmd_ret[10];
	int timeout;
	parseFun fun;
}AT_STRUCT;

typedef struct
{
	AT_STRUCT at;
	char data[64];
	int len;
}RxMsgTypeDefExt;

typedef enum
{
	RET_A=1<<1,		//应答
	RET_P=1<<2,		//协议
	RET_B1=1<<3,		//蓝牙返回OK
	RET_B0=1<<4,	//蓝牙没接收完全
	RET_G=1<<5,		//GPS
	RET_AN=1<<6,	//其他
}RET_TYPE;

typedef struct
{
	unsigned char conn_id;
	unsigned char trans_id;
	unsigned int attr_handle;
}BT_CONN_STRUCT;

typedef struct
{
	unsigned int delay_time;
	unsigned int delay_count;
	char delay_flag;	//0 初始化，1延时计时中，2延时到达
	char retry_times;
}AT_PROCE_STRUCT;

void module_init(void);
char* get_imei(void);
char* get_imsi(void);
void send_data(char* buf, int len);
void AT_reconnect_service(void);
void at_process(void);
#endif
