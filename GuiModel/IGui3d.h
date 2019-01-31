#pragma once

#include "IGui.h"

#include <Sdk/IPosition3.h>
#include <Sdk/IRotation3.h>
#include <Sdk/IScale3.h>


class IGui3d : public IGui, public IPosition3, public IRotation3, public IScale3
{
public:
  virtual ~IGui3d() = default;

  virtual bool is3d() const override { return true; }
};
