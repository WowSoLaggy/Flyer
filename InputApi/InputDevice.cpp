#include "stdafx.h"
#include "InputDevice.h"


void InputDevice::initialize()
{
  d_keyboard.reset(new Keyboard());
}

void InputDevice::dispose()
{
  d_keyboard.reset();
}


const KeyboardState& InputDevice::check()
{
  auto state = d_keyboard->GetState();
  memcpy(&d_keyboardState, &state, sizeof(state));

  return d_keyboardState;
}
