#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "DHT11.h"

/**
  * 坐标轴定义：
  * 左上角为(0, 0)点
  * 横向向右为X轴，取值范围：0~127
  * 纵向向下为Y轴，取值范围：0~63
  * 
  *       0             X轴           127 
  *      .------------------------------->
  *    0 |
  *      |
  *      |
  *      |
  *  Y轴 |
  *      |
  *      |
  *      |
  *   63 |
  *      v
  * 
  */

uint8_t temp, humi;

int main(void)
{
	OLED_Init();
	DHT11_Init();
	
	while (1)
	{
	
	//OLED_ShowString(0, 0, "driver_oled", OLED_8X16);
	DHT11_Read_Data(&temp, &humi);
	Delay_ms(1000);
	
	OLED_ShowString(0, 0, "Temp:", OLED_8X16);
	OLED_ShowNum(40, 0, temp, 2, OLED_8X16);
	OLED_ShowString(0, 16, "Humi:", OLED_8X16);
	OLED_ShowNum(40, 16, humi, 2, OLED_8X16);
	
	OLED_Update();
	}
}
