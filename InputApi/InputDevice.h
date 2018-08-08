#pragma once

#include "IInputDevice.h"


class InputDevice : public IInputDevice
{
public:

  virtual void processMessage(const InputMessage& i_inputMessage) override;

};
