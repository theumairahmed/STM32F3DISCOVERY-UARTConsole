#include "main.h"
#include "stm32f3_discovery.h"

/* Private variables ---------------------------------------------------------*/
__IO uint32_t TimingDelay = 0;
RCC_ClocksTypeDef RCC_Clocks;

/* Private function Prototypes */
void USART1_Init (void);

int main ()
	
{

/* -----SysTick end of count event each 1ms Used to Generate PreciseInterrupts for Delay function---- */
	RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
	
	STM_EVAL_LEDInit (LED10);
	USART1_Init();
	
	while (1){
	STM_EVAL_LEDOn (LED10);
	Delay (50);
	STM_EVAL_LEDOff (LED10);
	Delay (50);
	}

}

void USART1_Init ()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	//Setting the GPIO Pins
  RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOA, &GPIO_InitStruct);
	
	GPIO_PinAFConfig (GPIOA, GPIO_Pin_9 , GPIO_AF_7);
	GPIO_PinAFConfig (GPIOA, GPIO_Pin_10 , GPIO_AF_7);
	
	//Setting the UART 
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1, ENABLE);
	
  USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init (USART1, &USART_InitStruct);
	
	USART_Cmd(USART1, ENABLE);
	
	///Enabling USART1 Interrupts
	USART_ITConfig (USART1, USART_IT_TXE, ENABLE);
	NVIC_EnableIRQ (USART1_IRQn);
	
 
}

//Interrupt Handler for USART1

void USART1_IRQHandler (void)
{

	if (USART_GetITStatus (USART1, USART_IT_TXE) == SET )
	{
       USART_SendData(USART1, 'h');
       USART_ClearITPendingBit(USART1, USART_IT_TXE);		
	}
	
	USART_ITConfig(USART1, USART_IT_TXE,DISABLE);

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
