#include "stdafx.h"
#include "InputDevice.h"


void InputDevice::initialize()
{
  d_keyboard.reset(new Keyboard());
  d_keyboardState.reset();
}

void InputDevice::dispose()
{
  d_keyboard.reset();
}


const KeyboardState& InputDevice::check()
{
  auto state = d_keyboard->GetState();

  KeyboardKeys keyboardKeys;
  memcpy(&keyboardKeys, &state, sizeof(state));

  d_keyboardState.update(keyboardKeys);

  return d_keyboardState;
}
