#include "stdafx.h"
#include "IInputDevice.h"

#include "InputDevice.h"


std::shared_ptr<IInputDevice> IInputDevice::create()
{
  auto* pInputDevice = new InputDevice();
  return std::shared_ptr<IInputDevice>(pInputDevice);
}
