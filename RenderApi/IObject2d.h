#pragma once

#include "RenderApiFwd.h"


class IObject2d
{
public:

  virtual ~IObject2d() = default;

  virtual ResourceId getFontResourceId() const = 0;

};
