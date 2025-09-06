/*
 * Modbus.h
 *
 *  Created on: Aug 14, 2025
 *      Author: CHINH
 */

#ifndef INC_MODBUS_SLAVE_H_
#define INC_MODBUS_SLAVE_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f1xx.h"
#include "string.h"
#include "alt_main.h"
#include "EEPROMx.h"

#define Buffer_Size_Rx_Modbus 16
#define Buffer_Size_Tx_Modbus 256
//Request only function 3 4

static const uint16_t Input_Registers_Database[50]={
		0000,  1111,  2222,  3333,  4444,  5555,  6666,  7777,  8888,  9999,   // 0-9   30001-30010
		12345, 15432, 15535, 10234, 19876, 13579, 10293, 19827, 13456, 14567,  // 10-19 30011-30020
		21345, 22345, 24567, 25678, 26789, 24680, 20394, 29384, 26937, 27654,  // 20-29 30021-30030
		31245, 31456, 34567, 35678, 36789, 37890, 30948, 34958, 35867, 36092,  // 30-39 30031-30040
		45678, 46789, 47890, 41235, 42356, 43567, 40596, 49586, 48765, 41029,  // 40-49 30041-30050
};

class Modbus_Slave{
private:
	uint16_t Slave_id_to_Eeprom;
	uint8_t Slave_id;
	uint8_t RxData[Buffer_Size_Rx_Modbus];
	uint8_t TxData[Buffer_Size_Tx_Modbus];
	void sendData (uint8_t *data, int size);
	void modbusException (uint8_t exceptioncode);
	uint8_t readHoldingRegs();
	uint8_t readInputRegs_FC4();
	//only Write ID Slave id
	uint8_t WriteIDRegs_FC6();

public:
	Modbus_Slave();
	uint8_t Check_Buffer(USART_TypeDef *USARTx);
	void USARTx_PutS_Size(USART_TypeDef *USARTx, uint8_t *data,uint8_t size);
	friend void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);\
	friend void initial_UART_DMA();
	friend void Tacvu_HIENTHI();
	friend void Check_Slaveid();
};



#ifdef __cplusplus
}
#endif


#endif /* INC_MODBUS_SLAVE_H_ */
