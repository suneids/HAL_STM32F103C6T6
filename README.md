Selfwritten High Abstractive Layer for STM32F103C6T6
Instruction for using modules:
GPIO
Functions
| void enableGPIOClock(GPIO_TypeDef *port); | lorem |
| uint8_t gpioPortIndex(GPIO_TypeDef *port);| lorem |
| void pinMode(Pin_t pin, uint8_t mode, uint8_t cnf, uint8_t pull); |
| void pinModeMulti(Pin_t* pins, size_t pins_number, uint8_t mode, uint8_t cnf, uint8_t pull); |
| void digitalWrite(Pin_t pin, uint8_t value); |
| uint8_t digitalRead(Pin_t pin); |
| void pinToggle(Pin_t pin); |

Firstly, use enableGPIOClock with GPIO which you need.
