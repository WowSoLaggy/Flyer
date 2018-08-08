#pragma once

#include "InputDeviceFwd.h"


class IInputDevice
{
public:

  static std::shared_ptr<IInputDevice> create();

public:

  virtual ~IInputDevice() = default;

  virtual void processMessage(const InputMessage& i_inputMessage) = 0;

};
