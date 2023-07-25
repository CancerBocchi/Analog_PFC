#include "inc.h"
#include "PFC_3PH.h"

#ifdef __HRTIM_H__
void HAL_HRTIM_RegistersUpdateCallback(HRTIM_HandleTypeDef * hhrtim,uint32_t TimerIdx)//周期回调
{
   //SPLL_lab1();
    SPLL_lab1();
}
#endif

#ifdef __ADC_H__

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)//adc转换完后进入中断
{
    //HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
    //ADC_Conversion(&ADC_Value);
}

#endif

#ifdef __TIM_H__

#endif