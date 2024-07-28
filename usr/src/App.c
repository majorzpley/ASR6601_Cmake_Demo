#include "App.h"
#include "System_Initial.h"
#include "tremo_uart.h"
#include "tremo_adc.h"
#include "stdint.h"
#include "tremo_regs.h"
#include "math.h"
#include "delay.h"

extern float gain_value, dco_value;

uint16_t adc_data_ntc[ADC_DATA_NUM] = {0};
uint16_t adc_data_batt[ADC_DATA_NUM] = {0};
float calibrated_NTC[ADC_DATA_NUM] = {0.0};
float calibrated_BATT[ADC_DATA_NUM] = {0.0};
/**
 * 将电阻值转换为温度值。
 *
 * 此函数根据惠斯登电桥的平衡条件和温度与电阻的关系，计算给定电阻在特定温度下的理论温度值。
 * 其中，_R1 是已知的电阻值，_R2 是待测电阻的值，_B 是温度系数，_T2 是待测电阻所处的环境温度。
 * 函数返回的是待测电阻的实际温度值（摄氏度）。
 *
 * @param _R1 已知的固定电阻的值。
 * @param _B 电阻的温度系数。
 * @param _R2 待测电阻的值。
 * @param _T2 环境温度（摄氏度）。
 * @return 返回计算得到的待测电阻的实际温度（摄氏度）。
 */
static float resistanceToTemperature(float _R1, float _B, float _R2, float _T2)
{
  return (1.0 / ((1.0 / _B) * log(_R1 / _R2) + (1.0 / (_T2 + 273.15))) - 273.15);
}

float NTC_Temp = 0.0;
uint8_t Batt_Value = 0;
/**
 * 获取NTC温度和电池电压
 * 该函数通过ADC采集NTC和电池电压的样本数据，然后进行校准计算，
 * 最终得到NTC的温度值和电池的百分比电量。
 */
void Get_NTC_Temp(void)
{
	uint8_t i;
	float NTC_I = 0.0, NTC_RES = 0.0, Batt = 0.0;

	REFEN_H();
	BATTEN_H();
	DelayMs(10);
	adc_enable(true);
	adc_start(true);

	for (i = 0; i < ADC_DATA_NUM; i++)
	{
		while (!adc_get_interrupt_status(ADC_ISR_EOC))
			;
		adc_data_ntc[i] = adc_get_data();
		while (!adc_get_interrupt_status(ADC_ISR_EOC))
			;
		adc_data_batt[i] = adc_get_data();
		while (!adc_get_interrupt_status(ADC_ISR_EOC))
			;
		(void)adc_get_data();
		adc_start(true);
		;
	}

	adc_start(false);
	adc_enable(false);
	REFEN_L();
	BATTEN_L();

	for (i = 0; i < ADC_DATA_NUM; i++)
	{
		calibrated_NTC[i] = ((1.2 / 4096) * adc_data_ntc[i] - dco_value) / gain_value + 0.02;
		calibrated_BATT[i] = 3.68 * (((1.2 / 4096) * adc_data_batt[i] - dco_value) / gain_value);
	}
	NTC_I = (2.5 - calibrated_NTC[5]) / RES_Up;
	NTC_RES = calibrated_NTC[5] / NTC_I;
	NTC_Temp = resistanceToTemperature(NTC_RES, 3950, 10, 25);

	Batt = ((calibrated_BATT[5] - 2.7) / (3.5 - 2.7)) * 100;
	if (Batt >= 100)
		Batt = 100;
	if (Batt <= 0)
		Batt = 0;
	Batt_Value = (char)Batt;
}

/**
 * 计算给定数据数组的CRC-16校验值。
 *
 * @param dat[] 待计算CRC校验值的数据数组。
 * @param lenth 数据数组的长度。
 * @return 返回计算得到的CRC-16校验值。
 *
 * 此函数实现了CRC-16校验算法，用于验证数据的完整性和真实性。
 * CRC校验通过计算一个固定长度的校验码并将其添加到数据中，以检查数据在传输或存储过程中是否发生了错误。
 * 这里的CRC-16算法使用了0xA001作为生成多项式。
 */
unsigned int Protocol_Crc16(unsigned char dat[], unsigned char lenth)
{
  unsigned char i, _Flag, _LSB = 0;
  unsigned int CRC_Value = 0xFFFF;
  for (i = 0; i < lenth; i++) //=-1
  {
    CRC_Value ^= dat[i];
    for (_Flag = 0; _Flag <= 7; _Flag++)
    {
      _LSB = (unsigned char)(CRC_Value & 0x0001);
      CRC_Value = CRC_Value >> 1;
      if (_LSB == 1)
        CRC_Value ^= 0xA001;
    }
  }
  return CRC_Value;
}
