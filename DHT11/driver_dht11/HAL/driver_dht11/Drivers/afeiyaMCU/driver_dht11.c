#include "stm32f1xx_hal.h" 
#include "driver_dht11.h"


/**
 * @brief 微秒级延时函数（基于 SysTick）
 * @param us: 延时的微秒数
 */
void HAL_Delay_us(uint32_t us)
{
    uint32_t ticks = us * (SystemCoreClock / 1000000U); // 1us = SystemCoreClock / 1e6 个时钟周期
    uint32_t start = SysTick->VAL;
    while ((start - SysTick->VAL) < ticks); // 注意：SysTick是向下计数
}

/**********************************************************************
 * 函数名称： DHT11_Mode
 * 功能描述： 温湿度传感器模式
 * 输入参数： uint8_t mode
 * 输出参数： 无
 * 返 回 值： 0 - 成功, 其他值 - 失败
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2026/3/23	     V1.0	  afeiya	      创建
 ***********************************************************************/
void DHT11_ModeChange(uint8_t mode)
{
	//1 推挽输出 0 浮空输入
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	GPIO_InitStructure.Pin = DHT11_PIN;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	
	if(mode)
	{
		// 设置引脚为推挽输出模式
		GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
	}
	else
	{
		// 设置引脚为浮空输入模式
		GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
		HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
	}
	HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
}

/**********************************************************************
 * 函数名称： DHT11_Rst
 * 功能描述： 温湿度传感器复位
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 0 - 成功, 其他值 - 失败
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2026/3/23	     V1.0	  afeiya	      创建
 ***********************************************************************/
void DHT11_Rst(void)
{
	DHT11_ModeChange(OUT);
	
	//起始拉低20ms
	DHT11_Low;
    HAL_Delay(20);
    
    //起始拉高13us
    DHT11_High
    HAL_Delay_us(13);
}

/**********************************************************************
 * 函数名称： DHT11_Check
 * 功能描述： 温湿度传感器响应
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 0 - 成功, 其他值 - 失败
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2026/3/23	     V1.0	  afeiya	      创建
 ***********************************************************************/
//检测DHT11存在 0 存在 1 不存在
uint8_t DHT11_Check(void)
{
	uint8_t retry = 0;
	DHT11_ModeChange(IN);
	
	//DHT11拉低40~80us 高电平
	while(DHT11_READ && (retry <  DHT11_TIMEOUT))
	{
		retry++;
		HAL_Delay(1);
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
	while(!DHT11_READ && (retry <  DHT11_TIMEOUT))
	{
		retry++;
		HAL_Delay(1);
	};
	if(retry >= 100)
	{
		return 1;
	}
	return 0;
}


/**********************************************************************
 * 函数名称： DHT11_Init
 * 功能描述： 温湿度传感器初始化
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 0 - 成功, 其他值 - 失败
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2026/3/23	     V1.0	  afeiya	      创建
 ***********************************************************************/
uint8_t DHT11_Init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // 配置为推挽输出模式
    GPIO_InitStructure.Pin = DHT11_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;  // HAL 模式
    GPIO_InitStructure.Pull = GPIO_NOPULL;          // 无上下拉
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW; // 低速（DHT11 不需要高速）
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStructure);

    // 初始拉高
    DHT11_High;

    // 复位并检测响应
    DHT11_Rst();
    return DHT11_Check();
}


/**********************************************************************
 * 函数名称： DHT11_Read_Bit
 * 功能描述： 温湿度传感器读取一位数据
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 0 - 成功, 其他值 - 失败
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2026/3/23	     V1.0	  afeiya	      创建
 ***********************************************************************/
uint8_t DHT11_Read_Bit(void) 			 
{
 	uint8_t retry=0;
	while(DHT11_READ && (retry < DHT11_TIMEOUT))
	{
		retry++;
		HAL_Delay(1);
	}
	retry=0;
	while(!DHT11_READ && (retry < DHT11_TIMEOUT))
	{
		retry++;
		HAL_Delay(1);
	}
	HAL_Delay(40);
	if(DHT11_READ)
	{
		return 1;
	}
	else return 0;		   
}

/**********************************************************************
 * 函数名称： DHT11_Read_Byte
 * 功能描述： 温湿度传感器读取一字节
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 0 - 成功, 其他值 - 失败
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2026/3/23	     V1.0	  afeiya	      创建
 ***********************************************************************/
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

/**********************************************************************
 * 函数名称： DHT11_Read_Data
 * 功能描述： 温湿度传感器读取数据
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 0 - 成功, 其他值 - 失败
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2026/3/23	     V1.0	  afeiya	      创建
 ***********************************************************************/
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi)    
{        
 	uint8_t buf[5];
	DHT11_Rst();
	
	if(DHT11_Check() == 0)
	{
		for(int i = 0;i < 5; i++)
		{
			buf[i] = DHT11_Read_Byte();
		}
		//判断 校验字节＝湿度高位+湿度低位+温度高位+温度低位
		if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])
		{
			//湿度高位+湿度低位 温度高位+温度低位 
			//精度问题 直接舍弃低位
			*humi=buf[0];
			*temp=buf[2];
		}
	}
	else return 1;
	return 0;	    
}

