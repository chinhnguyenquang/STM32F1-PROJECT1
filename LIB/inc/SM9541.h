/*
 * SMI_9541.h
 *
 *  Created on: Sep 4, 2025
 *      Author: CHINH
 */

#ifndef INC_SM9541_H_
#define INC_SM9541_H_


#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f1xx.h"
#include <main.h>
#include "Switch.h"




uint8_t Get_Tempe_Press(float *temperature, float *pressure);


#ifdef __cplusplus
}
#endif

#endif /* INC_SM9541_H_ */
