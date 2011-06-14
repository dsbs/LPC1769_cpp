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

/******************************************************************************
 * Forward declarations
 *****************************************************************************/
struct Pin
{
   volatile LPC_GPIO_TypeDef * port;
   uint8_t pin; // which pin
};


/**
 * Lamp provides abstraction for a lamp connected to uC.
 * @todo Connect this class to hardware pins.
 */
class Lamp {
   public:
      /*****************************************************
       * Constructors
       *****************************************************/
      /**
       * Default empty construcor
       */
      Lamp() {};

      /**
       * Constructor allowing to assign a pin, change the inital state and specify if lamp logic is inverted or not.
       * @param[in] pin pin to which Lamp is connected.
       * @param[in] initial_state off when false (default), on when true.
       * @param[in] inverted true when lamp is inverted, fale (default) otherwise
       */
      Lamp(Pin &pin, bool initial_state /* = false */, bool inverted /* = false */);

      /**
       * Default destructor
       */
      ~Lamp() {};

      /*****************************************************
       * Functions: modifiers (set), selectors (get)
       *****************************************************/
      /**
       * Function used for verifying if a lamp is on or not.
       * @return true if lamp is on, false otherwise.
       */
      bool is_on() {return ((_pin->port->FIOSET & (1 << _pin->pin)) > 0);}

      /**
       * Turns the lap on
       */
      void __INLINE on(void) {_pin->port->FIOSET = (1 << _pin->pin);}

      /**
       * Turns the lap off
       */
      void __INLINE off(void) {_pin->port->FIOCLR = (1 << _pin->pin);}

      /**
       * Toggles the lap
       */
      void __INLINE toggle(void) {_pin->port->FIOPIN ^= (1 << _pin->pin);}

      /*****************************************************
       * Iterators
       *****************************************************/

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
      Pin *_pin; /**< Microcontroler pin lamp is connected to. */
      bool _is_on; /**< Whether a lamp is on. */
      bool _inverted; /**< Whether a lamp is inverted. */
      uint32_t on_mask;
};
