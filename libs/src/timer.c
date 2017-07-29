#include "timer.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include "led.h"

static volatile uint32_t clock_counter = 0;
static volatile TIM_TimeBaseInitTypeDef timerInitStructure;

static void timer_enable_interrutpt(void)
{
	NVIC_InitTypeDef nvicStructure;
	nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
	nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStructure.NVIC_IRQChannelSubPriority = 1;
	nvicStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&nvicStructure);
}

void timer_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = 40000;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 500;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2, &timerInitStructure);
}

void timer_start(void)
{
	TIM_Cmd(TIM2, ENABLE);
	timer_enable_interrutpt();
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void timer_stop(void)
{
	TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
	TIM_Cmd(TIM2, DISABLE);
}

void timer_set_prediv(uint16_t prediv)
{
	timerInitStructure.TIM_Prescaler = prediv;
}

void timer_set_ccrvalue(uint32_t ccrvalue)
{
	timerInitStructure.TIM_Period = ccrvalue;
}

uint32_t timer_get_counter(void)
{
	return clock_counter;
}

bool timer_wait(uint8_t periods)
{
	uint16_t time_start = 0;
	uint16_t time_end = 0;
	time_start = timer_get_counter();
	time_end = time_start + periods;
	while(time_end >= timer_get_counter());
	return true;
}

void TIM2_IRQHandler()
{
	led_toggle(1);
}

