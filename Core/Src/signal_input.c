#include "signal_input.h"
#include <stdbool.h>
#include "main.h"

extern ADC_HandleTypeDef hadc;
extern TIM_HandleTypeDef htim2;

void signal_input_init(void)
{
	HAL_TIM_Base_Start(&htim2);
}

float signal_input_measure_frequency(void)
{
	ADC_ChannelConfTypeDef sConfig;
	sConfig.Channel = ADC_CHANNEL_4; // TODO: find correct channel number!!
	HAL_ADC_ConfigChannel(&hadc, &sConfig);
	uint8_t iter = 10;
	uint32_t prev = 0;
	uint32_t curr = 0;
	uint32_t sum = 0;
	for (uint8_t i = 0; i < iter; i++) {
		do {
			HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
		} while(HAL_ADC_GetValue(&hadc) != 1862);
		if (i == 0) {
			prev = HAL_TIM_GET_COUNTER(&htim2);
		} else {
			curr = HAL_TIM_GET_COUNTER(&htim2);
			sum += curr - prev;
		}
	}
	float freq = sum/iter;
	return freq;
}
