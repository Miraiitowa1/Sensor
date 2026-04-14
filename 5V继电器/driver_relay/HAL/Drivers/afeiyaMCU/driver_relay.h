#ifndef __DRIVER_RELAY_H
#define __DRIVER_RELAY_H

#include "stm32f1xx_hal.h"

// 继电器引脚定义
#define RELAY_GPIO_PORT     GPIOA
#define RELAY_GPIO_PIN      GPIO_PIN_0

// 继电器控制宏
#define RELAY_ON()          HAL_GPIO_WritePin(RELAY_GPIO_PORT, RELAY_GPIO_PIN, GPIO_PIN_SET)
#define RELAY_OFF()         HAL_GPIO_WritePin(RELAY_GPIO_PORT, RELAY_GPIO_PIN, GPIO_PIN_RESET)
#define RELAY_TOGGLE()      HAL_GPIO_TogglePin(RELAY_GPIO_PORT, RELAY_GPIO_PIN)

// 函数声明
void RELAY_Init(void);

#endif