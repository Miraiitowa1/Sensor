#include "stm32f10x.h"
#include "KEY.h"


/**
  * 函    数：KEY_Init
  * 参    数：无
  * 返 回 值：无
  * 说    明：初始化按键
  */
void KEY_Init(void)
{
    //使能GPIO时钟
    RCC_APB2PeriphClockCmd(KEY_GPIO_CLK, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    //配置GPIO为输入模式，带上拉电阻
    GPIO_InitStructure.GPIO_Pin = KEY_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //输入模式，带上拉电阻
    
    //初始化GPIO
    GPIO_Init(KEY_GPIO, &GPIO_InitStructure);

    //默认按键状态为OFF
    KEY_OFF;
}