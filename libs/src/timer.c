#include <stdbool.h>
#include "timer.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include "led.h"
#include "bsp.h"

static volatile uint32_t clock_counter[8] = {0, 0, 0, 0, 0, 0, 0, 0};

static bool timer_is_valid(TIM_TypeDef* TIMx)
{
	switch((uintptr_t) TIMx)
	{
		case (uintptr_t) TIM1:
		case (uintptr_t) TIM2:
		case (uintptr_t) TIM3:
		case (uintptr_t) TIM4:
		case (uintptr_t) TIM5:
		case (uintptr_t) TIM9:
		case (uintptr_t) TIM10:
		case (uintptr_t) TIM11:
			return true;
		default:
			return false;
	}
}

static uint8_t get_irq_channel(TIM_TypeDef* TIMx)
{
	switch((uintptr_t) TIMx)
	{
		case (uintptr_t) TIM1:
			return TIM1_CC_IRQn;
		case (uintptr_t) TIM2:
			return TIM2_IRQn;
		case (uintptr_t) TIM3:
			return TIM3_IRQn;
		case (uintptr_t) TIM4:
			return TIM4_IRQn;
		case (uintptr_t) TIM5:
			return TIM5_IRQn;
		case (uintptr_t) TIM9:
			return TIM1_BRK_TIM9_IRQn;
		case (uintptr_t) TIM10:
			return TIM1_UP_TIM10_IRQn;
		case (uintptr_t) TIM11:
			return TIM1_TRG_COM_TIM11_IRQn;
		default:
			return UINT8_MAX;
	}
}

void timer_enable_interrupt(TIM_TypeDef* TIMx, uint8_t pre_priority, uint8_t sub_priority)
{
	if(timer_is_valid(TIMx) == false)	
	{
		return;
	}

	uint8_t irq_channel = 0;

	irq_channel = get_irq_channel(TIMx);

	if(irq_channel == UINT8_MAX)
	{
		return;
	}

	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);

	NVIC_InitTypeDef nvicStructure;
	nvicStructure.NVIC_IRQChannel = irq_channel;
	nvicStructure.NVIC_IRQChannelPreemptionPriority = pre_priority;
	nvicStructure.NVIC_IRQChannelSubPriority = sub_priority;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);
}

static uint32_t get_rcc_periph(TIMx)
{
	switch((uintptr_t) TIMx)
	{
		case (uintptr_t) TIM1:
			return RCC_APB2Periph_TIM1;
		case (uintptr_t) TIM2:
			return RCC_APB1Periph_TIM2;
		case (uintptr_t) TIM3:
			return RCC_APB1Periph_TIM3;
		case (uintptr_t) TIM4:
			return RCC_APB1Periph_TIM4;
		case (uintptr_t) TIM5:
			return RCC_APB1Periph_TIM5;
		case (uintptr_t) TIM9:
			return RCC_APB2Periph_TIM9;
		case (uintptr_t) TIM10:
			return RCC_APB2Periph_TIM10;
		case (uintptr_t) TIM11:
			return RCC_APB2Periph_TIM11;
		default:
			return UINT32_MAX;
	}
}

typedef void (*rcc_func_t)(uint32_t, FunctionalState);

static rcc_func_t get_rcc_cmd_function(TIM_TypeDef* TIMx)
{
	switch((uintptr_t) TIMx)
	{
		case (uintptr_t) TIM1:
		case (uintptr_t) TIM9:
		case (uintptr_t) TIM10:
		case (uintptr_t) TIM11:
			return RCC_APB2PeriphClockCmd;
		case (uintptr_t) TIM2:
		case (uintptr_t) TIM3:
		case (uintptr_t) TIM4:
		case (uintptr_t) TIM5:
			return RCC_APB1PeriphClockCmd;
		default:
			return NULL;
	}
}

void timer_init(TIM_TypeDef* TIMx)
{
	if(timer_is_valid(TIMx) == false)
	{
		return;
	}

	rcc_func_t rcc_function = NULL;
	rcc_function = get_rcc_cmd_function(TIMx);
	if(rcc_function == NULL)
	{
		return;
	}

	uint32_t rcc_periph = UINT32_MAX;
	rcc_periph = get_rcc_periph(TIMx);
	if(rcc_periph == UINT32_MAX)
	{
		return;
	}

	rcc_function(rcc_periph, ENABLE);

	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = 40000;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 500;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIMx, &timerInitStructure);
}

void timer_start(TIM_TypeDef* TIMx)
{
	if(timer_is_valid(TIMx) == false)
	{
		return;
	}

	TIM_Cmd(TIMx, ENABLE);
}

void timer_stop(TIM_TypeDef* TIMx)
{
	if(timer_is_valid(TIMx) == false)
	{
		return;
	}

	TIM_ITConfig(TIMx, TIM_IT_Update, DISABLE);
	TIM_Cmd(TIMx, DISABLE);
}

void timer_set_prediv(TIM_TypeDef* TIMx, uint16_t prediv)
{
	if(timer_is_valid(TIMx) == false)
	{
		return;
	}

	TIM_PrescalerConfig(TIMx, prediv, TIM_PSCReloadMode_Immediate);
}

void timer_set_ccrvalue(TIM_TypeDef* TIMx, uint32_t ccrvalue)
{
	if(timer_is_valid(TIMx) == false)
	{
		return;
	}

	TIM_SetAutoreload(TIMx, ccrvalue);
	TIMx->EGR = TIM_PSCReloadMode_Immediate;
}


uint32_t timer_get_counter(TIM_TypeDef* TIMx)
{
	if(timer_is_valid(TIMx) == false)
	{
		return 0;
	}
	
	uint8_t counter_id = 9;

	switch((uintptr_t) TIMx)
	{
		case (uintptr_t) TIM1:
			counter_id = 0;
			break;
		case (uintptr_t) TIM2:
			counter_id = 1;
			break;
		case (uintptr_t) TIM3:
			counter_id = 2;
			break;
		case (uintptr_t) TIM4:
			counter_id = 3;
			break;
		case (uintptr_t) TIM5:
			counter_id = 4;
			break;
		case (uintptr_t) TIM9:
			counter_id = 5;
			break;
		case (uintptr_t) TIM10:
			counter_id = 6;
			break;
		case (uintptr_t) TIM11:
			counter_id = 7;
			break;
		default:
			counter_id = 9;
	}
	if(counter_id > 7)
	{
		return 0;
	}

	return clock_counter[counter_id];
}

bool timer_wait(TIM_TypeDef* TIMx, uint8_t periods)
{
	uint16_t time_start = 0;
	uint16_t time_end = 0;
	time_start = timer_get_counter(TIMx);
	time_end = time_start + periods;
	while(time_end >= timer_get_counter(TIMx));
	return true;
}

void TIM2_IRQHandler()
{
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	clock_counter[1]++;
}

void TIM3_IRQHandler()
{
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	led_toggle(1);
}
