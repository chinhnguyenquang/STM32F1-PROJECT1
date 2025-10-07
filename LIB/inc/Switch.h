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




extern uint8_t Response_Switch;
extern uint16_t Value_Switch_Pre;


void Status_Current_Switch();





#ifdef __cplusplus
}
#endif


#endif /* INC_SWITCH_H_ */
