#include "stm32f10x.h"                  // Device header
#include "relay.h"

void RELAY_Init(void)
{
	RCC_APB2PeriphClockCmd(RELAY_GPIO_CLK, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = RELAY_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(RELAY_GPIO_PORT, &GPIO_InitStructure);
	
	RELAY_OFF();
}


