/*
 * Switch.cpp
 *
 *  Created on: Sep 11, 2025
 *      Author: CHINH
 */


#include "Switch.h"

Switch_Range Status_Switch_Cur;
extern uint32_t data_adc;

typedef struct {
    uint16_t min;
    uint16_t max;
    sm9541_range_t range;
    uint8_t response;
} RangeMapping;

const RangeMapping rangeMap[] = {
        {0, 100, SM9541_RANGE_100PA, 1},
        {300, 550, SM9541_RANGE_100PA, 4},
        {750, 890, SM9541_RANGE_250PA, 1},
        {1000, 1200, SM9541_RANGE_250PA, 4},
        {1270, 1400, SM9541_RANGE_500PA, 1},
        {1470, 1600, SM9541_RANGE_500PA, 4},
        {1650, 1790, SM9541_RANGE_750PA, 1},
        {1820, 1900, SM9541_RANGE_750PA, 4},
        {1950, 2030, SM9541_RANGE_1000PA, 1},
        {2070, 2150, SM9541_RANGE_1000PA, 4},
        {2160, 2260, SM9541_RANGE_1500PA, 1},
        {2270, 2340, SM9541_RANGE_1500PA, 4},
        {2360, 2410, SM9541_RANGE_2000PA, 1},
        {2425, 2500, SM9541_RANGE_2000PA, 4},
        {2515, 2575, SM9541_RANGE_2500PA, 1},
        {2585, 2690, SM9541_RANGE_2500PA, 4}
    };

void Status_Current_Switch(){

	for (uint8_t i = 0; i < 16; i++) {
	        if ((data_adc >= rangeMap[i].min) && (data_adc <= rangeMap[i].max)) {
	            Status_Switch_Cur.range_sm9541_cur = rangeMap[i].range;
	            Status_Switch_Cur.response = rangeMap[i].response;
	            return;
	        }
	    }
    // Default
    Status_Switch_Cur.range_sm9541_cur = SM9541_RANGE_2000PA;
    Status_Switch_Cur.response = 1;
}
