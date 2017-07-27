#define USE_STDPERIPH_DRIVER
#include "stm32f4xx.h"
#include "led.h"
 

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
	uint8_t i;
	for(i = 0; i < 4; i++)
	{
		led_on(i);
	}
	uint8_t j = 0;
    for (;;) {
       ms_delay(500);
       // GPIOD->ODR ^= (1 << 14);           // Toggle the pin 
	   led_toggle(j);
	   j++;
	   if(j > 3)
	   {
		   j = 0;
	   }
    }
}
