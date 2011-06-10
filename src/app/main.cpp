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

volatile uint32_t msTicks;                            /* counts 1ms timeTicks */

//#define VERSION_STRING "V1.2.0 12/2009"

void Default_Handler(void)
{
   LPC_GPIO1->FIOCLR_b25 = 1;
   /* Go into an infinite loop */
   while (1)
   {}
}

void SysTick_Handler(void)
{
   LPC_GPIO1->FIOCLR_b27 = 1;
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

   LPC_SC->PCONP |= ( 1 << 15 ); // power up GPIO
  LPC_GPIO1->FIODIR = 1; //1-output pin, 0-input pin
}

/*------------------------------------------------------------------------------
  Switch on LEDs
 *------------------------------------------------------------------------------*/
__INLINE static void LED_On () {

  LPC_GPIO1->FIOPIN = 0;                  /* 0 - Turn On  LED */
}

/**************************************************************************//**
 * LED_Off
 * Turns off a led connected to some pin
 *
 * @param uint32_t led channel
 *
 *****************************************************************************/
__INLINE static void LED_Off () {

   LPC_GPIO1->FIOPIN = 1;                  /* 1 - Turn Off LED */
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

volatile uint32_t temp;
void _delay(uint32_t del);

void _delay(uint32_t del){
   uint32_t i;
   for(i=0;i<del;i++)
       temp = i;
}

/**************************************************************************//**
 * main
 * Function from which everything starts...
 *
 * @return on embedded targets this function shall never return
 *
 *****************************************************************************/
int main(void)
{
   //   int i;
   //   static int j;
   //
   //   static Bits bits;
   //   bits.all = 0xFFFFFFFF;
   //   bits.b1 = 0;
   //   bits.b5 = 0;
   //   if(1==bits.b1)
   //   {
   //      bits.b2 = 0;
   //   }
   //   else
   //   {
   //      bits.b2 = 1;
   //   }
   //
   //   fastCodeFunct();
   //	  if (SysTick_Config(12 / 1000)) { /* Setup SysTick Timer for 1 msec interrupts  */
   //	    while (1);                                  /* Capture error */
   //
   //	  }

   //	  LED_Config();
   //
   //	  while(1) {
   ////	     i++;
   ////	       j--;
   //	    LED_Off ();                           /* Turn on the LED. */
   //	    Delay (100);                                /* delay  100 Msec */
   //	    LED_Off ();                          /* Turn off the LED. */
   //	    Delay (100);                                /* delay  100 Msec */
   //
   //	  }
   //	  return 0;

   LPC_SC->PCONP |= ( 1 << 15 ); // power up GPIO
   LPC_GPIO1->FIODIR_b24 = 1;
   LPC_GPIO1->FIODIR_b22 = 1;
   LPC_GPIO1->FIODIR_b25 = 1;
   LPC_GPIO1->FIODIR_b26 = 1;
   LPC_GPIO1->FIOSET_b22 = 1;
   LPC_GPIO1->FIOSET_b24 = 1;

   LPC_GPIO1->FIODIR_b27 = 1;
   LPC_GPIO1->FIOSET_b27 = 1;


   (void)SysTick_Config(100 * 1000);
   LPC_GPIO1->FIOCLR_b22 = 1;

   while(1)
   {
      LPC_GPIO1->FIOSET_b25 = 1;
      LPC_GPIO1->FIOCLR_b26 = 1;
      Delay(100);
      LPC_GPIO1->FIOCLR_b25 = 1;
      LPC_GPIO1->FIOSET_b26 = 1;
      Delay(100);
   }
   return 0;
}


void fastCodeFunct(void)
{
   //int dd = SysTick_Config(12 / 1000);
//   LED_Config();
//   LED_On ();                           /* Turn on the LED. */
//   Delay (100);                                /* delay  100 Msec */
//   LED_Off ();                          /* Turn off the LED. */
//   Delay (100);                                /* delay  100 Msec */
}
