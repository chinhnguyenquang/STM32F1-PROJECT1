/*
 * SM9541.cpp
 *
 *  Created on: Sep 4, 2025
 *      Author: CHINH
 */
#include "SM9541.h"

extern I2C_HandleTypeDef hi2c1;
extern uint8_t data[4];
void Get_Tempe_Press(float *temperature, float *pressure){

	if (HAL_I2C_Master_Receive(&hi2c1, 0x28<<1, data, 4, 100)==HAL_OK){
				 uint16_t pressure_raw = ((uint16_t)data[0] << 8) | data[1];
				 uint16_t temp_raw = ((uint16_t)data[2]<<3) | (data[3]>>5);
				 uint8_t dat = (40) /10;
				 (*pressure) = (((float)pressure_raw - 1638)*dat / (14745 - 1638) -2)*6894.757;

				 //th2=1.0*4/(1.0*14745 - 1638)*(pressure_raw-1638)-2;
				 (*temperature) = (float)temp_raw*200/2048 - 50;

			}
}
