#ifndef __DHT11_H
#define __DHT11_H

//引脚定义
#define DHT11_GPIO_PORT 	GPIOA
#define DHT11_GPIO_PIN  	GPIO_Pin_6
#define DHT11_GPIO_CLK		RCC_APB2Periph_GPIOA

//模式切换参数
#define IN  0
#define OUT 1

//DHT11控制宏定义
#define DHT11_Low       GPIO_ResetBits(DHT11_GPIO_PORT, DHT11_GPIO_PIN);
#define DHT11_High      GPIO_SetBits(DHT11_GPIO_PORT, DHT11_GPIO_PIN);

//函数声明
void DHT11_Mode(uint8_t mode);									//DHT11模式切换
void DHT11_Start(void);											//DHT11信号开始
uint8_t DHT11_Check(void);										//DHT11信号响应
uint8_t DHT11_Init(void);										//DHT11初始化
uint8_t DHT11_Read_Bit(void);									//DHT11读一位数据
uint8_t DHT11_Read_Byte(void);									//DHT11读一字节数据
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi);			//DHT11读数据

#endif