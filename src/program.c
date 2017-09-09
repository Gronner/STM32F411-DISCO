#include "stm32f4xx_rcc.h"
#include "led.h"
#include "button.h"

void mcu_init(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	__asm("dsb");
	RCC->APB2ENR |= (1 << 14);
	__asm("dsb");
}

 
int main(void)
{
	mcu_init();	
	led_init();	
	led_on(0);
	button_init();


    for (;;) {
		__asm("nop");
    }
}
