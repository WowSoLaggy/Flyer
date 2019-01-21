#pragma once

#include "GuiModelFwd.h"


class HudCollection
{
public:

  IHudPtrs& getHuds() { return d_huds; }
  const IHudPtrs& getHuds() const { return d_huds; }

private:

  IHudPtrs d_huds;

};
