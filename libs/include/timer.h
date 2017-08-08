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
#include "stm32f4xx_tim.h"

void timer_init(TIM_TypeDef* TIMx);
void timer_start(TIM_TypeDef* TIMx);
void timer_enable_interrupt(TIM_TypeDef* TIMx, uint8_t pre_priority, uint8_t sub_priority);
void timer_stop(TIM_TypeDef* TIMx);
void timer_set_prediv(TIM_TypeDef* TIMx, uint16_t prediv);
void timer_set_ccrvalue(TIM_TypeDef* TIMx, uint32_t ccrvalue);
uint32_t timer_get_counter(TIM_TypeDef* TIMx);
bool timer_wait(TIM_TypeDef* TIMx, uint8_t periods);

#endif // __TIMER_H_

