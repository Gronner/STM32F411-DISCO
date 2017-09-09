#include "bsp.h"
#include "button.h"
#include "led.h"
#include "misc.h"

static volatile uint16_t button_counter = 0;

void button_init(void)
{
	BUTTON_PORT->MODER &= ~(11 << BUTTON * 2);
	BUTTON_PORT->OSPEEDR |= (1 << BUTTON * 2);
	SYSCFG->EXTICR[1] &= ~(1111);
	EXTI->IMR |= (1 << BUTTON);
	EXTI->RTSR |= (1 << BUTTON);
	
	uint32_t priority = NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 1 ); 
	NVIC_SetPriority(EXTI0_IRQn, priority);
	NVIC_EnableIRQ(EXTI0_IRQn);
}

uint16_t button_get_counter(void)
{
	uint16_t temp_counter = button_counter;
	button_counter = 0;
	return temp_counter;
}

void EXTI0_IRQHandler(void)
{
	uint16_t i;
	for(i = 0;i < 11942; i++); // ~2ms debouncing
	EXTI->PR |= (1 << BUTTON);
	button_counter++;
}

