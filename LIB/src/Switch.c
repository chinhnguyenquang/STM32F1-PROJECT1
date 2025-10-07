/*
 * Switch.cpp
 *
 *  Created on: Sep 11, 2025
 *      Author: CHINH
 */


#include "Switch.h"


extern uint32_t data_adc;

uint8_t Response_Switch;
uint16_t Value_Switch_Pre;



const uint16_t minVal[16]  = {0,300,750,1000,1270,1470,1650,1820,1950,2070,2160,2270,2360,2425,2515,2585};
const uint16_t maxVal[16]  = {100,550,890,1200,1400,1600,1790,1900,2030,2150,2260,2340,2410,2500,2575,2690};


const uint16_t rangeVal[16] = {
    100, 100,   // 100 Pa
    250, 250,   // 250 Pa
    500, 500,   // 500 Pa
    750, 750,   // 750 Pa
    1000, 1000, // 1000 Pa
    1500, 1500, // 1500 Pa
    2000, 2000, // 2000 Pa
    2500, 2500  // 2500 Pa
};

const uint8_t respVal[16]  = {1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4};

void Status_Current_Switch(){

	for (uint8_t i = 0; i < 16; i++) {
	        if ((data_adc >= minVal[i]) && (data_adc <= maxVal[i])) {
	        	Response_Switch=respVal[i];
	        	Value_Switch_Pre=rangeVal[i];
	            return;
	        }
	    }
    // Default
	Response_Switch=respVal[12];
	Value_Switch_Pre=rangeVal[12];
}
