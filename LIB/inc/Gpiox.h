#ifndef __GPIOx_H
#define __GPIOx_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
/* Macro Definitions ---------------------------------------------------------*/

// Input modes
#define INPUT_ANALOG              ((uint8_t) 0x00)
#define INPUT_FLOATING            ((uint8_t) 0x01)
#define INPUT_PUPD                ((uint8_t) 0x02)

// Output types
#define OUTPUT_PP                 ((uint8_t) 0x00)
#define OUTPUT_OD                 ((uint8_t) 0x01)
#define OUTPUT_AF_PP              ((uint8_t) 0x02)
#define OUTPUT_AF_OD              ((uint8_t) 0x03)

// Speed modes
#define MODE_INPUT                ((uint8_t) 0x00)
#define MODE_OUTPUT_10MHZ        ((uint8_t) 0x01)
#define MODE_OUTPUT_2MHZ         ((uint8_t) 0x02)
#define MODE_OUTPUT_50MHZ        ((uint8_t) 0x03)

// Pull configurations
#define NOPULL                    ((uint8_t) 0x00)
#define PU                        ((uint8_t) 0x01)
#define PD                        ((uint8_t) 0x02)

/* Function Prototypes -------------------------------------------------------*/
void GPIOx_Init(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode, uint32_t Pull, uint32_t Speed);
void NVICx_Init(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);
#ifdef __cplusplus
}
#endif

#endif /* __my_GPIO_H */
