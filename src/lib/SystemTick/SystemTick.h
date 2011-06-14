/**************************************************************************//**
 * @file    Lamp.h
 * @brief   File contains class declaration of Lamp class.
 * @author  Dawid Bazan <dawidbazan@gmail.com>
 * @author  Dariusz Synowiec <devemouse@gmail.com>
 * @version 0.1.0
 * @date    May 2011
 * @warning This was never programmed to the uC yet.
 *****************************************************************************/

/******************************************************************************
 * Include files
 *****************************************************************************/
#include "inttypes.h"
#include "LPC17xx.h"

/**
 * SystemTick is used to handle SysTick counter in CM3
 * Class provides init, ISR handler, delay function.
 */
class SystemTick {
   public:
      /*****************************************************
       * Constructors
       *****************************************************/
      /**
       * Default empty construcor
       */
      SystemTick() { initialized = false; msTicks = 0;}

      /**
       * Initialize funcion shall be called as soon as clocks are set.
       * @param[in] ticks value for cpu register.
       * @return non-zero if failed to initialize
       * @todo in SystemTick::initialize change ticks to us.
       */
      int initialize(uint32_t ticks) ;

      /*****************************************************
       * Functions: modifiers (set), selectors (get)
       *****************************************************/

      /*****************************************************
       * Iterators
       *****************************************************/

      /*****************************************************
       * Other Functions
       *****************************************************/

      /**
       * Waits for dlyTicks amount of time
       * @param[in] dlyTicks amount of ticks to wait
       * @todo in SystemTick::wait change dlyTicks to us.
       */
      __INLINE static void wait(uint32_t dlyTicks) {
         if (initialized) {
            uint32_t curTicks;
            curTicks = msTicks;
            while ((msTicks - curTicks) < dlyTicks) {}
         }
      }

      /**
       * ISR inline Handler increments counter necessary in wait()
       * Shall be called inside usual ISR handler
       */
      __INLINE static void SysTick_Handler(void) { msTicks++;}

      /*****************************************************
       * Public attributes
       *****************************************************/

   protected:
      /*****************************************************
       * Protected functions
       *****************************************************/

      /*****************************************************
       * Protected attributes
       *****************************************************/

   private:
      /*****************************************************
       * Private functions
       *****************************************************/

      /*****************************************************
       * Private attributes
       *****************************************************/
      static volatile uint32_t msTicks; /**< counts 1ms timeTicks */
      static bool initialized; /**< whether SysTick was initialized or not*/
};
