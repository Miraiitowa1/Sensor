#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "KEY.h"

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
	
	KEY_Init();
	
	OLED_ShowString(0, 0, "driver_oled", OLED_8X16);
	
	OLED_ShowString(0, 20, "hello,gy-30", OLED_8X16);
	
	OLED_Update();
}
