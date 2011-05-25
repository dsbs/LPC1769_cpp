#include "inttypes.h"


class Lamp {
   public:
      Lamp() {};
      ~Lamp() {};

      Lamp(bool initial_state);
      Lamp(uint32_t pin, bool initial_state /* = false */);

      bool is_on() {return _is_on;};
      void on(void) {_is_on = true;};
      void off(void) {_is_on = false;};

   private:
      bool _is_on;
      uint32_t _pin;
};
