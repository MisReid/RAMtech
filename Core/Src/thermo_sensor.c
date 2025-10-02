/*
 * thermo_sensor.c
 *
 *  Created on: Sep 22, 2025
 *      Author: Reid
 */
#include "thermo_sensor.h"
#include "main.h"

extern ADC_HandleTypeDef hadc;

float thermo_read_temperature_f(void) {
	HAL_ADC_Start(&hadc);
	HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);

	uint32_t sum = 0;
	// Take 10 samples
	for (int i = 0; i < 10; i++)
	{
		uint16_t raw = HAL_ADC_GetValue(&hadc);
		sum += raw;
		HAL_Delay(2); // small delay to avoid reading the exact same sample
	}
	float avg_raw = sum / 10.0f;
	float voltage = 3.3 * avg_raw;
	float temp_f = voltage*0.393640928 - 586.8;
	return temp_f;
}
