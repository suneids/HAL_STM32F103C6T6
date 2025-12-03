#ifndef GPIO_H
#define GPIO_H
#include "mcu_config.h"
#include <stddef.h>

#define GPIO_MODE_INPUT 0b00
#define GPIO_MODE_OUTPUT_10MHz 0b01
#define GPIO_MODE_OUTPUT_2MHz 0b10
#define GPIO_MODE_OUTPUT_50MHz 0b11

#define GPIO_CNF_ANALOG 0b00
#define GPIO_CNF_FLOATING 0b01
#define GPIO_CNF_INPUT_PU_PD 0b10


#define GPIO_CNF_PUSH_PULL 0b00
#define GPIO_CNF_OPEN_DRAIN 0b01
#define GPIO_CNF_PUSH_PULL_ALT 0b10
#define GPIO_CNF_OPEN_DRAIN_ALT 0b11

typedef struct Pin_t{
	GPIO_TypeDef *port;
	uint8_t number;
};


void enableGPIOClock(GPIO_TypeDef *port);
uint8_t gpioPortIndex(GPIO_TypeDef *port);
void pinMode(Pin_t pin, uint8_t mode, uint8_t cnf, uint8_t pull);
void pinModeMulti(Pin_t* pins, size_t pins_number, uint8_t mode, uint8_t cnf, uint8_t pull);
void digitalWrite(Pin_t pin, uint8_t value);
uint8_t digitalRead(Pin_t pin);
void pinToggle(Pin_t pin);

#endif
