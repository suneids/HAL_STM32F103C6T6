#include "exti.h"
void extiInit(Pin_t pin, ExtiEdge edge){
	GPIO_TypeDef *GPIOx = pin.port;
	uint8_t pin_number = pin.number;

	pinMode(pin, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PU_PD, 1);
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	uint8_t index = pin_number/4;
	uint8_t offset = (pin_number%4)*4;
	AFIO->EXTICR[index] &= ~(0xF << offset);
	AFIO->EXTICR[index] |= (gpioPortIndex(GPIOx) << offset);

	EXTI->IMR |= (1 << pin_number);
	if(edge == EXTI_RISING_EDGE){
		EXTI->RTSR |= (1 << pin_number);
	}
	else if(edge == EXTI_FALLING_EDGE){
		EXTI->FTSR |= (1 << pin_number);
	}
	else if(edge == EXTI_BOTH_EDGES){
		EXTI->RTSR |= (1 << pin_number);
		EXTI->FTSR |= (1 << pin_number);
	}

	if(pin_number <= 4){
		NVIC_EnableIRQ(EXTI0_IRQn + pin_number);
	}
	else if(pin_number <= 9){
		NVIC_EnableIRQ(EXTI9_5_IRQn);
	}
	else{
		NVIC_EnableIRQ(EXTI15_10_IRQn);
	}
}


void extiClearFlag(Pin_t pin){
	uint8_t pin_number = pin.number;
	EXTI->PR |= (1 << pin_number);
}
