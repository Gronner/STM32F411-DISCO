#include "bsp.h"

void spi_init(void)
{
	L3GD20_NSS_PORT->MODER |= (1 << (L3GD20_NSS * 2));
	L3GD20_NSS_PORT->ODR |= (1 << L3GD20_NSS);

}

void spi_transmit(uint8_t byte)
{

}

void spi_receive(void)
{

}
