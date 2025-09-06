#include "Gpiox.h"

void GPIOx_Init(GPIO_TypeDef *GPIOx,uint32_t Pin,uint32_t Mode,uint32_t Pull,uint32_t Speed){
		//clock enable
		if(GPIOx==GPIOA) RCC->APB2ENR |=(1<<2);
		else if(GPIOx==GPIOB) RCC->APB2ENR |=(1<<3);
		else if(GPIOx==GPIOC) RCC->APB2ENR |=(1<<4);


		if(Pin<8){
			GPIOx->CRL&=~(0xF<<(Pin*4));
			GPIOx->CRL|=((Mode<<2)+Speed)<<(Pin*4);
		}
		else{
			GPIOx->CRH&=~(0xF<<((Pin-8)*4));
			GPIOx->CRH|=((Mode<<2)+Speed)<<((Pin-8)*4);
		}
		if(Pull==PU) GPIOx->ODR |=(1<<Pin);
		else if (Pull==PD) GPIOx->ODR &=~(1<<Pin);
}

void NVICx_Init(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t prioritygroup = 0x00U;

  prioritygroup = NVIC_GetPriorityGrouping();

  NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, PreemptPriority, SubPriority));

	NVIC_EnableIRQ(IRQn);
}
