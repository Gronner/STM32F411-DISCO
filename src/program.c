#include "stm32f4xx_rcc.h"
#include "led.h"
#include "button.h"

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
	button_init();

	uint16_t temp_button_counter = 0;
    for (;;) {
		if(button_get_counter() > temp_button_counter)
		{
			led_toggle(2);
			temp_button_counter = 0;
		}
		__asm("nop");
    }
}
