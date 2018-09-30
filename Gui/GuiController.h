#pragma once

#include "IGui.h"
#include "IGuiController.h"


class GuiController : public IGuiController
{
public:

  virtual void initialize() override;
  virtual void dispose() override;

  virtual void removeAllGuis() override;

private:

  std::vector<IGui> d_guis;

};
