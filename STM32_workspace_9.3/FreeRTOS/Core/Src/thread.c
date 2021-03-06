/*
 * thread.c
 *
 *  Created on: 24 Apr 2020
 *      Author: cedric
 */

#include "main.h"
#include <local_leds.h>
#include "local_button.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal_gpio.h"



void thread_red(void *argument){
	while (1){
		LedRedOn();
		osDelay(400);
		LedRedOff();
		osDelay(400);
	}
}

void thread_blue(void *argument){
	WaitForLocalButtonReleased();
	while (1){
		LedBlueOn();
		osDelay(400);
		LedBlueOff();
		osDelay(400);
	}
}

void thread_green(void *argument){
	while (1){
	HAL_GPIO_EXTI_Callback(LD2_Pin);
		LedGreenOn();
		osDelay(400);
		LedGreenOff();
		osDelay(400);
	}
}

void thread_timer(void *argument){
	while (1){
		osDelay(100);
	}
}
