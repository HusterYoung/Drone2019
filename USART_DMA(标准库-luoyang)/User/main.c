
// DMA 存储器到外设（串口）数据传输实验

#include "stm32f10x.h"
#include "bsp_usart_dma.h"
#include "bsp_led.h"

extern uint8_t txMessages[SENDBUFF_SIZE];
static void Delay(__IO u32 nCount); 


/**
  * @brief  编码函数
  * @param  Send1
	* @param  Send2
  * @retval 无
  */

void MsgCoding(uint16_t Send1,uint16_t Send2)
{
	uint16_t sum=0,i;
	txMessages[0]='!';
	txMessages[1]=0x05;
	txMessages[2]=(unsigned char)((Send1 >> 8)& 0x00ff);
	txMessages[3]=(unsigned char)(Send1 & 0x00ff);
	txMessages[4]=(unsigned char)((Send2 >> 8)& 0x00ff);
	txMessages[5]=(unsigned char)(Send2 & 0x00ff);
//	for(i=0;i<6;i++)
//	{
//		sum+=txMessages[i];
//	}
//	txMessages[6]=(unsigned char)(sum & 0x00ff);
	Append_CRC16_Check_Sum(txMessages, SENDBUFF_SIZE);
}
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
  uint16_t i;
	MsgCoding(0xeeff,0xabcd);
	LED_GPIO_Config();
  USART_Config(); 
  USARTx_DMA_Config();
  USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx, ENABLE);
  while(1)
  {
    //Usart_SendArray(DEBUG_USARTx,txMessages,7);
//		USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx, ENABLE);
//		DMA_Cmd (USART_TX_DMA_CHANNEL,ENABLE);
//		Delay(0x1fffff);
//		DMA_Cmd (USART_TX_DMA_CHANNEL,DISABLE);
//		DMA_DeInit(USART_TX_DMA_CHANNEL);
//		DMA_SetCurrDataCounter(USART_TX_DMA_CHANNEL, 7); 
		Delay(0x1fffff);
		LED1_TOGGLE;
  }
}

static void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/
