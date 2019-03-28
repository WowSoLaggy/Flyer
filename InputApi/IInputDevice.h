#pragma once

#include "InputApiFwd.h"

#include <WindowsApi/WindowsApiFwd.h>


class IInputDevice
{
public:

  static std::shared_ptr<IInputDevice> create();

public:

  virtual ~IInputDevice() = default;

  virtual void initialize() = 0;
  virtual void dispose() = 0;

  virtual void processMessage(const Message& i_inputMessage) = 0;

  virtual const KeyboardState& check() = 0;

};
