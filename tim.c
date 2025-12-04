#include "tim.h"
volatile uint32_t msTicks = 0;


void sysTickInit(void){
	SysTick_Config(SystemCoreClock / 1000);
}


uint32_t millis(void){
	return msTicks;
}


void SysTick_Handler(void){
	msTicks++;
}



void timerInit(TIM_TypeDef *TIMx, uint32_t psc, uint32_t arr, uint8_t debounce){
	if(TIMx == TIM1){
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
		if(debounce) NVIC_EnableIRQ(TIM1_IRQn);
	}
	else if(TIMx == TIM2){
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
		if(debounce) NVIC_EnableIRQ(TIM2_IRQn);
	}
	else if(TIMx == TIM3){
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		if(debounce) NVIC_EnableIRQ(TIM3_IRQn);
	}

	TIMx->PSC = psc;
	TIMx->ARR = arr;
	TIMx->CNT = 0;
	TIMx->DIER |= TIM_DIER_UIE;

	if(debounce){
		TIMx->CR1 &= ~TIM_CR1_CEN;
	}
	else{
		TIMx->CR1 |= TIM_CR1_ARPE;
		TIMx->EGR |= TIM_EGR_UG;
		TIMx->CR1 |= TIM_CR1_CEN;
	}
}

