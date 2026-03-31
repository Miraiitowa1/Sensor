#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "DHT11.h"


/**
  * 函    数：DHT11_Start
  * 参    数：无
  * 返 回 值：无
  * 说    明：进行数据传输前的配置
	拉低20ms，拉高13us 做起始信号
	主机发送 微处理器将单总线（SDA） 拉低一段时间（18~30ms） ， 通知传感器准备数据
**/
void DHT11_Start(void)
{
	DHT11_Mode(OUT);
	DHT11_Low;
	Delay_ms(20);
	DHT11_High;
	Delay_us(13);
}

/**
  * 函    数：DHT11_Check
  * 参    数：无
  * 返 回 值：无
  * 说    明：进行数据传输前的配置
	拉低83us（==100us），拉高87us（==100us） 做响应信号
	检测DHT11存在 0 存在 1 不存在
	从机发送 传感器将单总线（SDA） 拉低 83µs， 再接高 87µs 以响应主机的起始信号
**/
uint8_t DHT11_Check(void)
{
	uint8_t retry = 0;
	DHT11_Mode(IN);
	//DHT11拉低40~80us 高电平
	while(GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN) && retry < 100)
	{
		retry++;
		Delay_us(1);
	};
	if(retry >= 100)
	{
		return 1;
	}
	else 
	{
		retry = 0;
	}
	//DHT11拉低后再次拉高到40~80us 低电平
	while(!GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN) && retry < 100)
	{
		retry++;
		Delay_us(1);
	};
	if(retry >= 100)
	{
		return 1;
	}
	return 0;
}

/**
  * 函    数：DHT11_Read_Bit
  * 参    数：无
  * 返 回 值：无
  * 说    明：读取一位数据传输
**/
uint8_t DHT11_Read_Bit(void) 			 
{
 	uint8_t retry=0;
	while(GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN) && (retry < 100))
	{
		retry++;
		Delay_us(1);
	}
	retry=0;
	while(!GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN) && (retry < 100))
	{
		retry++;
		Delay_us(1);
	}
	Delay_us(40);
	if(GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN))
	{
		return 1;
	}
	else return 0;		   
}

/**
  * 函    数：DHT11_Read_Byte
  * 参    数：无
  * 返 回 值：无
  * 说    明：读取一字节数据传输
**/
uint8_t DHT11_Read_Byte(void)    
{        
	uint8_t Data = 0;
	for(int i = 0;i < 8; i++) 
	{
		Data <<= 1; 
		Data |= DHT11_Read_Bit();
	}						    
	return Data;
}

/**
  * 函    数：DHT11_Read_Data
  * 参    数：无
  * 返 回 值：无
  * 说    明：读取数据传输
	数据格式 湿度高位 + 湿度低位 + 温度高位 + 温度低位 = 校验数据
	模块存在精度问题 小数部分去掉
**/
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi)    
{        
 	uint8_t buf[5];
	DHT11_Start();
	if(DHT11_Check() == 0)
	{
		for(int i = 0;i < 5; i++)
		{
			buf[i] = DHT11_Read_Byte();
		}
		if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])
		{
			*humi=buf[0];
			*temp=buf[2];
		}
	}
	else return 1;
	return 0;	    
}

/**
  * 函    数：DHT11_Read_Data
  * 参    数：无
  * 返 回 值：无
  * 说    明：读取数据传输
**/
uint8_t DHT11_Init(void)
{
	RCC_APB2PeriphClockCmd(DHT11_GPIO_CLK, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = DHT11_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(DHT11_GPIO_PORT,DHT11_GPIO_PIN);
	
	DHT11_Start();
	return DHT11_Check();
}

/**
  * 函    数：DHT11_Mode
  * 参    数：无
  * 返 回 值：无
  * 说    明：进行输入输出切换
**/
void DHT11_Mode(uint8_t mode)
{
	//1 推挽输出 0 浮空输入
	GPIO_InitTypeDef GPIO_InitStructure;
	if(mode)
	{
		GPIO_InitStructure.GPIO_Pin = DHT11_GPIO_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	}
	else
	{
		GPIO_InitStructure.GPIO_Pin =  DHT11_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	}
	GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStructure);
}
