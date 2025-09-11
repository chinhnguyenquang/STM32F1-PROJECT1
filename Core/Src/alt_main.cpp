/*
 * alt_main.cpp
 *
 *  Created on: Aug 9, 2025
 *      Author: CHINH
 */

#include "alt_main.h"
#include "main.h"
#include <string.h>
///////////////////////
#include "ht621b.h"
#include "Modbus_Slave.h"
#include "EEPROMx.h"
#include "gpiox.h"
#include "Flags.h"
#include "SM9541.h"
#include "Switch.h"
//                                     CLASS
HT1621 _Ht621b;
Modbus_Slave _Modbus_Slave;
Flags _Flags;
////////////////////////
extern uint8_t RxBuf_DMA[10];
extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern ADC_HandleTypeDef hadc1;

///								LCD HT1621
typedef enum {
	NORMAL=1,
	SLAVE_ID=0
}Status_Display;

Status_Display Status_stm32=NORMAL;
bool Status_initial_LCD=true;

/////////////////////////////////


////                             SM9541
float temperature_Sm9541=0,pressure_Sm9541=0;
float temperature_Sm9541_cur=0,pressure_Sm9541_cur=0;
uint8_t data[4];

//////////                      ADC
uint32_t data_adc=0;
///////////////////////////////////

////                          Switch






void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart->Instance == USART1)
	{
		_Modbus_Slave.Check_Buffer(USART1);
		/* start the DMA again */
		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t *) _Modbus_Slave.RxData, 10);
		__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);

	}


}





uint32_t cur_time_ext=0,pre_time_ext=0;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
 /* Prevent unused argument(s) compilation warning */
 UNUSED(GPIO_Pin);
 	 cur_time_ext=HAL_GetTick();
	 if ((GPIO_Pin==GPIO_PIN_5)||(cur_time_ext-pre_time_ext>10)){
		 Status_stm32=(Status_stm32==NORMAL)?SLAVE_ID:NORMAL;
		 Status_initial_LCD=true;
	 }
}


uint16_t id=0;







void Tacvu_HIENTHI(void){
	id=_Modbus_Slave.Slave_id_to_Eeprom;
	if (Status_stm32==NORMAL){
		_Ht621b.clearAll();
		_Ht621b.displayOn();
		_Ht621b.Write_Float_Linex(temperature_Sm9541_cur,2);
		_Ht621b.Write_Float_Linex(pressure_Sm9541_cur,1);

	}
	else {
		_Ht621b.clearAll();
		_Ht621b.Write_Id(_Modbus_Slave.Slave_id);


	}
}


extern Switch_Range Status_Switch_Cur;
/////         THUC THI TAC VU THEO FLAG //////////
void ThucThiTacVuTheoFlag(){
	if (_Flags.Flag.t500ms){

	}
    if (_Flags.Flag.t1s) {
    	Status_Current_Switch(); //UPDATE CURRENT SWITCH
    	if (Status_Switch_Cur.response==1){
    		p_sensor_range();
        	if (Get_Tempe_Press(&temperature_Sm9541, &pressure_Sm9541)){
        		temperature_Sm9541_cur=temperature_Sm9541,
        		pressure_Sm9541_cur=pressure_Sm9541;
        	}
        	Tacvu_HIENTHI();
    	}

    }
    if (_Flags.Flag.t4s){
    	if (Status_Switch_Cur.response==4){
    		p_sensor_range();
        	if (Get_Tempe_Press(&temperature_Sm9541, &pressure_Sm9541)){
        		temperature_Sm9541_cur=temperature_Sm9541,
        		pressure_Sm9541_cur=pressure_Sm9541;
        	}
        	Tacvu_HIENTHI();
    	}
    }
    if (_Flags.Flag.t10s){

    }
}


#define ADD_Flash_Slave_ID 0x0801FCF0
///////////          LUU ID VAO FLASH (EEPROM)  /////////////////
void Check_Slaveid(){
	id=_Modbus_Slave.Slave_id;
	if(_Modbus_Slave.Slave_id!=_Modbus_Slave.Slave_id_to_Eeprom){
		Flash_ErasePage(127);
		Flash_Write(FLASH_TYPEPROGRAM_WORD,ADD_Flash_Slave_ID,_Modbus_Slave.Slave_id_to_Eeprom);
		_Modbus_Slave.Slave_id=_Modbus_Slave.Slave_id_to_Eeprom;
	}

}

void initial_UART_DMA(){
	  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, _Modbus_Slave.RxData, 10);
	  __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
}
/////////////////////////////////////////////////////////////////////////////
void alt_main()
{
	/* Initialization */

	initial_UART_DMA();
	 // _Ht621b.All_on();
	HAL_ADC_Start_DMA(&hadc1, &data_adc, 1);

	Status_Current_Switch();
	while (1)
	{
		/* Super loop */
		_Flags.TurnONFlags();
		if (Status_initial_LCD){Status_initial_LCD=false;Tacvu_HIENTHI();}
		Check_Slaveid();
		ThucThiTacVuTheoFlag();
		_Flags.TurnOFFFlags();

	}
}
