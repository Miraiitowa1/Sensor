#include "Delay.h"
#include "OLED.h"
#include "buzzer.h"
#include "stm32f10x.h" // Device header

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

int main(void) {
  OLED_Init();

  OLED_ShowString(0, 0, "driver_buzzer_on", OLED_8X16);

  BUZZER_ON;
  Delay_ms(500);
  BUZZER_OFF;

  OLED_Update();
}
