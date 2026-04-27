#ifndef __MQ135_H
#define __MQ135_H

//MQ135传感器ADC循环次数
#define MQ135_READ_TIMES 10

//选择MQ135的工作模式：模拟输出（AO）或数字输出（DO）
#define MODE_MQ135    1   //1表示AO模式，0表示DO模式

//AO模式 MQ135传感器引脚定义
#if MODE_MQ135
#define MQ135_AO_GPIO_CLK     RCC_APB2Periph_GPIOA
#define MQ135_AO_GPIO_PORT    GPIOA
#define MQ135_AO_GPIO_PIN     GPIO_Pin_0
//MQ135传感器连接到ADC通道0
#define ADC_CHANNEL_MQ135_AO  ADC_Channel_0

//DO模式 MQ135传感器引脚定义
#else
#define MQ135_DO_GPIO_CLK     RCC_APB2Periph_GPIOA
#define MQ135_DO_GPIO_PORT    GPIOA
#define MQ135_DO_GPIO_PIN     GPIO_Pin_1
#endif

//函数声明
void MQ135_Init(void);
uint16_t MQ135_GetData(void);
float MQ135_GetData_PPM(void);

#endif


