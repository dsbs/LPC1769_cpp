#include "Lamp.h"

Lamp::Lamp(bool initial_state) 
   : _is_on(initial_state)
{
}

Lamp::Lamp(uint32_t pin, bool initial_state = false) 
   : _is_on(initial_state), _pin(pin)
{
}
