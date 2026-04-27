#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "mq135.h"

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
    MQ135_Init();
    
    OLED_ShowString(0, 0, "SMO:", OLED_8X16);
    OLED_ShowString(0, 16, "PPM:", OLED_8X16);
    

	  while(1)
	  {
		uint32_t value = MQ135_GetData();
		OLED_ShowNum(36, 0, value, 4, OLED_8X16);
		  
		float ppm = MQ135_GetData_PPM();
		OLED_Printf(36, 16, OLED_8X16,"%.4f", ppm);
		OLED_Update();
	  }
}
