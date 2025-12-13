#include "utilities.h"
#include "gpio.h"
Pin_t led_pin = {GPIOC, ONBOARD_LED_PIN};
void assert(uint8_t condition){
	if(!condition){
		assertFailed();
	}
}

void assertFailed(){
	__disable_irq();//отключить периферию, прерывания

	while(1){
		pinToggle(led_pin);
		for(volatile uint32_t i = 0; i < 500000; i++);
	}
}
