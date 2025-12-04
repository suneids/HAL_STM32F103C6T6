#ifndef PWM_H
#define PWM_H
#include "mcu_config.h"
#include "tim.h"
#include "gpio.h"

typedef struct {
    TIM_TypeDef *TIMx;
    uint8_t channel;
}TimerChannel_t;

typedef struct{
    Pin_t pin;
    TIM_TypeDef *TIMx,
    uint8_t channel;
}PinMap_t;

PinMap_t map[12] = {
    {{GPIOA, 8}, TIM1, 1},
    {{GPIOA, 9}, TIM1, 2},
    {{GPIOA, 10}, TIM1, 3},
    {{GPIOA, 11}, TIM1, 4},
    
    {{GPIOA, 0}, TIM2, 1},
    {{GPIOA, 1}, TIM2, 2},
    {{GPIOA, 2}, TIM2, 3},
    {{GPIOA, 3}, TIM2, 4},
    
    {{GPIOC, 6}, TIM3, 1},
    {{GPIOC, 7}, TIM3, 2},
    {{GPIOC, 8}, TIM3, 3},
    {{GPIOC, 9}, TIM3, 4},
};

extern const uint32_t CCMR_OCxM[4];
extern const uint32_t CCMR_OCxPos[4];
extern const uint32_t CCMR_OCxPE[4];
extern const uint32_t CCER_CCxE[4];

void pwmInit(Pin_t pin);
void pwmWrite(Pin_t pin, uint16_t value);

TimerChannel_t getTIMChannel(Pin_t pin);
#endif
