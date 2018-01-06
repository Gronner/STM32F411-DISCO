#include "bsp.h"
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "led.h"

#define GPIO_ALT_FUNC_SPI 0b101 // -> AF5
#define SPI_CLK_DIV_16 0b11 // -> /16

void spi_init(void)
{ 
    /*
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; 
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2Periph_SPI1;
    */
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    // Set GPIO-Pins
    // Set NSS Pin to output mode 
    L3GD20_NSS_PORT->MODER |= (uint32_t) ((uint32_t) 1 << (L3GD20_NSS * 2));
    // Set NSS Pin to Pull-up
    L3GD20_NSS_PORT->PUPDR |= (uint32_t) ((uint32_t) 1 << (L3GD20_NSS * 2));
    // Set NSS Pin to High ( = unselected for SPI)
    L3GD20_NSS_PORT->ODR |= (uint32_t) ((uint32_t) 1 << L3GD20_NSS);

    // Set MOSI, MISO and SCK to Alternative Function Mode
    L3GD20_SPI_PORT->MODER |= (uint32_t) (((uint32_t) 0b10 << (L3GD20_SCK * 2))
                              + ((uint32_t) 0b10 << (L3GD20_MOSI * 2))
                              + ((uint32_t) 0b10 << (L3GD20_MISO * 2)));
    // Set MOSI, MISO and SCK to High Speed Mode
    L3GD20_SPI_PORT->OSPEEDR |= (uint32_t) (((uint32_t) 0b11 << (L3GD20_SCK * 2))
                              + ((uint32_t) 0b11 << (L3GD20_MOSI * 2))
                              + ((uint32_t) 0b11 << (L3GD20_MISO * 2)));
    // Set MOSI, MISO and SCK to SPI Mode
    L3GD20_SPI_PORT->AFR[0] |= (uint32_t) (((uint32_t) GPIO_ALT_FUNC_SPI << (L3GD20_SCK * 4))
                             + ((uint32_t) GPIO_ALT_FUNC_SPI << (L3GD20_MOSI * 2))
                             + ((uint32_t) GPIO_ALT_FUNC_SPI << (L3GD20_MISO * 2)));
    // Configure SPI according to L3GD20 needs
    SPI1->CR1 &= (uint16_t) ~((uint16_t) 1 << 6); // Disable SPI
    SPI1->CR1 |= (uint16_t) (((uint16_t) 1 << 11)  // Set 16-bit mode 
                 + ((uint16_t) 1 << 9)            // Set Software NSS to High
                 + ((uint16_t) 1 << 8)            // Set Software NSS
                 + ((uint16_t) 1 << 3)           // Set clock div to 1/4 
                 + ((uint16_t) 1 << 2)            // Master mode 
                 + ((uint16_t) 1 << 1)            // CK to 1 when idle
                 + ((uint16_t) 1));               // Use 2nd Clock Edge
    SPI1->I2SCFGR &= (uint16_t) ~((uint16_t) SPI_I2SCFGR_I2SMOD);
    // SPI Enable
    SPI1->CR1 |= (uint16_t) 1 << 6;
}

uint16_t spi_transmit(uint16_t doublebyte)
{
    GPIOE->ODR &= ~(GPIO_Pin_3);
	SPI1->DR = doublebyte;
    while(!(SPI1->SR & SPI_I2S_FLAG_TXE));
    while(!(SPI1->SR & SPI_I2S_FLAG_RXNE));
    while(SPI1->SR & SPI_I2S_FLAG_BSY);
    GPIOE->ODR |= GPIO_Pin_3;
    return SPI1->DR;
}

void spi_receive(void)
{
	return;
}
