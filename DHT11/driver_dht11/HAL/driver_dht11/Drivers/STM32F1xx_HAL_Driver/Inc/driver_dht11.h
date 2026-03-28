#ifndef __DHT11_H
#define __DHT11_H

//引脚定义
#define DHT11_PORT 		GPIOA
#define DHT11_PIN 		GPIO_PIN_6

//超时参数
#define DHT11_TIMEOUT 	100

//模式切换参数
#define IN  0
#define OUT 1

#define DHT11_Low  HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET);
#define DHT11_High HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
#define DHT11_READ  HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)

void DHT11_Mode(uint8_t mode);									//DHT11模式切换
void DHT11_Start(void);											//DHT11信号开始
uint8_t DHT11_Check(void);										//DHT11信号响应
uint8_t DHT11_Init(void);										//DHT11初始化
uint8_t DHT11_Read_Bit(void);									//DHT11读一位数据
uint8_t DHT11_Read_Byte(void);									//DHT11读一字节数据
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi);			//DHT11读数据

#endif