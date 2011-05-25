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

typedef uint32_t Pin;

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
      Lamp(Pin pin, bool initial_state /* = false */, bool inverted /* = false */);

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
      bool is_on() {return _is_on;};

      /**
       * Turns the lap on
       */
      void on(void) {_is_on = true;};

      /**
       * Turns the lap off
       */
      void off(void) {_is_on = false;};

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
      Pin _pin; /**< Microcontroler pin lamp is connected to. */
      bool _is_on; /**< Whether a lamp is on. */
      bool _inverted; /**< Whether a lamp is inverted. */
};
