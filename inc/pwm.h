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
    TIM_TypeDef *TIMx;
    uint8_t channel;
}PinMap_t;


extern const uint32_t CCMR_OCxM[4];
extern const uint32_t CCMR_OCxPos[4];
extern const uint32_t CCMR_OCxPE[4];
extern const uint32_t CCER_CCxE[4];

void pwmInit(Pin_t pin);
void pwmWrite(Pin_t pin, uint16_t value);

TimerChannel_t getTIMChannel(Pin_t pin);
#endif
