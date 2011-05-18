/**************************************************************************//**
 * @file main.cpp
 * @brief This file contains main loop
 * @author Dawid Bazan <dawidbazan@gmail.com>
 * @author Dariusz Synowiec <devemouse@gmail.com>
 * @version 0.0
 * @date    May 2011
 * @bug There is no bug. left this to have a refference.
 * @warning This was never programmed to the uC yet.
 *****************************************************************************/

#include "LPC17xx.h"

//#define VERSION_STRING "V1.2.0 12/2009"


volatile uint32_t msTicks;                            /* counts 1ms timeTicks */
/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
  msTicks++;                        /* increment counter necessary in Delay() */
}

/*------------------------------------------------------------------------------
  delays number of tick Systicks (happens every 1 ms)
 *------------------------------------------------------------------------------*/
__INLINE static void Delay (uint32_t dlyTicks) {
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks);
}

/*------------------------------------------------------------------------------
  configer LED pins
 *------------------------------------------------------------------------------*/
__INLINE static void LED_Config(void) {

  LPC_GPIO1->FIODIR = 0xB0000000;               /* LEDs PORT1 are Output */
}

/*------------------------------------------------------------------------------
  Switch on LEDs
 *------------------------------------------------------------------------------*/
__INLINE static void LED_On (uint32_t led) {

  LPC_GPIO1->FIOPIN |=  (led);                  /* Turn On  LED */
}

/**************************************************************************//**
 * LED_Off
 * Turns off a led connected to some pin
 *
 * @param uint32_t led channel
 *
 *****************************************************************************/
__INLINE static void LED_Off (uint32_t led) {

  LPC_GPIO1->FIOPIN &= ~(led);                  /* Turn Off LED */
}

/**************************************************************************//**
 * main
 * Function from which everything starts...
 *
 * @return on embeded targets this function shall never return
 *
 *****************************************************************************/
int main(void)
{
	  if (SysTick_Config(12 / 1000)) { /* Setup SysTick Timer for 1 msec interrupts  */
	    while (1);                                  /* Capture error */
	  }

	  LED_Config();

	  while(1) {
	    LED_On ((1<<28));                           /* Turn on the LED. */
	    Delay (100);                                /* delay  100 Msec */
	    LED_Off ((1<<28));                          /* Turn off the LED. */
	    Delay (100);                                /* delay  100 Msec */
	  }
	  return 0;
}

