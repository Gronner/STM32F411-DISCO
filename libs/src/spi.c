#include "bsp.h"
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "led.h"

#define GPIO_ALT_FUNC_SPI 101 // -> AF5
#define SPI_CLK_DIV_16 11 // -> /16

void spi_init(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	__asm("dsb");
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	__asm("dsb");
	RCC->APB2ENR |= RCC_APB2Periph_SPI1;
	__asm("dsb");

	SPI1->CR1 &= ~(SPI_CR1_SPE);  // SPI Disable 
		
	L3GD20_NSS_PORT->MODER |= (1 << (L3GD20_NSS * 2));
	L3GD20_NSS_PORT->ODR |= (1 << L3GD20_NSS);

	// Active Alternative Function Mode
	L3GD20_SPI_PORT->MODER |= (uint32_t) (((uint32_t)10 << (L3GD20_SCK * 2))
							+ ((uint32_t)10 << (L3GD20_MOSI * 2))
							+ ((uint32_t)10 << (L3GD20_MISO * 2)));
	
	// Set Ports to High Speed Mode
	L3GD20_SPI_PORT->OSPEEDR |= (11 << (L3GD20_SCK * 2))
							+ (11 << (L3GD20_MOSI * 2))
							+ (11 << (L3GD20_MISO * 2));


	L3GD20_SPI_PORT->AFR[0] |= (uint32_t) ((uint32_t)GPIO_ALT_FUNC_SPI << (L3GD20_SCK * 4))
							+ (uint32_t) ((uint32_t)GPIO_ALT_FUNC_SPI << (L3GD20_MOSI  * 4))
							+ (uint32_t) ((uint32_t)GPIO_ALT_FUNC_SPI << (L3GD20_MISO * 4));


	SPI1->CR1 |= (uint32_t)SPI_CR1_SPE;  // SPI Enable

	SPI1->CR1 |= (uint32_t)((uint32_t)1 << 11)  // Set 16-bit mode
				+ ((uint32_t)1 << 2)  // Master Mode
				+ ((uint32_t)1 << 1); // CPOL = 1
	SPI1->CR1 &= (uint32_t) 1; // CPHA = 0

	SPI1->I2SCFGR &= (uint16_t) ~ ((uint16_t) 1 << 11);
}

void spi_transmit(uint16_t doublebyte)
{
	L3GD20_NSS_PORT->ODR &= (1 << L3GD20_NSS);

	SPI1->DR = doublebyte;

	while(SPI1->SR && (1 << 1)); // Wait for transmission complete
	while(SPI1->SR && (1 << 7)); // Wait for BUS to be not busy

	L3GD20_NSS_PORT->ODR |= (1 << L3GD20_NSS);

}

void spi_receive(void)
{
	return;
}
