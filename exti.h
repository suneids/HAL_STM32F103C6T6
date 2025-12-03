#ifndef EXTI_C
#define EXTI_H
#include "gpio.h"

typedef enum{
	EXTI_RISING_EDGE,
	EXTI_FALLING_EDGE,
	EXTI_BOTH_EDGES
} ExtiEdge;

void extiInit(Pin_t pin, ExtiEdge);
void extiClearFlag(Pin_t pin);

#endif
