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
uint16_t spi_transmit(uint16_t byte);
uint16_t spi_receive();

#endif // __SPI_H__

