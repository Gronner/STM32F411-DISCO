/*
 * Author:		Gronner@Github
 * Date:		2017-07-28
 * Description:	Library to manage the different Timers of the STM32F411VET6
 *
 *
 *
 */
#ifndef __TIMER_H_
#define __TIMER_H_

#include <stdint.h>
#include <stdbool.h>

void timer_init(void);
void timer_start(void);
void timer_stop(void);
void timer_set_prediv(uint16_t prediv);
void timer_set_ccrvalue(uint32_t ccrvalue);
uint32_t timer_get_counter(void);
bool timer_wait(uint8_t periods);

#endif // __TIMER_H_

