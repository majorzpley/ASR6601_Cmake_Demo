#ifndef __APP_H__
#define __APP_H__

#define RES_Up 39.0
#define ADC_DATA_NUM 10

void Get_NTC_Temp(void);
unsigned int Protocol_Crc16(unsigned char dat[], unsigned char lenth);

#endif
