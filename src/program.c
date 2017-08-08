#include "led.h"
#include "timer.h"
 
int main(void)
{
	led_init();	
	timer_init(TIM2);
	timer_start(TIM2);
	timer_enable_interrupt(TIM2, 0, 1);

    for (;;) {
		timer_wait(TIM2, 1);
		led_toggle(2);
    }
}
