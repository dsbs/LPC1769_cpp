/*
 * dummy.c
 *
 *  Created on: 10-06-2011
 *      Author: bazi
 */
#include "LPC17xx.h"

volatile uint32_t msTicks;                            /* counts 1ms timeTicks */

/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void)
{
   LPC_GPIO1->FIOCLR_b27 = 1;
  msTicks++;                        /* increment counter necessary in Delay() */
}

