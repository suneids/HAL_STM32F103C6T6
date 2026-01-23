#ifndef DMA_H
#define DMA_H
#include "gpio.h"

void DMAInit(DMA_Channel_TypeDef *DMAx, uint32_t peripheral_addr, uint32_t memory_addr, uint16_t data_count);

#endif
