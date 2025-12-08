#ifndef TIM_H
#define TIM_H
#include "mcu_config.h"
extern volatile uint32_t msTicks;

typedef void(*TimHandler_t)(void);


void sysTickInit(void);
uint32_t millis(void);
void timerInit(TIM_TypeDef *TIMx, uint32_t psc, uint32_t arr, uint8_t debounce);


void timRegisterHandler(TIM_TypeDef *TIMx, TimHandler_t handler);

#endif
