#include "stm32f4xx_rcc.h"
#include "led.h"
#include "spi.h"

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
	
	spi_init();
	
    uint16_t doublebyte, result;
    doublebyte = 0x000F;
    
    for (;;) 
    {
        result = spi_transmit(doublebyte);
        if(result == 0b11010100)
        {
            led_on(1);
        }
    }
}
