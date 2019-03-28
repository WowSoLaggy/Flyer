#include "stdafx.h"
#include "InputDevice.h"

#include <WindowsApi/Message.h>


void InputDevice::processMessage(const Message& i_inputMessage)
{
  Keyboard::ProcessMessage(static_cast<UINT>(i_inputMessage.message), i_inputMessage.wParam, i_inputMessage.lParam);
}
