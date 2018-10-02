#pragma once

#include "GuiModelFwd.h"


class GuiCollection
{
public:

  const std::vector<std::shared_ptr<IGui>>& getGuis() const { return d_guis; }

  void addGui(std::shared_ptr<IGui> i_gui);

private:

  std::vector<std::shared_ptr<IGui>> d_guis;

};
