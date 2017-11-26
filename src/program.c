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
	
    uint8_t byte;
    

    GPIOE->BSRRH |= GPIO_Pin_3;
    for (;;) {
        byte = 0x20;
        spi_transmit(byte);
        byte = 0x0F;
        spi_transmit(byte);
    }
    GPIOE->BSRRL |= GPIO_Pin_3;
}
