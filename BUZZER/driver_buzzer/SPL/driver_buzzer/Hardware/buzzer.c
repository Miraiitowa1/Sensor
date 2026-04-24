#include "stm32f10x.h"                  // Device header
#include "buzzer.h"

/**
  * 函    数：Buzzer_Init()
  * 参    数：无
  * 返 回 值：无
  * 说    明：蜂鸣器初始化
  */
void Buzzer_Init(void)
{
  //使能GPIO时钟
  RCC_APB2PeriphClockCmd(BUZZER_GPIO_CLK, ENABLE);

  //配置GPIO为推挽输出
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = BUZZER_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  //初始化GPIO
  GPIO_Init(BUZZER_GPIO_PORT, &GPIO_InitStructure);

  //默认关闭蜂鸣器
  BUZZER_OFF;
}
