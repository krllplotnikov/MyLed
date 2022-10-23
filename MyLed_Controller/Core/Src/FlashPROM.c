#include "FlashPROM.h"

uint16_t BUFFSIZE = 0;

void FlashPROM_Init(uint16_t buffsize){
	BUFFSIZE = buffsize;
}

//void FlashPROM_Write8(uint8_t* buff){
//	uint32_t WRITE_ADDR = START_ADDR;
//	while(WRITE_ADDR < END_ADDR){
//		if(*(__IO uint32_t*)WRITE_ADDR != 0xFFFFFFFF)
//			WRITE_ADDR += BUFFSIZE;
//		else break;
//	}
//
//	if((WRITE_ADDR > END_ADDR) || (WRITE_ADDR + BUFFSIZE > END_ADDR)){
//		EraseFlash();
//		WRITE_ADDR = START_ADDR;
//	}
//
//	HAL_FLASH_Unlock();
//	for(int i = 0; i < BUFFSIZE; i++)
//		HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, WRITE_ADDR + i, buff[i]);
//	HAL_FLASH_Lock();
//}
//
//void FlashPROM_Read8(uint8_t* buff){
//	uint32_t READ_ADDR = START_ADDR;
//	while(READ_ADDR < END_ADDR){
//		if(*(__IO uint32_t*)(READ_ADDR + BUFFSIZE) != 0xFFFFFFFF)
//			READ_ADDR += BUFFSIZE;
//		else break;
//	}
//
//	if((READ_ADDR > END_ADDR) || (READ_ADDR + BUFFSIZE > END_ADDR)){
//		READ_ADDR = START_ADDR;
//	}
//
//	for(int i = 0; i < BUFFSIZE; i++)
//		buff[i] = *(__IO uint32_t*)(READ_ADDR + i);
//}

void FlashPROM_Write16(uint16_t* buff){
	uint32_t WRITE_ADDR = START_ADDR;
	while(WRITE_ADDR < END_ADDR){
		if(*(__IO uint32_t*)WRITE_ADDR != 0xFFFFFFFF)
			WRITE_ADDR += BUFFSIZE * 2;
		else break;
	}

	if((WRITE_ADDR > END_ADDR) || (WRITE_ADDR + BUFFSIZE * 2 > END_ADDR)){
		EraseFlash();
		WRITE_ADDR = START_ADDR;
	}

	HAL_FLASH_Unlock();
	for(int i = 0; i < BUFFSIZE; i++)
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, WRITE_ADDR + i*2, buff[i]);
	HAL_FLASH_Lock();
}

void FlashPROM_Read16(uint16_t* buff){
	uint32_t READ_ADDR = START_ADDR;
	while(READ_ADDR < END_ADDR){
		if(*(__IO uint32_t*)(READ_ADDR + BUFFSIZE * 2) != 0xFFFFFFFF)
			READ_ADDR += BUFFSIZE * 2;
		else break;
	}

	if((READ_ADDR > END_ADDR) || (READ_ADDR + BUFFSIZE * 2 > END_ADDR)){
		READ_ADDR = START_ADDR;
	}

	for(int i = 0; i < BUFFSIZE; i++)
		buff[i] = *(__IO uint32_t*)(READ_ADDR + i*2);
}

void EraseFlash(){
	static FLASH_EraseInitTypeDef EraseInitStruct;

	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = START_ADDR;
	EraseInitStruct.NbPages = 1;

	uint32_t page_error = 0;

	HAL_FLASH_Unlock();
	HAL_FLASHEx_Erase(&EraseInitStruct, &page_error);
	HAL_FLASH_Lock();
}

//*(__IO uint32_t*)ADDR
