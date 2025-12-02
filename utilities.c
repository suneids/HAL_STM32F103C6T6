#include "utilities.h"
#include "gpio.h"
void assert(uint8_t condition){
	if(!condition){
		assertFailed();
	}
}

void assertFailed(){
	__disable_irq();//отключить периферию, прерывания
	while(1){
		pinToggle(GPIO_PORT_C, ONBOARD_LED_PIN);
		for(volatile uint32_t i = 0; i < 500000; i++);
	}
}
