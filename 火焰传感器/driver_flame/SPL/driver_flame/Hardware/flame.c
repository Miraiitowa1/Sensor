#include "stm32f10x.h"
#include "adcx.h"
#include "Delay.h"
#include "math.h"
#include "flame.h"

/**
  * 函    数：FLAME_Init()
  * 参    数：无
  * 返 回 值：无
  * 说    明：配置FLAME的引脚和ADC
  */
void FLAME_Init(void)
{
    #if MODE_FLAME
    {
        //AO模式初始化
        GPIO_InitTypeDef GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(FLAME_AO_GPIO_CLK, ENABLE);
        GPIO_InitStructure.GPIO_Pin = FLAME_AO_GPIO_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入
        GPIO_Init(FLAME_AO_GPIO_PORT, &GPIO_InitStructure);
        
        ADCx_Init();
    }
    #else
    {
        //DO模式初始化
        GPIO_InitTypeDef GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(FLAME_DO_GPIO_CLK, ENABLE);
        GPIO_InitStructure.GPIO_Pin = FLAME_DO_GPIO_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
        GPIO_Init(FLAME_DO_GPIO_PORT, &GPIO_InitStructure);
    }
    #endif
}

/**
  * 函    数：AO模式 FLAME_ADC_Read()
  * 参    数：无
  * 返 回 值：无
  * 说    明：AO模式下读取FLAME传感器的ADC值，返回转换结果
  */
#if MODE_FLAME
uint16_t FLAME_ADC_Read(void)
{
	//设置指定ADC的规则组通道，采样时间
	return ADCx_GetValue(ADC_CHANNEL_FLAME_AO, ADC_SampleTime_55Cycles5);
}
#endif

uint16_t FLAME_FireData(void)
{
	
	#if MODE_FLAME
	uint32_t  tempData = 0;
	for (uint8_t i = 0; i < FLAME_READ_TIMES; i++)
	{
		tempData += FLAME_ADC_Read();
		Delay_ms(5);
	}

	tempData /= FLAME_READ_TIMES;
	return 4095 - (uint16_t)tempData;
	
	#else
	uint16_t tempData;
	tempData = !GPIO_ReadInputDataBit(FLAME_DO_GPIO_PORT, FLAME_DO_GPIO_PIN);
	return tempData;
	#endif
}

