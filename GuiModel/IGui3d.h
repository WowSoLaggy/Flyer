#pragma once

#include "IGui.h"

#include <LaggySdk/IPosition3.h>
#include <LaggySdk/IRotation3.h>
#include <LaggySdk/IScale3.h>


class IGui3d : public IGui, public Sdk::IPosition3, public Sdk::IRotation3, public Sdk::IScale3
{
public:
  virtual ~IGui3d() = default;

  virtual bool is3d() const override { return true; }
};
