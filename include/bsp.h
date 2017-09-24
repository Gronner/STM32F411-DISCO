/*
 * Author:		Gronner@Github
 * Date:		2017-07-28
 * Description:	Board specific definitions for the STM32F411E-DISCO Board
 *
 *
 */

#ifndef __BSP_H__
#define __BSP_H__
#include <stm32f4xx_gpio.h>

// Global Definitions
#define NULL ((void *)0)

// LED Definitions
#define LED_PORT GPIOD

#define LED_GREEN GPIO_PinSource12
#define LED_ORANGE GPIO_PinSource13
#define LED_RED GPIO_PinSource14
#define LED_BLUE GPIO_PinSource15

// Button Definitions
#define BUTTON_PORT GPIOA

#define BUTTON GPIO_PinSource0
// --> Button Timer Definitions
#define BUTTON_TIMER TIM3

// SPI Definitions
// L3GD20 Gyroscope
#define L3GD20_NSS_PORT GPIOE
#define L3GD20_NSS GPIO_PinSource3
#define L3GD20_SPI_PORT GPIOA
#define L3GD20_SCK GPIO_PinSource5
#define L3GD20_MOSI GPIO_PinSource7
#define L3GD20_MISO GPIO_PinSource6

#endif // __BSP_H__
