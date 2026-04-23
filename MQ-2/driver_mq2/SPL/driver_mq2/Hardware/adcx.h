#ifndef __ADCX_H
#define __ADCX_H

#define ADCx            ADC1
#define ADCx_CLK        RCC_APB2Periph_ADC1

void ADCx_Init(void);
uint16_t ADCx_GetValue(uint8_t ADC_channel, uint8_t ADC_SampleTime);

#endif
