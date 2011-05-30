/**************************************************************************//**
 * @file main.cpp
 * @brief This file contains main loop
 * @author Dawid Bazan <dawidbazan@gmail.com>
 * @author Dariusz Synowiec <devemouse@gmail.com>
 * @version 0.0
 * @date    May 2011
 * @bug There is no bug. left this to have a reference.
 * @warning This was never programmed to the uC yet.
 *****************************************************************************/

/** 
 * \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */


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

__attribute__ ((section(".fastcode")))
void fastCodeFunct(void);

typedef union
{
   struct
   {
      int b1:1;
      int b2:1;
      int b3:1;
      int b4:1;
      int b5:27;
   };
   int all;
}Bits;

/**************************************************************************//**
 * main
 * Function from which everything starts...
 *
 * @return on embedded targets this function shall never return
 *
 *****************************************************************************/
int main(void)
{
   int i;
   static int j;

   static Bits bits;
   bits.all = 0xFFFFFFFF;
   bits.b1 = 0;
   bits.b5 = 0;
   if(1==bits.b1)
   {
      bits.b2 = 0;
   }
   else
   {
      bits.b2 = 1;
   }

   fastCodeFunct();
	  if (SysTick_Config(12 / 1000)) { /* Setup SysTick Timer for 1 msec interrupts  */
	    while (1);                                  /* Capture error */

	  }

	  LED_Config();

	  while(1) {
	     i++;
	       j--;
	    LED_On ((1<<28));                           /* Turn on the LED. */
	    Delay (100);                                /* delay  100 Msec */
	    LED_Off ((1<<28));                          /* Turn off the LED. */
	    Delay (100);                                /* delay  100 Msec */

	  }
	  return 0;
}


void fastCodeFunct(void)
{
   //int dd = SysTick_Config(12 / 1000);
   LED_Config();
   LED_On ((1<<28));                           /* Turn on the LED. */
   Delay (100);                                /* delay  100 Msec */
   LED_Off ((1<<28));                          /* Turn off the LED. */
   Delay (100);                                /* delay  100 Msec */
}
