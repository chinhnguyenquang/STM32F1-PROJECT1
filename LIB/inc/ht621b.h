/*
 * HT621.h
 *
 *  Created on: Aug 5, 2025
 *      Author: CHINH
 */

#ifndef HT621B_H_
#define HT621B_H_


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include "stm32f1xx.h"
#include "Gpiox.h"





typedef struct {
  uint8_t map[2];
  uint8_t map1[11];
  uint8_t map2[10];
  uint8_t digit[6];
}HT1621Values;




class HT1621{
private:
	void wrBytes(uint8_t addr, uint8_t sdata);
	void wrCmd(uint8_t cmd);
	void sendBits(uint8_t sdata,uint8_t size);
	void ValuesConstructor();
	void Convert(uint16_t a,uint8_t line,uint8_t tmp);

	HT1621Values HT1621_data;
public:
	HT1621();
	void displayOn();
	void All_on();
	void clearAll();
	void Write_Float_Linex(float a,uint8_t line);
	void Write_Id(uint8_t a);
	void Write_INT_Linex(float a,uint8_t line);
};


#ifdef __cplusplus
}
#endif

#endif /* HT621_H_ */


