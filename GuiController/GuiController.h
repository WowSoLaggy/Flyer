#pragma once

#include <GuiModel/GuiModelFwd.h>


class GuiController
{
public:

  static std::shared_ptr<GuiCollection> createGameGui();

  static void update(GuiCollection& io_guiCollection, double i_dt);

private:
  GuiController() = delete;
};
