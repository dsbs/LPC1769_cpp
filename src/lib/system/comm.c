/* Martin Thomas 4/2009 */

#include "stm32f10x.h"
#include "comm.h"

#define USARTx USART1

int comm_test(void)
{
	return ( USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET ) ? 0 : 1;
}

unsigned char comm_get(void)
{
	while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET) { ; }
	return (unsigned char)USART_ReceiveData(USARTx);
}

void comm_put(unsigned char d)
{
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET) { ; }
	USART_SendData(USARTx, (uint16_t)d);
}

void comm_init(void)
{
	USART_InitTypeDef USART_InitStructure;

	/* USART1 configuration ------------------------------------------------------*/
	/* USART configured as follow:
	 - BaudRate = 19200 baud
	 - Word Length = 8 Bits
	 - One Stop Bit
	 - No parity
	 - Hardware flow control disabled (RTS and CTS signals)
	 - Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure USART1 */
	USART_Init(USART1, &USART_InitStructure);

	/* Enable the USART1 */
	USART_Cmd(USART1, ENABLE);
}


