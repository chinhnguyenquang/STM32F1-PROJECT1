/*
 * SM9541.cpp
 *
 *  Created on: Sep 4, 2025
 *      Author: CHINH
 */
#include "SM9541.h"
#include "Switch.h"


#define SM9541_MAXCOUNT         14745
#define SM9541_MINCOUNT         1638


extern I2C_HandleTypeDef hi2c1;




#define SM9541_MAXCOUNT         14745
#define SM9541_MINCOUNT         1638

#define SM9541_PRESSURE_MAX     1961.28  /*980.7*/
#define SM9541_PRESSURE_MIN     -1961.28


uint8_t Get_Tempe_Press(float *t9541, float *p9541){
	uint8_t buf95_read[4]={0};
	uint8_t status =0;
	uint16_t pressure_adc,temperature_adc;
	float dat;
	if (HAL_I2C_Master_Receive(&hi2c1, 0x28<<1, buf95_read, 4, 200)==HAL_OK){
				 status=buf95_read[0]>>6;
				 if (status==0){
					 pressure_adc=(((uint16_t)buf95_read[0]&0x3f)<<8) | buf95_read[1];
					 temperature_adc=((uint16_t)buf95_read[2]<<3) | (buf95_read[3]>>5);
					 dat=SM9541_PRESSURE_MAX-SM9541_PRESSURE_MIN;
					 *p9541 = (pressure_adc - SM9541_MINCOUNT)*dat / (SM9541_MAXCOUNT - SM9541_MINCOUNT) +SM9541_PRESSURE_MIN;
					 *t9541 = (float)temperature_adc*200/2047 - 50;
					 return 1;
				 }
			}
	return 0;
}
