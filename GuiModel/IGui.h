#pragma once

#include "GuiModelFwd.h"

#include <Sdk/IUniqueId.h>


class IGui : public IUniqueId
{
public:
  virtual ~IGui() = default;
};
