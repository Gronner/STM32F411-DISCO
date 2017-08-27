#include "led.h"
#include "timer.h"

void mcu_init(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	__asm("dsb");
}

 
int main(void)
{
	mcu_init();	
	led_init();	
	led_on(0);
	timer_init(TIM2);
	timer_start(TIM2);
	timer_enable_interrupt(TIM2, 0, 1);
	timer_init(TIM3);
	timer_start(TIM3);
	timer_enable_interrupt(TIM3, 0, 1);


    for (;;) {
		timer_wait(TIM2, 1);
		led_toggle(2);
    }
}
