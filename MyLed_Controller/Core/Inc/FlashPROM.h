#ifndef INC_FLASHPROM_H_
#define INC_FLASHPROM_H_

#include "stm32f1xx_hal.h"

#define START_ADDR ((uint32_t)0x0801FC00)
#define END_ADDR   ((uint32_t)0x0801FFFF)

void FlashPROM_Init(uint16_t buffsize);
void FlashPROM_Write8(uint8_t* buff);
void FlashPROM_Read8(uint8_t* buff);
void FlashPROM_Write16(uint16_t* buff);
void FlashPROM_Read16(uint16_t* buff);

void EraseFlash();

#endif
