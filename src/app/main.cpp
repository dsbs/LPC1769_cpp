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


#include "lamp.h"
#include "SystemTick.h"

#include "LPC17xx.h"

/* #define VERSION_STRING "V1.2.0 12/2009" */

/**************************************************************************//**
 * Default_Handler is an ISR handler for every unknown interrupt.
 * This one is optional and placed here as an example. User might want to e.g.
 * set some debug pin here
 *****************************************************************************/
void Default_Handler(void)
{
   /* Go into an infinite loop */
   while (1) {}
}

/**************************************************************************//**
 * SysTick_Handler is an ISR handler for SysTick interrupt
 *****************************************************************************/
void SysTick_Handler(void)
{
   SystemTick::SysTick_Handler();
}

__attribute__((section(".fastcode")))
void fastCodeFunct(void);


/**************************************************************************//**
 * main
 * Function from which everything starts...
 *
 * @return on embedded targets this function shall never return
 *****************************************************************************/
int main(void)
{
   // fastCodeFunct();
   // if (SysTick_Config(12 / 1000)) { / * Setup SysTick Timer for 1 msec interrupts  * /
   // while (1);                                  / * Capture error * /
   //
   // }

   Pin p1_25 = {LPC_GPIO1, 25};
   Pin p1_26 = {LPC_GPIO1, 26};

   Lamp the_blinker(p1_25, false, false);
   Lamp the_inverted_blinker(p1_26, false, true);

   SystemTick systick;
   (void)systick.initialize(100 * 1000);

   while (1)
   {
      the_blinker.toggle();
      systick.wait(100);
      the_blinker.toggle();
      the_inverted_blinker.toggle();
      systick.wait(100);
   }
   return(0);
} /* main */

/**************************************************************************//**
 * fastCodeFunct
 * Dummy function running from RAM.
 * It is placed here only to show how to use such thing.
 *****************************************************************************/
void fastCodeFunct(void)
{
   // int dd = SysTick_Config(12 / 1000);
   // LED_Config();
   // LED_On ();                           / * Turn on the LED. * /
   // Delay (100);                                / * delay  100 Msec * /
   // LED_Off ();                          / * Turn off the LED. * /
   // Delay (100);                                / * delay  100 Msec * /
}
