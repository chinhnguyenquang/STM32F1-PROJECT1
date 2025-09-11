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



extern Switch_Range Status_Switch_Cur;
float P_sensor_range;

void p_sensor_range(){
	 switch(Status_Switch_Cur.range_sm9541_cur)
	    {
	        case SM9541_RANGE_100PA:
	        	P_sensor_range=0.2f;
	            break;

	        case SM9541_RANGE_250PA:
	        	P_sensor_range=0.5f;
	            break;

	        case SM9541_RANGE_500PA:
	        	P_sensor_range=1.0f;
	            break;

	        case SM9541_RANGE_750PA:
	        	P_sensor_range=1.5f;
	            break;

	        case SM9541_RANGE_1000PA:
	        	P_sensor_range=2.0f;
	            break;

	        case SM9541_RANGE_1500PA:
	        	P_sensor_range=3.0f;
	            break;

	        case SM9541_RANGE_2000PA:
	        	P_sensor_range=4.0f;
	            break;

	        case SM9541_RANGE_2500PA:
	        	P_sensor_range=5.0f;
	            break;

	        default:
	        	P_sensor_range=4.0f; //tu chọn
	            break;
	    }
}

#define SM9541_MAXCOUNT         14745
#define SM9541_MINCOUNT         1638

uint8_t Get_Tempe_Press(float *t9541, float *p9541){
	uint8_t buf95_read[4]={0};
	uint8_t status =0;
	uint16_t pressure_adc,temperature_adc;
	float dat;
	if (HAL_I2C_Master_Receive(&hi2c1, 0x28<<1, buf95_read, 4, 100)==HAL_OK){
				 status=buf95_read[0]>>6;
				 if (!status){
					 pressure_adc=((buf95_read[0]&0x3f)<<8) | buf95_read[1];
					 temperature_adc=(buf95_read[2]<<3) | (buf95_read[3]>>5);
					 dat = P_sensor_range /10;
					 *p9541 = (pressure_adc - SM9541_MINCOUNT)*dat / (SM9541_MAXCOUNT - SM9541_MINCOUNT) + P_sensor_range/10;
					 *t9541 = (float)temperature_adc*200/2047 - 50;
					 return 1;
				 }
			}
	return 0;
}
