#pragma once

#include "GuiModelFwd.h"


class GuiCollection
{
public:

  IGuiPtrs& getGuis() { return d_guis; }
  const IGuiPtrs& getGuis() const { return d_guis; }

private:

  IGuiPtrs d_guis;

};
