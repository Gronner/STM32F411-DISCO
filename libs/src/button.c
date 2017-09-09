#include "bsp.h"
#include "button.h"
#include "led.h"
#include "misc.h"

static uint16_t button_counter = 0;

void button_init(void)
{
	BUTTON_PORT->MODER &= ~(11 << BUTTON * 2);
	BUTTON_PORT->OSPEEDR |= (11 << BUTTON * 2);
	SYSCFG->EXTICR[1] &= ~(1111);
	EXTI->IMR |= (1 << BUTTON);
	EXTI->RTSR |= (1 << BUTTON);
	
	uint32_t priority = NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 1 ); 
	NVIC_SetPriority(EXTI0_IRQn, priority);
	NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler(void)
{
	EXTI->PR |= (1 << BUTTON);
	led_toggle(1);
}

