/*
 * Flags.cpp
 *
 *  Created on: Sep 4, 2025
 *      Author: CHINH
 */


#include "Flags.h"

void Flags::TurnONFlags(void) {
	#ifdef _Flag_500ms
		if ((HAL_GetTick() - StartTimer.t1s) >= 500) {
			Flag.t500ms = true;
			StartTimer.t500ms =HAL_GetTick();
		}
	#endif
    #ifdef _Flag_1s
        if ((HAL_GetTick() - StartTimer.t1s) >= 1000) {
            Flag.t1s = true;
            StartTimer.t1s = HAL_GetTick();
        }
    #endif
    #ifdef _Flag_2s
        if ((HAL_GetTick() - StartTimer.t2s) >= 2000) {
            Flag.t2s = true;
            StartTimer.t2s = HAL_GetTick();
        }
    #endif
    #ifdef _Flag_3s
        if ((HAL_GetTick() - StartTimer.t3s) >= 3000) {
            Flag.t3s = true;
            StartTimer.t3s = HAL_GetTick();
        }
    #endif
    #ifdef _Flag_4s
        if ((HAL_GetTick() - StartTimer.t4s) >= 4000) {
            Flag.t4s = true;
            StartTimer.t4s = HAL_GetTick();
        }
    #endif
	#ifdef _Flag_10s
		if ((HAL_GetTick() - StartTimer.t10s) >= 10000) {
			Flag.t10s = true;
			StartTimer.t10s = HAL_GetTick();
		}
	#endif
	#ifdef _Flag_1m
		if ((HAL_GetTick() - StartTimer.t1m) >= 60000) {
			Flag.t1m = true;
			StartTimer.t1m = HAL_GetTick();
		}
	#endif
}



void Flags::TurnOFFFlags(void) {
	#ifdef _Flag_500ms
		Flag.t500ms  =   false;
	#endif
    #ifdef _Flag_1s
        Flag.t1s  =   false;
    #endif
    #ifdef _Flag_2s
        Flag.t2s  =   false;
    #endif
    #ifdef _Flag_3s
        Flag.t3s  =   false;
    #endif
    #ifdef _Flag_4s
        Flag.t4s  =   false;
    #endif
	#ifdef _Flag_10s
		Flag.t10s  =   false;
	#endif
	#ifdef _Flag_1m
		Flag.t1m  =   false;
	#endif

}
