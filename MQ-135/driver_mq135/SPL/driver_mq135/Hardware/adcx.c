#include "stm32f10x.h"      
#include "adcx.h"

/**
  * 函    数：ADCx_Init()
  * 参    数：无
  * 返 回 值：无
  * 说    明：ADC初始化函数，配置ADC的时钟、模式、采样时间等参数，并进行校准
  */
void ADCx_Init(void)
{
	//开启ADC时钟
	RCC_APB2PeriphClockCmd(ADCx_CLK, ENABLE);
	
	//ADC频率进行6分频
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	//配置ADC结构体
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;					//独立模式
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				//数据右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//软件触发
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;					//单次转换
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;						//非扫描模式
	ADC_InitStructure.ADC_NbrOfChannel = 1;								//总通道数
	ADC_Init(ADCx, &ADC_InitStructure);									//初始化ADC1
	
	//开启ADCx
	ADC_Cmd(ADCx, ENABLE);
	
	//进行ADC校准
	ADC_ResetCalibration(ADCx);
	while(ADC_GetResetCalibrationStatus(ADCx) == SET);
	ADC_StartCalibration(ADCx);
	while(ADC_GetCalibrationStatus(ADCx) == SET);	
}

/**
  * 函    数：ADCX_GetValue()
  * 参    数：uint8_t ADC_channel, uint8_t ADC_SampleTime
  * 返 回 值：ADC转换值，如果超时返回0
  * 说    明：读取指定ADC通道的值，参数包括ADC通道号和采样时间，返回转换结果
  */
uint16_t ADCx_GetValue(uint8_t ADC_Channel,uint8_t ADC_SampleTime)
{
	//配置ADC通道
	ADC_RegularChannelConfig(ADCx, ADC_Channel, 1, ADC_SampleTime);
	
	ADC_SoftwareStartConvCmd(ADCx, ENABLE); //软件触发ADC转换
	while(ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET); //读取ADC转换完成标志位
	return ADC_GetConversionValue(ADCx);
}
