/*
 * Author:		Gronner@Github
 * Date:		2017-07-28
 * Description:	Library to interface with the on-board button of the STM32F411
 *				at pin PA0
 *
 */
#ifndef __BUTTON_H__
#define __BUTTON_H__

void button_init(void);
void button_get_counter(void);

#endif // __BUTTON_H__
