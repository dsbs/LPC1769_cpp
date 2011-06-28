/**************************************************************************//**
 * @file    SystemTick.h
 * @brief   File contains declaration of SystemTick class.
 * @author  Dawid Bazan <dawidbazan@gmail.com>
 * @author  Dariusz Synowiec <devemouse@gmail.com>
 * @version 0.1.0
 * @date    June 2011
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
       * Initializes Systick counter at fixed 1ms. 
       * This method shall be called as soon as clocks are set.
       * @return non-zero if failed to initialize
       */
      int initialize();

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
       * Waits for delay_ms amount of time
       * @param[in] delay_ms amount of miliseconds to wait
       */
      __INLINE static void wait_ms(uint32_t delay_ms) {
         if (initialized) {
            uint32_t curTicks;
            curTicks = msTicks;
            while ((msTicks - curTicks) < delay_ms) {}
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
