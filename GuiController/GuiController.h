#pragma once

#include <GuiModel/GuiModelFwd.h>


class GuiController
{
public:

  static std::shared_ptr<GuiCollection> createGameGui();

private:
  GuiController() = delete;
};
