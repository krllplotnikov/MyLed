#ifndef INC_FLASHPROM_H_
#define INC_FLASHPROM_H_

#include "stm32f1xx_hal.h"

#ifdef __STM32F1xx_HAL_H
//F103C8
//#define START_ADDR ((uint32_t)0x0801F800)
//#define END_ADDR   ((uint32_t)0x0801FBFF)

//F103C6
#define START_ADDR ((uint32_t)0x08007C00)
#define END_ADDR   ((uint32_t)0x08007FFF)
#endif

#ifdef __STM32F4xx_HAL_H
//F411
//#define START_ADDR ((uint32_t)0x08060000)
//#define END_ADDR   ((uint32_t)0x0807FFFF)

//F401
//#define START_ADDR ((uint32_t)0x08020000)
//#define END_ADDR   ((uint32_t)0x0803FFFF)
#endif

void FlashPROM_Init(uint16_t buffsize);
void FlashPROM_Write(void* buff);
void FlashPROM_Read(void* buff);

void EraseFlash();

#endif
