
#include "bsp_usart_dma.h"

uint8_t txMessages[SENDBUFF_SIZE];

/**
  * @brief  USART GPIO 配置,工作参数配置
  * @param  无
  * @retval 无
  */
void USART_Config(void)
{
//	NVIC_InitTypeDef  nvic;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
//	nvic.NVIC_IRQChannel = USART1_IRQn;
//  nvic.NVIC_IRQChannelPreemptionPriority = 1;
//  nvic.NVIC_IRQChannelSubPriority = 3;
//  nvic.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&nvic);
	
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;

	USART_InitStructure.USART_WordLength = USART_WordLength_8b;

	USART_InitStructure.USART_StopBits = USART_StopBits_1;

	USART_InitStructure.USART_Parity = USART_Parity_No ;

	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(DEBUG_USARTx, &USART_InitStructure);	
	
//	USART_ITConfig(DEBUG_USARTx,USART_IT_TC,ENABLE);

	USART_Cmd(DEBUG_USARTx, ENABLE);	    
}


/**
  * @brief  USARTx TX DMA 配置，内存到外设(USART1->DR)
  * @param  无
  * @retval 无
  */
void USARTx_DMA_Config(void)
{
		DMA_InitTypeDef DMA_InitStructure;

		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART_DR_ADDRESS;
		DMA_InitStructure.DMA_MemoryBaseAddr = (u32)txMessages;
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
		DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;   
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	   
		DMA_Init(USART_TX_DMA_CHANNEL, &DMA_InitStructure);		
		DMA_Cmd (USART_TX_DMA_CHANNEL,ENABLE);
}

//void USART1_IRQHandler(void)
//{
//	if (USART_GetITStatus(USART1, USART_IT_TC) != RESET)
//	{
//		(void)USART1->SR;
//		(void)USART1->DR;	
//	}
//}
