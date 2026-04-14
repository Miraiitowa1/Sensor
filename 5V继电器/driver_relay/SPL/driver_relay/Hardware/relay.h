#ifndef __RELAY_H
#define __REALY_H


#include "stm32f10x.h"                  // Device header

#define RELAY_GPIO_CLK		RCC_APB2Periph_GPIOA
#define RELAY_GPIO_PIN		GPIO_Pin_0
#define RELAY_GPIO_PORT		GPIOA

#define RELAY_ON()			GPIO_SetBits(RELAY_GPIO_PORT, RELAY_GPIO_PIN)
#define RELAY_OFF()			GPIO_ResetBits(RELAY_GPIO_PORT, RELAY_GPIO_PIN)

#endif