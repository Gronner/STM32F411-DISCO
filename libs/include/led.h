/*
 * Author:		Gronner@Github
 * Date:		2017-07-28	
 * Description:	Library to interface with the on-board LEDs of the STM32F411
 *				Discovery Board
 *				LED Numbers:
 *
 *				0 -> Green LED
 *				1 -> Orange LED
 *				2 -> Red LED
 *				3 -> Blue LED
 *
 */
#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>
#include <stdbool.h>

void led_init(void);
void led_on(uint8_t led);
void led_off(uint8_t led);
void led_toggle(uint8_t led);
bool led_get_state(uint8_t led); 

void led_on_all(void);
void led_off_all(void);
uint8_t  led_get_state_all(void);

#endif // __LED_H__

