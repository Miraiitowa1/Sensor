#ifndef __KEY_H
#define __KEY_H

//引脚配置
#define KEY_GPIO            GPIOA
#define KEY_GPIO_PIN        GPIO_Pin_0
#define KEY_GPIO_CLK        RCC_APB2Periph_GPIOA

//按键状态
#define KEY_ON              GPIO_ResetBits(KEY_GPIO, KEY_GPIO_PIN);
#define KEY_OFF             GPIO_SetBits(KEY_GPIO, KEY_GPIO_PIN);

//函数声明
void KEY_Init(void);

#endif
