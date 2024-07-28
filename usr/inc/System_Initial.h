#ifndef __SYSTEM_INITIAL_H__
#define __SYSTEM_INITIAL_H__

#include "tremo_gpio.h"


#define REFEN_PORT 			GPIOA
#define REFEN_PIN   		GPIO_PIN_2

#define RUN_LED_PORT 		GPIOA
#define RUN_LED_PIN   	GPIO_PIN_3

#define BATT_EN_PORT 		GPIOA
#define BATT_EN_PIN   	GPIO_PIN_8

#define NTC_PORT 				GPIOA
#define NTC_PIN   			GPIO_PIN_4

#define BATT_PORT 			GPIOA
#define BATT_PIN   			GPIO_PIN_5

#define REFEN_H()				gpio_write(REFEN_PORT, REFEN_PIN, 1)
#define REFEN_L()				gpio_write(REFEN_PORT, REFEN_PIN, 0)

#define BATTEN_H()			gpio_write(BATT_EN_PORT, BATT_EN_PIN, 1)
#define BATTEN_L()			gpio_write(BATT_EN_PORT, BATT_EN_PIN, 0)

#define LED_OFF()				gpio_write(RUN_LED_PORT, RUN_LED_PIN, 1)
#define LED_ON()				gpio_write(RUN_LED_PORT, RUN_LED_PIN, 0)

void Gpio_init(void);
void Adc_init(void);
void uart_log_init(void);
void board_init();


#endif
