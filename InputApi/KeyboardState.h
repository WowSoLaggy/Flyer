#pragma once

#include "KeyboardKeys.h"


class KeyboardState
{
public:
  KeyboardKeys pressed;
  KeyboardKeys released;
  KeyboardKeys currentState;

  KeyboardState();

  void update(const KeyboardKeys& i_state);
  void reset();
};


