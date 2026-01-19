#ifndef I2C_H
#define I2C_H
#include "gpio.h"
// В проекте Glove не используется постольку, поскольку ломает соседние пины
void I2C_Init(I2C_TypeDef *I2Cx, Pin_t SDA, Pin_t SCL);
void I2C_Start(I2C_TypeDef *I2Cx);
void I2C_WriteReg(I2C_TypeDef *I2Cx, uint8_t devAddr, uint8_t regAddr, uint8_t data);
void I2C_WriteByteArray(I2C_TypeDef *I2Cx, uint8_t devAddr, uint8_t regAddr, uint8_t *pData, uint16_t len);
uint8_t I2C_ReadReg(I2C_TypeDef *I2Cx, uint8_t devAddr, uint8_t regAddr);
void I2C_Read_Burst(I2C_TypeDef *I2Cx, uint8_t devAddr, uint8_t regAddr, uint8_t *pBuffer, uint16_t size);
#endif
