#include "stdafx.h"
#include "IInputDevice.h"

#include "InputDevice.h"


std::shared_ptr<IInputDevice> IInputDevice::create()
{
  return std::make_shared<InputDevice>();
}
