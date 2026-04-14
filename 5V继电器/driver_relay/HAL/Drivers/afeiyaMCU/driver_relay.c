#include "stm32f1xx_hal.h"
#include "driver_relay.h"

void RELAY_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    GPIO_InitStruct.Pin = RELAY_GPIO_PIN;                
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;          
    GPIO_InitStruct.Pull = GPIO_NOPULL;                  
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;        
    
    HAL_GPIO_Init(RELAY_GPIO_PORT, &GPIO_InitStruct);
    
    RELAY_OFF();
}