#include "lamp.h"


Lamp::Lamp(Pin pin, bool initial_state = false, bool inverted = false) 
   : _pin(pin), _is_on(initial_state), _inverted(inverted)
{
}
