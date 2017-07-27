/*
 * Author:		Gronner@Github
 * Date:		2017-07-28	
 * Description:	Library to interface with the on-board LEDs of the STM32F411
 *				Discovery Board
 *
 */
#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>

void led_init(void);
void led_on(uint8_t led);
void led_off(uint8_t led);
void led_toggle(uint8_t led);

#endif // __LED_H__
