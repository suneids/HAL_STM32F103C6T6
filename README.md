Selfwritten High Abstractive Layer for STM32F103C6T6
Instruction for using modules:
## GPIO
| Functions | Description |
| --------- | ----- |
| void enableGPIOClock(GPIO_TypeDef *port) | Enables clocking (RCC) for the specified port. It is necessary before any manipulation of pins. |
| uint8_t gpioPortIndex(GPIO_TypeDef *port) | Returns the integer index of the port [0-2]. It is used for internal addressing and offsets in data arrays. |
| void pinMode(Pin_t pin, uint8_t mode, uint8_t cnf, uint8_t pull) | Configures one pin. Adjusts the MODE and CNF bits in the CRL/CRH registers, including Pull-up/down control. |
| void pinModeMulti(Pin_t* pins, size_t pins_number, uint8_t mode, uint8_t cnf, uint8_t pull) | Group initialization of an array of pins with the same parameters. Optimizes the code when configuring data buses |
| void digitalWrite(Pin_t pin, uint8_t value) | Sets the output status (High/Low). Uses the BSRR register to atomically change the state of a bit. |
| uint8_t digitalRead(Pin_t pin) | Returns the current logical state of the pin by reading the value from the input data register (IDR). |
| void pinToggle(Pin_t pin) | Inverts the current state of the output pin. It is convenient for debugging and display (Heartbeat LED). |

## How to use
Firstly, use enableGPIOClock with GPIO which you need.

## USART
| Functions | Description |
| --------- | ----- |
| void echo(USART_TypeDef *USARTx) | A debug utility that immediately retransmits received data back to the sender. Useful for link testing. |
| void usartInit(USART_TypeDef *USARTx, uint32_t baud_rate) | High-level initializer. Configures baud rate, parity, and stop bits, then enables the USART peripheral. | 
| uint16_t usartAvailable(USART_TypeDef *USARTx) | Returns the number of bytes currently waiting in the receive buffer. Essential for non-blocking reads. |
| void usartWriteByte(USART_TypeDef *USARTx, char byte) | Transmits a single 8-bit character. Waits for the TXE flag to ensure the register is ready. |
| void usartWriteLine(USART_TypeDef *USARTx, const char *str) | Transmits a null-terminated string followed by line ending characters (CR/LF). |
| char usartReadByte(USART_TypeDef *USARTx) | Reads a single byte from the DR register. Blocks until the RXNE flag is set. |
| void usartReadBytes(USART_TypeDef *USARTx, char *buf, uint32_t max_len) | Reads a stream of data into a buffer until max_len is reached or a timeout occurs. |
| void USART_IRQHandler_Generic(USART_TypeDef *USARTx) | A centralized interrupt handler that manages RX/TX events for any given USART instance |
| uint32_t usartDiv(uint32_t F_CPU, uint32_t baud_rate) | Internal helper. Calculates the required USARTDIV value based on $f_{CPU}$ and target baud rate. |
| uint8_t usartIndex(USART_TypeDef *USARTx) | Returns the hardware instance index (0 for USART1, etc.). Used for peripheral mapping and offsets. |

## How to use

## TIM
| Functions | Description |
| --------- | ----- |
| void sysTickInit(void) | Configures the system tick timer to generate interrupts every 1ms. Essential for time-base management. |
| uint32_t millis(void) | Returns the number of milliseconds elapsed since the program started. Used for non-blocking delays and timing. |
| void timerInit(TIM_TypeDef *TIMx, uint32_t psc, uint32_t arr, uint8_t debounce) | General-purpose timer initializer. Sets Prescaler (PSC) and Auto-Reload (ARR) values, with optional debounce filtering. |
| void sysTickDelay(uint32_t ms) | Implements a blocking delay in milliseconds using the SysTick counter. Accurate but halts main execution. |
| void timRegisterHandler(TIM_TypeDef *TIMx, TimHandler_t handler) | Attaches a callback function (handler) to a specific timer instance. Enables modular interrupt processing. |

## How to use


## SOFT UART
| Functions | Description |
| --------- | ----- |
| uint16_t softUartAvailable(void) | Returns the number of received bytes currently stored in the software buffer. Non-blocking check. |
| char softUartReadByte(void) | Retrieves one byte from the software receive buffer. |
| void softUartPutChar(char data) | Transmits a single character by manually toggling (bit-banging) the TX pin with precise timing. |
| void softUartPutString(const char *data) | Sends a null-terminated string using the bit-banging transmission method. |
| void softUartInit(Pin_t rx, Pin_t tx, uint32_t baud_rate) | Configures GPIO pins for RX/TX and sets up a timer to generate bit-interval interrupts for the specified baud rate. |

## How to use


## SOFT I2C
| Functions | Description |
| --------- | ----- |
| void SoftI2C_Start(Pin_t sda, Pin_t scl) | Generates a START condition by pulling the SDA line low while SCL is high. Signals the beginning of a data transfer. |
| void SoftI2C_Stop(Pin_t sda, Pin_t scl) | Generates a STOP condition by releasing the SDA line to high while SCL is high. Ends the current bus session. |
| uint8_t SoftI2C_Write(Pin_t sda, Pin_t scl, uint8_t byte) | Transmits an 8-bit byte to the bus bit-by-bit. Returns the ACK/NACK bit received from the slave device. |
| uint8_t SoftI2C_Read(Pin_t sda, Pin_t scl, uint8_t ack) | Receives an 8-bit byte from the slave and sends an ACK or NACK bit to control the data flow. |

## How to use


## PWM
| Functions | Description |
| --------- | ----- |
| void pwmInit(Pin_t pin) | Configures the GPIO pin for Alternate Function and initializes the corresponding Timer channel in PWM mode. |
| void pwmWrite(Pin_t pin, uint16_t value) | Updates the Capture/Compare Register (CCR) to set the pulse width, effectively controlling motor speed or LED brightness. |
| TimerChannel_t getTIMChannel(Pin_t pin) | Internal helper. Maps a specific GPIO pin to its hardware Timer channel based on the STM32 pinout. |

## How to use


## I2C
| Functions | Description |
| --------- | ----- |
| void I2C_Init(I2C_TypeDef *I2Cx, Pin_t SDA, Pin_t SCL) | Sets up the hardware I2C peripheral, including clock speed and GPIO pins configuration (SDA/SCL). |
| void I2C_Start(I2C_TypeDef *I2Cx) | Generates a START condition on the bus. Manages the SB (Start Bit) flag in the Status Register. |
| void I2C_WriteReg(I2C_TypeDef *I2Cx, uint8_t devAddr, uint8_t regAddr, uint8_t data) | Writes a single byte to a specific register of a slave device. Handles addressing and data transmission. |
| void I2C_WriteByteArray(I2C_TypeDef *I2Cx, uint8_t devAddr, uint8_t regAddr, uint8_t *pData, uint16_t len) | Transmits multiple bytes to a slave device. Efficient for loading configuration tables or large data sets. |
| uint8_t I2C_ReadReg(I2C_TypeDef *I2Cx, uint8_t devAddr, uint8_t regAddr) | Reads a single byte from a target register. Manages the transition between Write (addressing) and Read modes. |
| void I2C_Read_Burst(I2C_TypeDef *I2Cx, uint8_t devAddr, uint8_t regAddr, uint8_t *pBuffer, uint16_t size) | High-performance sequential read. Reads multiple bytes in a single transaction, essential for IMU sensor data. |

## How to use


## EXTI
| Functions | Description |
| --------- | ----- |
| void extiRegisterHandler(Pin_t pin, ExtiHandler_t handler) | Configures the external interrupt line for a specific pin and selects the trigger edge (Rising/Falling/Both). |
| void extiInit(Pin_t pin, ExtiEdge) | Registers a callback function to be executed when the interrupt occurs on the specified pin. |
| void extiClearFlag(Pin_t pin) | Clears the Pending Register (PR) bit to acknowledge the interrupt and allow future triggers. |
| void EXTIx_User_Handler(void) | Weak interrupt handlers. Can be overridden in user code to implement custom logic without modifying the library. |


## How to use


## DMA
| Functions | Description |
| --------- | ----- |
| void DMAInit(DMA_Channel_TypeDef *DMAx, uint32_t peripheral_addr, uint32_t memory_addr, uint16_t data_count) | Configures the Direct Memory Access channel to transfer data between a peripheral and memory without CPU intervention. |

## How to use


## ADC
| Functions | Description |
| --------- | ----- |
| void ADCInitMulti(Pin_t *pins, uint16_t count, uint8_t need_dma) | Initializes multiple ADC channels for a given array of pins. Includes optional DMA support for autonomous data collection from multiple sensors. |
## How to use

