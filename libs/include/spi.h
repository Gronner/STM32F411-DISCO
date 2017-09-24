/*
 * Author:		Gronner@Github
 * Date:		2017-09-25
 * Description:	Library to interface with interface the SPI-Modules
 *
 *
 */
#ifndef __SPI_H__
#define __SPI_H__

void spi_init(void);
void spi_transmit(uint8_t byte);
uint8_t spi_receive(void);

#endif // __SPI_H__

