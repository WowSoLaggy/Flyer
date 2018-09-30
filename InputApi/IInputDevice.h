#pragma once

#include "InputDeviceFwd.h"


class IInputDevice
{
public:

  static std::shared_ptr<IInputDevice> create();

public:

  virtual ~IInputDevice() = default;

  virtual void initialize() = 0;
  virtual void dispose() = 0;

  virtual void processMessage(const InputMessage& i_inputMessage) = 0;

  virtual const KeyboardState& check() = 0;

};
