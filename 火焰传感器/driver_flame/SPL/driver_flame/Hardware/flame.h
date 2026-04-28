#ifndef __FLAME_H
#define __FLAME_H

//FLAME传感器ADC循环次数
#define FLAME_READ_TIMES 10

//选择FLAME的工作模式：模拟输出（AO）或数字输出（DO）
#define MODE_FLAME    1   //1表示AO模式，0表示DO模式

//AO模式 FLAME传感器引脚定义
#if MODE_FLAME
#define FLAME_AO_GPIO_CLK     RCC_APB2Periph_GPIOA
#define FLAME_AO_GPIO_PORT    GPIOA
#define FLAME_AO_GPIO_PIN     GPIO_Pin_0
//FLAME传感器连接到ADC通道0
#define ADC_CHANNEL_FLAME_AO  ADC_Channel_0

//DO模式 FLAME传感器引脚定义
#else
#define FLAME_DO_GPIO_CLK     RCC_APB2Periph_GPIOA
#define FLAME_DO_GPIO_PORT    GPIOA
#define FLAME_DO_GPIO_PIN     GPIO_Pin_1
#endif

//函数声明
void FLAME_Init(void);
uint16_t FLAME_FireData(void);

#endif


