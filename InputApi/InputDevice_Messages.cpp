#include "stdafx.h"
#include "InputDevice.h"

#include "InputMessage.h"


void InputDevice::processMessage(const InputMessage& i_inputMessage)
{
  Keyboard::ProcessMessage(i_inputMessage.message, i_inputMessage.wParam, i_inputMessage.lParam);
}
