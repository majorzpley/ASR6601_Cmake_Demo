#include <stdio.h>
#include <string.h>
#include "delay.h"
#include "timer.h"
#include "radio.h"
#include "sx126x.h"
#include "System_Initial.h"
#include "tremo_uart.h"
#include "tremo_gpio.h"
#include "tremo_rcc.h"
#include "tremo_pwr.h"
#include "tremo_delay.h"
#include "rtc-board.h"
#include "tremo_iwdg.h"
#include "tremo_rtc.h"
#include "sx126x_Init.h"
#include "App.h"


uint8_t RF_Tx_Buff[64] = {0x01, 0x02};
uint16_t Run_Tick = 0, CRC_16 = 0;
extern float NTC_Temp;
extern uint8_t Batt_Value;
float NTC_Temp_Last = 0.0;
uint8_t Send_Flag = 0;

int main(void)
{
	board_init();
	RF_Tx_Buff[0] = 0xAA;		   // 帧头
	RF_Tx_Buff[1] = 0x02;		   // 类型码
	RF_Tx_Buff[2] = 0x24;		   // 生产年份
	RF_Tx_Buff[3] = 0x24;		   // 生产月份
	RF_Tx_Buff[4] = SN_NUM >> 8;   // SN号高八位
	RF_Tx_Buff[5] = SN_NUM & 0xff; // SN号低八位
	RF_Tx_Buff[6] = 0x01;		   // reserved
	RF_Tx_Buff[7] = 0x64;		   // 电池电量
	LED_ON();
	DelayMs(5000);

	/* Infinite loop */
	while (1)
	{
		Run_Tick++;
		iwdg_reload();
		LED_ON();
		Get_NTC_Temp();

		if (((NTC_Temp - NTC_Temp_Last) > 2) || ((NTC_Temp_Last - NTC_Temp) > 2))
		{
			Send_Flag = 1;
			NTC_Temp_Last = NTC_Temp;
		}

		if ((Send_Flag == 1) || (Run_Tick >= 120))
		{
			Run_Tick = 0;
			Send_Flag = 0;

			RF_Tx_Buff[7] = Batt_Value;
			RF_Tx_Buff[8] = (short)(NTC_Temp * 10) >> 8;
			RF_Tx_Buff[9] = (short)(NTC_Temp * 10) & 0xFF;

			CRC_16 = Protocol_Crc16(RF_Tx_Buff, 10);
			RF_Tx_Buff[10] = CRC_16 >> 8;
			RF_Tx_Buff[11] = CRC_16 & 0xFF;

			Radio_Send(RF_Tx_Buff, 12, 1000);
		}
		LED_OFF();
		//			DelayMs(1000 );
		rtc_alarm_wakeup(0, 10); // 1-59��;
		rtc_check_syn();
		pwr_deepsleep_wfi(PWR_LP_MODE_STOP3);
	}
}

#ifdef USE_FULL_ASSERT
void assert_failed(void *file, uint32_t line)
{
	(void)file;
	(void)line;

	while (1)
	{
	}
}
#endif
