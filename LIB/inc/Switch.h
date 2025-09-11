/*
 * Switch.h
 *
 *  Created on: Sep 11, 2025
 *      Author: CHINH
 */

#ifndef INC_SWITCH_H_
#define INC_SWITCH_H_



#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx.h"
#include "string.h"
#include "SM9541.h"
#include "main.h"

typedef enum
{
    SM9541_RANGE_100PA=0,
    SM9541_RANGE_250PA=1,
    SM9541_RANGE_500PA=2,
    SM9541_RANGE_750PA=3,
    SM9541_RANGE_1000PA=4,
    SM9541_RANGE_1500PA=5,
    SM9541_RANGE_2000PA=6,
    SM9541_RANGE_2500PA=7
} sm9541_range_t;

typedef struct {
	uint8_t response;
	sm9541_range_t range_sm9541_cur;
}Switch_Range;

extern Switch_Range Status_Switch_Cur;

void Status_Current_Switch();





#ifdef __cplusplus
}
#endif


#endif /* INC_SWITCH_H_ */
