#include "System_Initial.h"
#include "timer.h"
#include "tremo_uart.h"
#include "tremo_gpio.h"
#include "tremo_rcc.h"
#include "tremo_pwr.h"
#include "rtc-board.h"
#include "tremo_adc.h"
#include "sx126x_Init.h"
#include <stdio.h>
#include "tremo_regs.h"
#include "tremo_rtc.h"
#include "tremo_rcc.h"
#include "tremo_pwr.h"
#include "tremo_iwdg.h"
#include "math.h"

char __errno;

void rtc_IRQHandler(void);

// GPIO��ʼ��
void Gpio_init(void)
{
	rcc_enable_peripheral_clk(RCC_PERIPHERAL_GPIOA, true);

	// NTC��Դ��������PA02
	gpio_init(REFEN_PORT, REFEN_PIN, GPIO_MODE_OUTPUT_PP_LOW);
	// ��ص�ѹԴ��������PA08
	gpio_init(BATT_EN_PORT, BATT_EN_PIN, GPIO_MODE_OUTPUT_PP_LOW);
	// LED��������PA03
	gpio_init(RUN_LED_PORT, RUN_LED_PIN, GPIO_MODE_OUTPUT_PP_HIGH);
	// NTC��������PA04
	gpio_init(NTC_PORT, NTC_PIN, GPIO_MODE_ANALOG);
	// BATT��������PA05
	gpio_init(BATT_PORT, BATT_PIN, GPIO_MODE_ANALOG);
}

// ���Ź���ʼ��
void iwdog_init(uint32_t timeout)
{
	// enable the iwdg clk
	rcc_enable_peripheral_clk(RCC_PERIPHERAL_IWDG, true);

	iwdg_init(true);
	iwdg_set_prescaler(IWDG_PRESCALER_256);
	iwdg_set_reload(timeout); // 8s
							  // start wdg
	iwdg_start();
}

// ADC��ʼ��
float gain_value = 1, dco_value = 0;

void Adc_init(void)
{
	adc_get_calibration_value(false, &gain_value, &dco_value);

	adc_init();

	adc_config_clock_division(20); // sample frequence 150K

	adc_config_sample_sequence(0, 4); // gpio_04,ADC_IN3
	adc_config_sample_sequence(1, 3); // gpio_05,ADC_IN2
	adc_config_sample_sequence(2, 3); // gpio_05,ADC_IN2

	adc_config_conv_mode(ADC_CONV_MODE_SINGLE); // ����ת��

	adc_start(false);
	adc_enable(false);
}

void uart_log_init(void)
{
	// uart0
	gpio_set_iomux(GPIOB, GPIO_PIN_0, 1);
	gpio_set_iomux(GPIOB, GPIO_PIN_1, 1);

	/* uart config struct init */
	uart_config_t uart_config;
	uart_config_init(&uart_config);

	uart_config.baudrate = UART_BAUDRATE_115200;
	uart_init(CONFIG_DEBUG_UART, &uart_config);
	uart_cmd(CONFIG_DEBUG_UART, ENABLE);
}

void board_init()
{
	rcc_enable_oscillator(RCC_OSC_XO32K, true);
	rcc_set_adc_clk_source(RCC_ADC_CLK_SOURCE_RCO48M);
	rcc_enable_peripheral_clk(RCC_PERIPHERAL_AFEC, true);
	rcc_enable_peripheral_clk(RCC_PERIPHERAL_UART0, true);
	rcc_enable_peripheral_clk(RCC_PERIPHERAL_GPIOA, true);
	rcc_enable_peripheral_clk(RCC_PERIPHERAL_GPIOB, true);
	rcc_enable_peripheral_clk(RCC_PERIPHERAL_GPIOC, true);
	rcc_enable_peripheral_clk(RCC_PERIPHERAL_GPIOD, true);
	rcc_enable_peripheral_clk(RCC_PERIPHERAL_PWR, true);
	rcc_enable_peripheral_clk(RCC_PERIPHERAL_RTC, true);
	rcc_enable_peripheral_clk(RCC_PERIPHERAL_SAC, true);
	rcc_enable_peripheral_clk(RCC_PERIPHERAL_LORA, true);
	rcc_enable_peripheral_clk(RCC_PERIPHERAL_ADC, true);

	Gpio_init();

	Adc_init();
	iwdog_init(0xFFF);
	LoRa_Init();
}