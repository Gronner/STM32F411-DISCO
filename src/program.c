#include "stm32f4xx_tim.h"
#include "led.h"
#include "timer.h"
 

//Quick hack, approximately 1ms delay
void ms_delay(int ms)
{
   while (ms-- > 0) {
      volatile int x=5971;
      while (x-- > 0)
         __asm("nop");
   }
}

//Flash orange LED at about 1hz
int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  // enable the clock to GPIOD
    __asm("dsb");                         // stall instruction pipeline, until instruction completes, as
                                          //    per Errata 2.1.13, "Delay after an RCC peripheral clock enabling"
    // GPIOD->MODER = (1 << 28);             // set pin 13 to be general purpose output
	led_init();	
	led_on_all();
	ms_delay(500);
	led_off_all();
	ms_delay(500);
	timer_init();
	timer_start();

    for (;;) {
		timer_wait(1);
		led_toggle(2);
    }
}
