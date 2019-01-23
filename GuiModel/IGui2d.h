#pragma once

#include "IGui.h"


class IGui2d : public IGui
{
public:
  virtual ~IGui2d() = default;

  virtual bool is3d() const override { return false; }
};
