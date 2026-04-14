#ifndef __DHT11_H
#define __DHT11_H

//引脚定义
#define DHT11_PORT 		GPIOA
#define DHT11_PIN 		GPIO_PIN_6
#define DHT11_TIMEOUT 	100

//模式定义
#define IN  0
#define OUT 1

//定义拉低电平函数
#define DHT11_Low  HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET);
//定义拉高电平函数
#define DHT11_High HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
//定义读取引脚状态函数
#define DHT11_READ  HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)

void DHT11_Mode(uint8_t mode);							//DHT11引脚输出模式控制
void DHT11_Rst(void);									//复位DHT11
uint8_t DHT11_Check(void);								//检测DHT11
uint8_t DHT11_Init(void);								//初始化DHT11
uint8_t DHT11_Read_Bit(void);							//读取一位数据 			 
uint8_t DHT11_Read_Byte(void);							//读取一字节数据
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi);	//读取温湿度数据

#endif