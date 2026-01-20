Selfwritten High Abstractive Layer for STM32F103C6T6
Instruction for using modules:
## GPIO
| Functions | Description |
| --------- | ----- |
| void enableGPIOClock(GPIO_TypeDef *port); | Enables clocking (RCC) for the specified port. It is necessary before any manipulation of pins. |
| uint8_t gpioPortIndex(GPIO_TypeDef *port); | Returns the integer index of the port [0-2]. It is used for internal addressing and offsets in data arrays. |
| void pinMode(Pin_t pin, uint8_t mode, uint8_t cnf, uint8_t pull); | Configures one pin. Adjusts the MODE and CNF bits in the CRL/CRH registers, including Pull-up/down control. |
| void pinModeMulti(Pin_t* pins, size_t pins_number, uint8_t mode, uint8_t cnf, uint8_t pull); | Group initialization of an array of pins with the same parameters. Optimizes the code when configuring data buses |
| void digitalWrite(Pin_t pin, uint8_t value); | Sets the output status (High/Low). Uses the BSRR register to atomically change the state of a bit. |
| uint8_t digitalRead(Pin_t pin); | Returns the current logical state of the pin by reading the value from the input data register (IDR). |
| void pinToggle(Pin_t pin); | Inverts the current state of the output pin. It is convenient for debugging and display (Heartbeat LED). |

## USART
| Functions | Description |
| --------- | ----- |
| void echo(USART_TypeDef *USARTx); | A debug utility that immediately retransmits received data back to the sender. Useful for link testing. |
| void usartInit(USART_TypeDef *USARTx, uint32_t baud_rate); | High-level initializer. Configures baud rate, parity, and stop bits, then enables the USART peripheral. | 
| uint16_t usartAvailable(USART_TypeDef *USARTx); | Returns the number of bytes currently waiting in the receive buffer. Essential for non-blocking reads. |
| void usartWriteByte(USART_TypeDef *USARTx, char byte); | Transmits a single 8-bit character. Waits for the TXE flag to ensure the register is ready. |
| void usartWriteLine(USART_TypeDef *USARTx, const char *str); | Transmits a null-terminated string followed by line ending characters (CR/LF). |
| char usartReadByte(USART_TypeDef *USARTx); | Reads a single byte from the DR register. Blocks until the RXNE flag is set. |
| void usartReadBytes(USART_TypeDef *USARTx, char *buf, uint32_t max_len); | Reads a stream of data into a buffer until max_len is reached or a timeout occurs. |
| void USART_IRQHandler_Generic(USART_TypeDef *USARTx); | A centralized interrupt handler that manages RX/TX events for any given USART instance |
| uint32_t usartDiv(uint32_t F_CPU, uint32_t baud_rate); | Internal helper. Calculates the required USARTDIV value based on $f_{CPU}$ and target baud rate. |
| uint8_t usartIndex(USART_TypeDef *USARTx); | Returns the hardware instance index (0 for USART1, etc.). Used for peripheral mapping and offsets. |


## TIM
| Functions | Description |
| --------- | ----- |

## SOFT UART
| Functions | Description |
| --------- | ----- |

## SOFT I2C
| Functions | Description |
| --------- | ----- |

## PWM
| Functions | Description |
| --------- | ----- |

## I2C
| Functions | Description |
| --------- | ----- |

## EXTI
| Functions | Description |
| --------- | ----- |

## DMA
| Functions | Description |
| --------- | ----- |

## ADC
| Functions | Description |
| --------- | ----- |

## How to use
Firstly, use enableGPIOClock with GPIO which you need.
