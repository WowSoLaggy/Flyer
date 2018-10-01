#pragma once

#include "GuiModelFwd.h"


class GuiCollection
{
public:

  std::vector<std::shared_ptr<IGui>>& getGuis() { return d_guis; }
  const std::vector<std::shared_ptr<IGui>>& getGuis() const { return d_guis; }

private:

  std::vector<std::shared_ptr<IGui>> d_guis;

};
