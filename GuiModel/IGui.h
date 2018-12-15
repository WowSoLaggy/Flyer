#pragma once

#include "GuiModelFwd.h"


class IGui
{
public:

  IGui();
  virtual ~IGui() = default;

  GuiId getId() const { return d_id; }

private:

  GuiId d_id;
  static GuiId s_nextId;

};
