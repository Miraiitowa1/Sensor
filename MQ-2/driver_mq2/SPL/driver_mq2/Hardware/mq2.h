#ifndef __MQ2_H
#define __MQ2_H

//MQ2传感器ADC循环次数
#define MQ2_READ_TIMES 10

//选择MQ2的工作模式：模拟输出（AO）或数字输出（DO）
#define MODE_MQ2    1   //1表示AO模式，0表示DO模式

//AO模式 MQ2传感器引脚定义
#if MODE_MQ2
#define MQ2_AO_GPIO_CLK     RCC_APB2Periph_GPIOA
#define MQ2_AO_GPIO_PORT    GPIOA
#define MQ2_AO_GPIO_PIN     GPIO_Pin_0
//MQ2传感器连接到ADC通道0
#define ADC_CHANNEL_MQ2_AO  ADC_Channel_0

//DO模式 MQ2传感器引脚定义
#else
#define MQ2_DO_GPIO_CLK     RCC_APB2Periph_GPIOA
#define MQ2_DO_GPIO_PORT    GPIOA
#define MQ2_DO_GPIO_PIN     GPIO_Pin_1
#endif

//函数声明
void MQ2_Init(void);
uint16_t MQ2_GetData(void);
float MQ2_GetData_PPM(void);

#endif


