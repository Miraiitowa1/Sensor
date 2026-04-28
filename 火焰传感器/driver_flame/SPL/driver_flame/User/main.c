#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "flame.h"

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


int main(void)
{
    OLED_Init();
    FLAME_Init();
    
    OLED_ShowString(0, 0, "火焰强度：", OLED_8X16);

	  while(1)
	  {
		uint32_t value = FLAME_FireData();
		OLED_ShowNum(80, 0, value, 4, OLED_8X16);
		  
		if(value > 100)
		{
			OLED_ClearArea(0, 16, 128, 16);
			OLED_ShowString(0, 16, "fire!!!", OLED_8X16);
		}
		else
		{
			OLED_ClearArea(0, 16, 128, 16);
			OLED_ShowString(0, 16, "ok", OLED_8X16);
		}
		  
		OLED_Update();
	  }
}
