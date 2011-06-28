
#include "SystemTick.h"
#include "system_LPC17xx.h"

bool SystemTick::initialized = false;
volatile uint32_t SystemTick::msTicks = 0; /* counts 1ms timeTicks */

int SystemTick::initialize() 
{
   if (!initialized)
   {
      uint32_t ticks = GetSystemCoreClock() / 1000;                /* Hard coded at 1000Hz (1ms) */
      if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            /* Reload value impossible */

      SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      /* set reload register */
      NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Cortex-M0 System Interrupts */
      SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
      SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
         SysTick_CTRL_TICKINT_Msk   |
         SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */

      SystemTick::msTicks = 0;
      initialized = true;
   }
   return (0);
}

