#include "bsp.h"
#include "led.h"

void led_init(void)
{
	// Set Pins as output
	LED_PORT->MODER |= (1 << (LED_GREEN * 2));
	LED_PORT->MODER |= (1 << (LED_ORANGE * 2));
	LED_PORT->MODER |= (1 << (LED_RED * 2));
	LED_PORT->MODER |= (1 << (LED_BLUE* 2));
}

static uint8_t led_get_pin(uint8_t led)
{
	switch(led)
	{
		case 0:
			return LED_GREEN;
			break;
		case 1:
			return LED_ORANGE;
			break;
		case 2:
			return LED_RED;
			break;
		case 3:
			return LED_BLUE;
			break;
		default:
			return UINT8_MAX;
			break;
	}
}

void led_on(uint8_t led)
{
	uint8_t led_pin = UINT8_MAX;
	led_pin = led_get_pin(led);
	if(led_pin == UINT8_MAX)
	{
		return;
	}
	LED_PORT->ODR |= (1 << led_pin);
}

void led_off(uint8_t led)
{
	uint8_t led_pin = UINT8_MAX;
	led_pin = led_get_pin(led);
	if(led_pin == UINT8_MAX)
	{
		return;
	}
	LED_PORT->ODR &= ~(1 << led_pin);

}

void led_toggle(uint8_t led)
{
	uint8_t led_pin = UINT8_MAX;
	led_pin = led_get_pin(led);
	if(led_pin == UINT8_MAX)
	{
		return;
	}
	LED_PORT->ODR ^= (1 << led_pin);
}

bool led_get_state(uint8_t led)
{
	uint8_t led_pin = UINT8_MAX;
	led_pin = led_get_pin(led);
	if(led_pin == UINT8_MAX)
	{
		return UINT8_MAX;
	}

	if(LED_PORT->ODR & (1 << led_pin))
	{
		return true;
	}
	else
	{
		return false;
	}
}

