#include <stdbool.h>
#include "bsp.h"
#include "button.h"
#include "misc.h"
#include "timer.h"

static bool button_timer_active = false;
static volatile uint16_t button_counter = 0;

void button_init(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	__asm("dsb");

	BUTTON_PORT->MODER &= ~(11 << BUTTON * 2);
	BUTTON_PORT->PUPDR &= ~(11 << BUTTON * 2);
	if(button_timer_active == false)
	{
		timer_init(BUTTON_TIMER);
		timer_start(BUTTON_TIMER);
		timer_set_prediv(BUTTON_TIMER, 40000);
		timer_set_ccrvalue(BUTTON_TIMER, 70);
		timer_enable_interrupt(BUTTON_TIMER, 0, 1);
		
		button_timer_active = true;
	}
}

uint16_t button_get_counter(void)
{
	uint16_t temp_counter = button_counter;
	button_counter = 0;
	return temp_counter;
}

void TIM3_IRQHandler()
{
	TIM_ClearITPendingBit(BUTTON_TIMER, TIM_IT_Update);
	if(BUTTON_PORT->IDR & ( 1 << BUTTON))
	{
		button_counter++;
	}
}
