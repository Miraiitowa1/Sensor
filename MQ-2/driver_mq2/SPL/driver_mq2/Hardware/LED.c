#include "stm32f10x.h"                  // Device header
#include "LED.h"

void LED_Init(void)
{
	//开启GPIOC的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	//配置LED引脚为推挽输出
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	//初始化LED引脚
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);

	//默认关闭LED
	LED_OFF;
}








