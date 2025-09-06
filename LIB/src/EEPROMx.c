/*
 * Eepromx.cpp
 *
 *  Created on: Aug 30, 2025
 *      Author: CHINH
 */
#include "EEPROMx.h"

uint16_t Flash_Read(uint32_t Addr)
{

    return *(uint16_t *)(Addr);

}

HAL_StatusTypeDef Flash_ErasePage(uint8_t Page)
{
	HAL_StatusTypeDef status;

	assert_param(IS_FLASH_ADDRESS(Page_Address));

	HAL_FLASH_Unlock();
    // Define the page and bank for the erase operation
    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t PageError = 0x0;
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.Banks = FLASH_BANK_1;
    EraseInitStruct.PageAddress =(FLASH_BASE + ((Page) * FLASH_PAGE_SIZE));
    EraseInitStruct.NbPages = 1;

    status = HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

    HAL_FLASH_Lock();

  	return status;

}





HAL_StatusTypeDef Flash_Write(uint32_t TypeProgram,uint32_t WriteAddr, uint16_t data)
{

	HAL_StatusTypeDef state;

	assert_param((((WriteAddr) >= FLASH_START_ADDR) && ((WriteAddr) <= FLASH_END_ADDR)));

	HAL_FLASH_Unlock();


	state = HAL_FLASH_Program(TypeProgram, WriteAddr,data);

    HAL_FLASH_Lock();

    return state;

}
