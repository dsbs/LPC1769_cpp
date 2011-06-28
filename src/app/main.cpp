/**************************************************************************//**
 * @file main.cpp
 * @brief This file contains main loop
 * @author Dawid Bazan <dawidbazan@gmail.com>
 * @author Dariusz Synowiec <devemouse@gmail.com>
 * @version 0.1.0dev
 * @date    May 2011
 * @bug There is no bug. left this to have a reference.
 *****************************************************************************/

/**
 * \mainpage LPC176x Startup project
 *
 * \section intro_sec Introduction
 *
 * The project main goal is to provide a template startup project for LPC176x micro.
 * See README for more details.
 *
 */

#define VERSION_STRING "v0.1.0dev"

#include "lamp.h"
#include "SystemTick.h"

#include "LPC17xx.h"

/**************************************************************************//**
 * Default_Handler is an ISR handler for every unknown interrupt.
 * This one is optional and placed here as an example. User might want to e.g.
 * set some debug pin here
 *****************************************************************************/
void Default_Handler(void)
{
   /* Go into an infinite loop */
   while (1)
   {}
}

/**************************************************************************//**
 * SysTick_Handler is an ISR handler for SysTick interrupt
 *****************************************************************************/
void SysTick_Handler(void)
{
   SystemTick::SysTick_Handler();
}

/**************************************************************************//**
 * This function is run from RAM not from ROM
 *****************************************************************************/
__attribute__((section(".fastcode")))
void fastCodeFunct(void);


/**************************************************************************//**
 * enableCLKOUT
 * After calling this function you will have cpu clock divided by 10 on pin 1.27
 *****************************************************************************/
void enableCLKOUT(void)
{
   LPC_GPIO1->FIODIR_b27 = 1;          // 1 - output
   LPC_SC->CLKOUTCFG     = 0x00000190; // 0x0100 - enable, 0x00A0 - divide by 10
   LPC_PINCON->PINSEL3   = 0x00400000; // set pin as CLKOUT
}

/**************************************************************************//**
 * main
 * Function from which everything starts...
 *
 * @return on embedded targets this function shall never return
 *****************************************************************************/
int main(void)
{
   enableCLKOUT();

   Pin p1_25 = {LPC_GPIO1, 25};
   Pin p1_26 = {LPC_GPIO1, 26};

   Lamp the_blinker(p1_25, false, false);
   Lamp the_inverted_blinker(p1_26, false, true);

   SystemTick systick;

   (void)systick.initialize();

   while (1)
   {
      the_blinker.toggle();
      systick.wait_ms(100);
      the_blinker.toggle();
      the_inverted_blinker.toggle();
      systick.wait_ms(100);
   }
   return(0);
} /* main */
