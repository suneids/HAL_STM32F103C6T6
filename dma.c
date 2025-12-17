#include "dma.h"

void DMAInit(DMA_Channel_TypeDef *DMAx, uint32_t peripheral_addr, uint32_t memory_addr, uint16_t data_count){
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	DMAx->CCR &= ~DMA_CCR_EN;
	DMAx->CCR = 0;
	DMAx->CCR |= DMA_CCR_MINC | DMA_CCR_CIRC | DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0;

	DMAx->CPAR = peripheral_addr;
	DMAx->CMAR = memory_addr;
	DMAx->CNDTR = data_count;

	DMAx->CCR |= DMA_CCR_EN;

}
