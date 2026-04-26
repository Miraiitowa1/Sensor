#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "KEY.h"
#include "stepper motor.h"

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
	Stepper_Motor_Init();
	
	OLED_ShowString(0, 0, "driver_stepper_motor", OLED_8X16);
	
	while (1)
	{
		Stepper_Motor_Direction_Angle(1, 0, 90, 10);
		Delay_ms(500);
		Stepper_Motor_Direction_Angle(0, 0, 90, 10);
		Delay_ms(500);
	}
	
	
	OLED_Update();
}
