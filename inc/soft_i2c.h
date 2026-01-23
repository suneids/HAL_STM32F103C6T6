#ifndef SOFT_I2C_H
#define SOFT_I2C_H
#define I2C_DELAY() for(volatile int i=0; i < 5000; i++)
#include "gpio.h"
void SoftI2C_Start(Pin_t sda, Pin_t scl);
void SoftI2C_Stop(Pin_t sda, Pin_t scl);
uint8_t SoftI2C_Write(Pin_t sda, Pin_t scl, uint8_t byte);
uint8_t SoftI2C_Read(Pin_t sda, Pin_t scl, uint8_t ack);

#endif
