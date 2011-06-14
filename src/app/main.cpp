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
#include "lamp.h"

volatile uint32_t msTicks;                            /* counts 1ms timeTicks */

/* #define VERSION_STRING "V1.2.0 12/2009" */
void Default_Handler(void)
{
   /* Go into an infinite loop */
   while (1)
   {}
}

/*----------------------------------------------------------------------------
   SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void)
{
   msTicks++;                       /* increment counter necessary in Delay() */
}

/*------------------------------------------------------------------------------
   delays number of tick Systicks (happens every 1 ms)
 *------------------------------------------------------------------------------*/
__INLINE static void Delay(uint32_t dlyTicks)
{
   uint32_t curTicks;

   curTicks = msTicks;
   while ((msTicks - curTicks) < dlyTicks)
   {
      ;
   }
}

__attribute__((section(".fastcode")))
void fastCodeFunct(void);


/**************************************************************************//**
 * main
 * Function from which everything starts...
 *
 * @return on embedded targets this function shall never return
 *
 *****************************************************************************/
int main(void)
{
   /*   fastCodeFunct(); */
   /*	  if (SysTick_Config(12 / 1000)) { / * Setup SysTick Timer for 1 msec interrupts  * / */
   /*	    while (1);                                  / * Capture error * / */
   /* */
   /*	  } */

   Pin  p1_25 = {
      LPC_GPIO1, 25
   };
   Pin  p1_26 = {
      LPC_GPIO1, 26
   };
   Lamp the_blinker(p1_25, false, false);
   Lamp the_inverted_blinker(p1_26, false, true);

   (void)SysTick_Config(100 * 1000);

   while (1)
   {
      the_blinker.toggle();
      Delay(100);
      the_blinker.toggle();
      the_inverted_blinker.toggle();
      Delay(100);
   }
   return(0);
} /* main */

void fastCodeFunct(void)
{
   /* int dd = SysTick_Config(12 / 1000); */
/*   LED_Config(); */
/*   LED_On ();                           / * Turn on the LED. * / */
/*   Delay (100);                                / * delay  100 Msec * / */
/*   LED_Off ();                          / * Turn off the LED. * / */
/*   Delay (100);                                / * delay  100 Msec * / */
}
