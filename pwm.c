#include "pwm.h"
const uint32_t CCMR_OCxM[4] = { TIM_CCMR1_OC1M, TIM_CCMR1_OC2M,
						 TIM_CCMR2_OC3M, TIM_CCMR2_OC4M };
const uint32_t CCMR_OCxPos[4] = { TIM_CCMR1_OC1M_Pos, TIM_CCMR1_OC2M_Pos,
							TIM_CCMR2_OC3M_Pos, TIM_CCMR2_OC4M_Pos };
const uint32_t CCMR_OCxPE[4] = {TIM_CCMR1_OC1PE, TIM_CCMR1_OC2PE,
						  TIM_CCMR2_OC3PE, TIM_CCMR2_OC4PE};
const uint32_t CCER_CCxE[4] = {TIM_CCER_CC1E, TIM_CCER_CC2E,
						 TIM_CCER_CC3E, TIM_CCER_CC4E };

void pwmInit(Pin_t pin){
	TimerChannel_t pin_metadata = getTIMChannel(pin); 
	TIM_TypeDef *TIMx = pin_metadata.TIMx;
	uint8_t channel = pin_metadata.channel;
	if((channel < 1) || (channel > 4)){
		//TODO assert error
	}
	__IO uint32_t *CCMRx = channel <= 2? &TIMx->CCMR1 : &TIMx->CCMR2;
	channel -= 1;
	*CCMRx &= ~(CCMR_OCxM[channel]);
	*CCMRx |= (6 << CCMR_OCxPos[channel]);
	*CCMRx |= (CCMR_OCxPE[channel]);
	TIMx->CCER |= (CCER_CCxE[channel]);
}


void pwmWrite(Pin_t pin, uint16_t value){
	TimerChannel_t pin_metadata = getTIMChannel(pin); 
	TIM_TypeDef *TIMx = pin_metadata.TIMx;
	uint8_t channel = pin_metadata.channel;
	__IO uint16_t *CCRs[4] = {&TIMx->CCR1, &TIMx->CCR2, &TIMx->CCR3, &TIMx->CCR4};
	if((channel > 0) && (channel < 5) && (value <= TIMx->ARR)){
		*CCRs[channel - 1] = value;
	}
}

TimerChannel_t getTIMChannel(Pin_t pin){
	TimerChannel_t result = {NULL, 0};
	for(int i = 0; i < 12; i++){
		if((map[i].pin.port == pin.port) && ( map[i].pin.number == pin.number)){
			result.TIMx = map[i].TIMx; 
			result.channel = map[i].channel;
			return result;
		}
	}

	return result;
}