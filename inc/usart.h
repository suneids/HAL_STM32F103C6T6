#ifndef USART_H
#define USART_H
#include <stdint.h>
#include "mcu_config.h"
#include "gpio.h"
#define USART_BUFFER_SIZE 257
#define USART_BUFFER_MASK (USART_BUFFER_SIZE - 1)

extern volatile uint16_t rx_heads[2], tx_heads[2];
extern volatile uint16_t rx_tails[2], tx_tails[2];
extern volatile char usartRXBuffers[2][USART_BUFFER_SIZE], usartTXBuffers[2][USART_BUFFER_SIZE];

void echo(USART_TypeDef *USARTx);
void usartInit(USART_TypeDef *USARTx, uint32_t baud_rate);
uint16_t usartAvailable(USART_TypeDef *USARTx);
void usartWriteByte(USART_TypeDef *USARTx, char byte);
void usartWriteLine(USART_TypeDef *USARTx, const char *str, uint16_t len);

char usartReadByte(USART_TypeDef *USARTx);
void usartReadBytes(USART_TypeDef *USARTx, char *buf, uint32_t max_len);

void USART_IRQHandler_Generic(USART_TypeDef *USARTx);


uint32_t usartDiv(uint32_t F_CPU, uint32_t baud_rate);
uint8_t usartIndex(USART_TypeDef *USARTx);
#endif
