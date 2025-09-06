/*
 * Eepromx.h
 *
 *  Created on: Aug 30, 2025
 *      Author: CHINH
 */

#ifndef INC_EEPROMX_H_
#define INC_EEPROMX_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "stm32f1xx.h"


#define FLASH_START_ADDR 0x08019000       //the start address of  data space.
#define FLASH_END_ADDR   0x0801FC00       //the end address of  data space.






//#define FLASH_TYPEPROGRAM_HALFWORD             0x01U  /*!<Program a half-word (16-bit) at a specified address.*/
//#define FLASH_TYPEPROGRAM_WORD                 0x02U  /*!<Program a word (32-bit) at a specified address.*/
//#define FLASH_TYPEPROGRAM_DOUBLEWORD           0x03U  /*!<Program a double word (64-bit) at a specified address*/

//Function definition

HAL_StatusTypeDef Flash_ErasePage(uint8_t Page);
uint16_t Flash_Read(uint32_t Addr);
HAL_StatusTypeDef Flash_Write(uint32_t TypeProgram,uint32_t WriteAddr, uint16_t data);
#ifdef __cplusplus
}
#endif


#endif /* INC_EEPROMX_H_ */
