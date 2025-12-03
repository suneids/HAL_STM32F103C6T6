#include <stdio.h>
#include "usart.h"
#include "gpio.h"

volatile uint16_t rx_heads[2] = { 0 }, tx_heads[2] = { 0 };
volatile uint16_t rx_tails[2] = { 0 }, tx_tails[2] = { 0 };
volatile char usartRXBuffers[2][USART_BUFFER_SIZE] = {{ 0 }}, usartTXBuffers[2][USART_BUFFER_SIZE] = {{ 0 }};

void usartInit(USART_TypeDef *USARTx, uint32_t  baud_rate){
	enableGPIOClock(GPIOA);
	if(USARTx == USART1){
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		Pin_t tx = {GPIOA, 9}, rx = {GPIOA, 10};
		pinMode(tx, GPIO_MODE_OUTPUT_50MHz, GPIO_CNF_PUSH_PULL_ALT, 0);
		pinMode(rx, GPIO_MODE_INPUT, GPIO_CNF_FLOATING, 0);
		NVIC_EnableIRQ(USART1_IRQn);	
	}
	else if(USARTx == USART2){
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		Pin_t tx = {GPIOA, 2}, rx = {GPIOA, 3};
		pinMode(tx, GPIO_MODE_OUTPUT_50MHz, GPIO_CNF_PUSH_PULL_ALT, 0);
		pinMode(rx, GPIO_MODE_INPUT, GPIO_CNF_FLOATING, 0);
		NVIC_EnableIRQ(USART2_IRQn);
	}

	USARTx->BRR = usartDiv(8000000, baud_rate);
	USARTx->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;

}

uint16_t usartAvailable(USART_TypeDef *USARTx){
	uint8_t port_id = usartIndex(USARTx);
	return (rx_heads[port_id] - rx_tails[port_id]) & USART_BUFFER_MASK;
}

void usartWriteByte(USART_TypeDef *USARTx, char byte){
	uint8_t port_id = usartIndex(USARTx);
	char *usartTXBuffer = usartTXBuffers[port_id];
	uint16_t next_head = (tx_heads[port_id] + 1) % USART_BUFFER_SIZE;
	if(next_head == tx_tails[port_id]){
		return;
	}
	usartTXBuffer[tx_heads[port_id]] = byte;
	tx_heads[port_id] = next_head;
	USARTx->CR1 |= USART_CR1_TXEIE;
}


void usartWriteLine(USART_TypeDef *USARTx, const char* str){
	uint8_t port_id = usartIndex(USARTx);
	char *usartTXBuffer = usartTXBuffers[port_id];
	while(*str != '\0'){
		uint16_t next_head = (tx_heads[port_id] + 1) % USART_BUFFER_SIZE;
		if(next_head == tx_tails[port_id]){
			return;
		}
		usartTXBuffer[tx_heads[port_id]] = *str++;
		tx_heads[port_id] = next_head;
	}
	USARTx->CR1 |= USART_CR1_TXEIE;
}


char usartReadByte(USART_TypeDef *USARTx){
	uint8_t port_id = usartIndex(USARTx);
	char *usartRXBuffer = usartRXBuffers[port_id];
	if(rx_tails[port_id] == rx_heads[port_id]){
		return '\0';
	}
	char result = usartRXBuffer[rx_tails[port_id]];
	rx_tails[port_id] = (rx_tails[port_id] + 1) % USART_BUFFER_SIZE;
	return result;
}


void usartReadBytes(USART_TypeDef *USARTx, char *buf, uint32_t max_len){
	uint8_t port_id = usartIndex(USARTx);
	char *usartRXBuffer = usartRXBuffers[port_id];
	uint32_t current_len = 0, end = 0;
	while((current_len + 1 < max_len) && rx_tails[port_id] != rx_heads[port_id]){
		char last_byte = usartRXBuffer[rx_tails[port_id]];
		if(last_byte == '\n'){
			end = 1;
		}
		buf[current_len++] = last_byte;
		rx_tails[port_id] = (rx_tails[port_id] + 1) % USART_BUFFER_SIZE;
		if(end){
			break;
		}
	}
	buf[current_len] = '\0';
}


void echo(USART_TypeDef *USARTx){
	if(USARTx->SR & USART_SR_RXNE){
		char temp = (USARTx->DR & 0xFF);
		USARTx->DR = temp;
	}
}


uint32_t usartDiv(uint32_t F_CPU, uint32_t baud_rate){
    return F_CPU/baud_rate;
}

uint8_t usartIndex(USART_TypeDef *USARTx){
	if(USARTx == USART2){
		return 1;
	}
	return 0;
}

__attribute__((weak)) void USART1_IRQHandler(void){
	USART_IRQHandler_Generic(USART1);
}


__attribute__((weak)) void USART2_IRQHandler(void){
	USART_IRQHandler_Generic(USART2);
}


void USART_IRQHandler_Generic(USART_TypeDef *USARTx){
	// ==== RX ====
	uint8_t port_id = usartIndex(USARTx);
	if(USARTx->SR & USART_SR_RXNE){
		char byte = (char)(USARTx->DR & 0xFF);
		uint16_t next_head = (rx_heads[port_id] + 1) % USART_BUFFER_SIZE;
		if(next_head != rx_tails[port_id]){
			volatile char *usartRXBuffer = usartRXBuffers[port_id];
			usartRXBuffer[rx_heads[port_id]] = byte;
			rx_heads[port_id] = next_head;
		}
	}
	// ==== TX ====
	if((USARTx->SR & USART_SR_TXE) && (USARTx->CR1 & USART_CR1_TXEIE)){
		volatile char *usartTXBuffer = usartTXBuffers[port_id];
		if(tx_tails[port_id] != tx_heads[port_id]){
			USARTx->DR = usartTXBuffer[tx_tails[port_id]];
			tx_tails[port_id] = (tx_tails[port_id] + 1) % USART_BUFFER_SIZE;
		}
		else{
			USARTx->CR1 &= ~USART_CR1_TXEIE;
		}
	}
}
