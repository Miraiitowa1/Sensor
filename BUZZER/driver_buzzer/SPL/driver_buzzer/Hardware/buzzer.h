#ifndef __BUZZER_H
#define __BUZZER_H

//引脚定义
#define BUZZER_GPIO_PORT        GPIOA
#define BUZZER_GPIO_PIN         GPIO_Pin_0
#define BUZZER_GPIO_CLK         RCC_APB2Periph_GPIOA

//蜂鸣器控制宏定义
#define BUZZER_ON              GPIO_SetBits(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN);
#define BUZZER_OFF             GPIO_ResetBits(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN);
#define BUZZER_TOGGLE          GPIO_WriteBit(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN)));

//函数声明
void Buzzer_Init(void);

#endif