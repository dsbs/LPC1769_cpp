#include "LPC17xx.h"
#include "lamp.h"

Lamp::Lamp(Pin &pin, bool initial_state /* = false */, bool inverted /* = false */)
   : _pin(&pin), _is_on(initial_state), _inverted(!inverted)
{
   LPC_SC->PCONP      |= (1 << 15); // power up GPIO
   _pin->port->FIODIR |= (1 << _pin->pin);

   if (initial_state) {on();} else {off();}
}
