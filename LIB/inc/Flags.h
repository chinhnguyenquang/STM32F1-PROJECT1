/*
 * Flags.h
 *
 *  Created on: Sep 4, 2025
 *      Author: CHINH
 */

#ifndef INC_FLAGS_H_
#define INC_FLAGS_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx.h"

//----------------------------------------------------//
//-------- Begin: Các define cho cờ thời gian --------//
//----------------------------------------------------//
// Lưu ý: muốn sử dụng cờ nào thì mở define cho cờ đó.
#define _Flag_500ms
#define _Flag_1s
//#define _Flag_2s
//#define _Flag_3s
#define _Flag_4s
//#define _Flag_1m
#define _Flag_10s

typedef struct {
#ifdef _Flag_500ms
  bool t500ms = 0;
#endif
#ifdef _Flag_1s
  bool t1s = 0;
#endif
#ifdef _Flag_2s
  bool t2s = 0;
#endif
#ifdef _Flag_3s
  bool t3s = 0;
#endif
#ifdef _Flag_4s
  bool t4s = 0;
#endif
#ifdef _Flag_10s
  bool t10s = 0;
#endif
#ifdef _Flag_1m
  bool t1m = 0;
#endif
} flagType;

typedef struct {
#ifdef _Flag_500ms
 uint32_t t500ms = 0;
#endif
#ifdef _Flag_1s
  uint32_t t1s = 0;
#endif
#ifdef _Flag_2s
  uint32_t t2s = 0;
#endif
#ifdef _Flag_3s
  uint32_t t3s = 0;
#endif
#ifdef _Flag_4s
  uint32_t t4s = 0;
#endif

#ifdef _Flag_10s
  uint32_t t10s = 0;
#endif

#ifdef _Flag_1m
  uint32_t t1m = 0;
#endif


} startType;

class Flags {
private:
  startType StartTimer;

public:
  flagType Flag;
  void TurnONFlags(void);
  void TurnOFFFlags(void);
};


#ifdef __cplusplus
}
#endif
#endif /* INC_FLAGS_H_ */
