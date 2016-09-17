#include "main.h"
#include "stm32f3_discovery.h"

/* Private variables ---------------------------------------------------------*/
__IO uint32_t TimingDelay = 0;
RCC_ClocksTypeDef RCC_Clocks;


int main ()
	
{

/* -----SysTick end of count event each 1ms Used to Generate PreciseInterrupts for Delay function---- */
	RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
	
	STM_EVAL_LEDInit (LED10);
	
	
	while (1){
	STM_EVAL_LEDOn (LED10);
	Delay (1000);
	STM_EVAL_LEDOff (LED10);
	Delay (1000);
	}

}
/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 10 ms.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}
