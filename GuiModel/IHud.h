#pragma once

#include "IGui.h"

#include <Sdk/IPosition3.h>
#include <Sdk/IRotation3.h>


class IHud : public IGui, public IPosition3, public IRotation3
{
public:
  virtual ~IHud() = default;

  virtual bool isHud() const override { return true; }
};
