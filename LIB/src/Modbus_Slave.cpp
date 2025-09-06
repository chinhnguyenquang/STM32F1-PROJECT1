/*
 * Modbus.c
 *
 *  Created on: Aug 14, 2025
 *      Author: CHINH
 */
#include <Modbus_Slave.h>


#define ILLEGAL_FUNCTION       0x01
#define ILLEGAL_DATA_ADDRESS   0x02
#define ILLEGAL_DATA_VALUE     0x03

#define ADD_Flash_Slave_ID 0x0801FCF0


Modbus_Slave::Modbus_Slave(){
	GPIOA->ODR &=~(1<<11);
	GPIOA->ODR &=~(1<<12);
	this->Slave_id_to_Eeprom=Flash_Read(ADD_Flash_Slave_ID);
	if ((this->Slave_id_to_Eeprom<255)&&(this->Slave_id_to_Eeprom >0)) this->Slave_id=this->Slave_id_to_Eeprom;
	else{
		this->Slave_id=0x01;
		this->Slave_id_to_Eeprom=0x01;
	}

}
void Modbus_Slave::USARTx_PutS_Size(USART_TypeDef *USARTx, uint8_t *data,uint8_t size){
	uint32_t timeout=0;
	for (uint8_t i=0;i<size;++i){
		while(!(USARTx->SR & (1<<7))){++timeout; if (timeout==0xFFFFFFF) return;};
		USARTx->DR =data[i];
		timeout=0;
	}
	while(!(USARTx->SR & (1<<6))) {++timeout; if (timeout==0xFFFF) return;}
}


uint16_t CRC16 (uint8_t *nData, uint16_t wLength)
{
    uint16_t temp, flag;
    temp = 0xFFFF;
    for (uint16_t  i = 0; i < wLength; i++)
    {
        temp = temp ^ nData[i];
        for (uint8_t j = 1; j <= 8; j++)
        {
            flag = temp & 0x0001;
            temp >>=1;
            if (flag)
                temp ^= 0xA001;
        }
    }
    temp &= 0xFFFF;
    return temp;
}

void Modbus_Slave::sendData(uint8_t *data, int size)
{
	// we will calculate the CRC in this function itself
	uint16_t crc = CRC16(data, size);
	data[size] = crc&0xFF;   // CRC LOW
	data[size+1] = (crc>>8)&0xFF;  // CRC HIGH
	GPIOA->ODR |=(1<<11);
	GPIOA->ODR |=(1<<12);
	USARTx_PutS_Size(USART1,data,size+2);
	GPIOA->ODR &=~(1<<11);
	GPIOA->ODR &=~(1<<12);
}

void Modbus_Slave::modbusException (uint8_t exceptioncode)
{
	//| SLAVE_ID | FUNCTION_CODE | Exception code | CRC     |
	//| 1 BYTE   |  1 BYTE       |    1 BYTE      | 2 BYTES |

	this->TxData[0] = this->RxData[0];       // slave ID
	this->TxData[1] = this->RxData[1]|0x80;  // adding 1 to the MSB of the function code
	this->TxData[2] = exceptioncode;   // Load the Exception code
	sendData(this->TxData, 3);         // send Data... CRC will be calculated in the function
}


//10 not function expected
uint8_t Modbus_Slave::Check_Buffer(USART_TypeDef *USARTx){
	uint8_t status=0;
		if (this->RxData[0] == this->Slave_id){
			switch (this->RxData[1]){
			case 0x03:
				readHoldingRegs();
				break;
			case 0x04:
				readInputRegs_FC4();
				break;
			case 0x06:
				WriteIDRegs_FC6();
				break;
			default:
				break;
			}
	}
	return status;
}

uint8_t Modbus_Slave::readInputRegs_FC4 (void)
{
	uint16_t startAddr = ((this->RxData[2]<<8)|this->RxData[3]);  // start Register Address

	uint16_t numRegs = ((this->RxData[4]<<8)|this->RxData[5]);   // number to registers master has requested
	if ((numRegs<1)||(numRegs>125))  // maximum no. of Registers as per the PDF
	{
		modbusException (ILLEGAL_DATA_VALUE);  // send an exception
		return 0;
	}

	uint16_t endAddr = startAddr+numRegs-1;  // end Register
	if (endAddr>49)  // end Register can not be more than 49 as we only have record of 50 Registers in total
	{
		modbusException(ILLEGAL_DATA_ADDRESS);   // send an exception
		return 0;
	}

	// Prepare TxData buffer

	//| SLAVE_ID | FUNCTION_CODE | BYTE COUNT | DATA      | CRC     |
	//| 1 BYTE   |  1 BYTE       |  1 BYTE    | N*2 BYTES | 2 BYTES |

	this->TxData[0] = this->Slave_id;  // slave ID
	this->TxData[1] = this->RxData[1];  // function code
	this->TxData[2] = numRegs*2;  // Byte count
	int indx = 3;  // we need to keep track of how many bytes has been stored in TxData Buffer

	for (int i=0; i<numRegs; i++)   // Load the actual data into TxData buffer
	{
		this->TxData[indx++] = (Input_Registers_Database[startAddr]>>8)&0xFF;  // extract the higher byte
		this->TxData[indx++] = (Input_Registers_Database[startAddr])&0xFF;   // extract the lower byte
		startAddr++;  // increment the register address
	}

	sendData(this->TxData, indx);  // send data... CRC will be calculated in the function itself
	memset(RxData, 0, sizeof(Buffer_Size_Rx_Modbus));
	memset(TxData, 0, sizeof(Buffer_Size_Tx_Modbus));
	return 1;   // success
}

uint8_t Modbus_Slave::readHoldingRegs(){
	return 1;
}


// address = 0x01
uint8_t Modbus_Slave::WriteIDRegs_FC6(){
	uint16_t address=((this->RxData[2]<<8)|this->RxData[3]);
	uint16_t data=((this->RxData[4]<<8)|this->RxData[5]);
	if (address!=0x01)
	{
		modbusException(ILLEGAL_DATA_ADDRESS);
		return 0;
	}
	if ((data ==0) || (data >247)){
		modbusException(ILLEGAL_DATA_VALUE);
		return 0;
	}
	this->Slave_id_to_Eeprom=data;
	for(uint8_t i=0;i<6;++i){
		this->TxData[i]=this->RxData[i];
	}
	sendData(this->TxData,6);
	memset(RxData, 0, sizeof(Buffer_Size_Rx_Modbus));
	memset(TxData, 0, sizeof(Buffer_Size_Tx_Modbus));
	return 1;
}
